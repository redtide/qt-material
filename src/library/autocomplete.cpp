#include "autocomplete_internal.hpp"
#include "autocomplete_p.hpp"

#include <QtMaterialWidgets/autocomplete.hpp>
#include <QtMaterialWidgets/flatbutton.hpp>

#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QTimer>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>

/*!
 *  \class MaterialAutoCompletePrivate
 *  \internal
 */

/*!
 *  \internal
 */
MaterialAutoCompletePrivate::MaterialAutoCompletePrivate(MaterialAutoComplete *q)
    : MaterialTextFieldPrivate(q)
{
}

/*!
 *  \internal
 */
MaterialAutoCompletePrivate::~MaterialAutoCompletePrivate()
{
}

/*!
 *  \internal
 */
void MaterialAutoCompletePrivate::init()
{
    Q_Q(MaterialAutoComplete);

    menu         = new QWidget;
    frame        = new QWidget;
    stateMachine = new MaterialAutoCompleteStateMachine(menu);
    menuLayout   = new QVBoxLayout;
    maxWidth     = 0;

    menu->setParent(q->parentWidget());
    frame->setParent(q->parentWidget());

    menu->installEventFilter(q);
    frame->installEventFilter(q);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);

    frame->setGraphicsEffect(effect);
    frame->setVisible(false);

    menu->setLayout(menuLayout);
    menu->setVisible(false);

    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setSpacing(0);

    QObject::connect(q, SIGNAL(textEdited(QString)), q, SLOT(updateResults(QString)));

    stateMachine->start();
}

/*!
 *  \class MaterialAutoComplete
 */

MaterialAutoComplete::MaterialAutoComplete(QWidget *parent)
    : MaterialTextField(*new MaterialAutoCompletePrivate(this), parent)
{
    d_func()->init();
}

MaterialAutoComplete::~MaterialAutoComplete()
{
}

QStringList MaterialAutoComplete::dataSource() const
{
    Q_D(const MaterialAutoComplete);
    return d->dataSource;
}

void MaterialAutoComplete::setDataSource(const QStringList &data)
{
    Q_D(MaterialAutoComplete);

    d->dataSource = data;
    update();
}

void MaterialAutoComplete::updateResults(QString text)
{
    Q_D(MaterialAutoComplete);

    QStringList results;
    QString trimmed(text.trimmed());

    if (!trimmed.isEmpty()) {
        QString lookup(trimmed.toLower());
        QStringList::iterator i;
        for (i = d->dataSource.begin(); i != d->dataSource.end(); ++i) {
            if (i->toLower().indexOf(lookup) != -1) {
                results.push_back(*i);
            }
        }
    }

    const int diff = results.length() - d->menuLayout->count();
    QFont font("Roboto", 12, QFont::Normal);

    if (diff > 0) {
        for (int c = 0; c < diff; c++) {
            MaterialFlatButton *item = new MaterialFlatButton;
            item->setFont(font);
            item->setTextAlignment(Qt::AlignLeft);
            item->setCornerRadius(0);
            item->setHaloVisible(false);
            item->setFixedHeight(50);
            item->setOverlayStyle(Material::TintedOverlay);
            d->menuLayout->addWidget(item);
            item->installEventFilter(this);
        }
    } else if (diff < 0) {
        for (int c = 0; c < -diff; c++) {
            QWidget *widget = d->menuLayout->itemAt(0)->widget();
            if (widget) {
                d->menuLayout->removeWidget(widget);
                delete widget;
            }
        }
    }

    QFontMetrics *fm = new QFontMetrics(font);
    d->maxWidth = 0;

    for (int i = 0; i < results.count(); ++i) {
        QWidget *widget = d->menuLayout->itemAt(i)->widget();
        MaterialFlatButton *item;
        if ((item = static_cast<MaterialFlatButton *>(widget))) {
            QString text = results.at(i);
            QRect rect = fm->boundingRect(text);
            d->maxWidth = qMax(d->maxWidth, rect.width());
            item->setText(text);
        }
    }

    if (!results.count()) {
        Q_EMIT d->stateMachine->shouldClose();
    } else {
        Q_EMIT d->stateMachine->shouldOpen();
    }

    d->menu->setFixedHeight(results.length()*50);
    d->menu->setFixedWidth(qMax(d->maxWidth + 24, width()));
    d->menu->update();
}

bool MaterialAutoComplete::event(QEvent *event)
{
    Q_D(MaterialAutoComplete);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize: {
        d->menu->move(pos() + QPoint(0, height() + 6));
        break;
    }
    case QEvent::ParentChange: {
        QWidget *widget = static_cast<QWidget *>(parent());
        if (widget) {
            d->menu->setParent(widget);
            d->frame->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return MaterialTextField::event(event);
}

bool MaterialAutoComplete::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(MaterialAutoComplete);

    if (d->frame == watched)
    {
        switch (event->type())
        {
        case QEvent::Paint: {
            QPainter painter(d->frame);
            painter.fillRect(d->frame->rect(), Qt::white);
            break;
        }
        default:
            break;
        }
    }
    else if (d->menu == watched)
    {
        switch (event->type())
        {
        case QEvent::Resize:
        case QEvent::Move: {
            d->frame->setGeometry(d->menu->geometry());
            break;
        }
        case QEvent::Show: {
            d->frame->show();
            d->menu->raise();
            break;
        }
        case QEvent::Hide: {
            d->frame->hide();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        switch (event->type())
        {
        case QEvent::MouseButtonPress: {
            Q_EMIT d->stateMachine->shouldFade();
            MaterialFlatButton *widget;
            if ((widget = static_cast<MaterialFlatButton *>(watched))) {
                QString text(widget->text());
                setText(text);
                Q_EMIT itemSelected(text);
            }
            break;
        }
        default:
            break;
        }
    }
    return MaterialTextField::eventFilter(watched, event);
}
