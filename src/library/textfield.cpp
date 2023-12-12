#include "textfield_internal.hpp"
#include "textfield_p.hpp"

#include <QtMaterialWidgets/textfield.hpp>
#include "palette-helper.hpp"

#include <QDebug>
#include <QPainter>
#include <QtWidgets/QApplication>

MaterialTextFieldPrivate::MaterialTextFieldPrivate(MaterialTextField* q)
    : q_ptr(q)
{
}

MaterialTextFieldPrivate::~MaterialTextFieldPrivate()
{
}

void MaterialTextFieldPrivate::init()
{
    Q_Q(MaterialTextField);

    material::updatePalette(q);

    stateMachine   = new MaterialTextFieldStateMachine(q);
    label          = nullptr;
    labelFontSize  = 9.5;
    showLabel      = false;
    showInputLine  = true;

    q->setFrame(false);
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setTextMargins(0, 2, 0, 4);
    q->setFont(QFont("Roboto", 11, QFont::Normal));

    stateMachine->start();
    QCoreApplication::processEvents();
}

MaterialTextField::MaterialTextField(QWidget *parent)
    : QLineEdit(parent)
    , d_ptr(new MaterialTextFieldPrivate(this))
{
    d_func()->init();
}

MaterialTextField::~MaterialTextField()
{
}

void MaterialTextField::setShowLabel(bool value)
{
    Q_D(MaterialTextField);

    if (value == d->showLabel)
        return;

    d->showLabel = value;

    if (!d->label && value) {
        d->label = new MaterialTextFieldLabel(this);
        d->stateMachine->setLabel(d->label);
    }

    if (value) {
        setContentsMargins(0, 23, 0, 0);
        return;
    }

    setContentsMargins(0, 0, 0, 0);
}

bool MaterialTextField::hasLabel() const
{
    Q_D(const MaterialTextField);

    return d->showLabel;
}

void MaterialTextField::setLabelFontSize(qreal size)
{
    Q_D(MaterialTextField);

    d->labelFontSize = size;

    if (!d->label)
        return;

    QFont font(d->label->font());
    font.setPointSizeF(size);
    d->label->setFont(font);
    d->label->update();
}

qreal MaterialTextField::labelFontSize() const
{
    Q_D(const MaterialTextField);

    return d->labelFontSize;
}

void MaterialTextField::setLabel(const QString& label)
{
    Q_D(MaterialTextField);

    d->labelString = label;
    setShowLabel(true);
    d->label->update();
}

QString MaterialTextField::label() const
{
    Q_D(const MaterialTextField);

    return d->labelString;
}

void MaterialTextField::setShowInputLine(bool value)
{
    Q_D(MaterialTextField);

    if (d->showInputLine == value)
        return;

    d->showInputLine = value;
    update();
}

bool MaterialTextField::hasInputLine() const
{
    Q_D(const MaterialTextField);

    return d->showInputLine;
}

MaterialTextField::MaterialTextField(MaterialTextFieldPrivate& d, QWidget *parent)
    : QLineEdit(parent),
      d_ptr(&d)
{
    d_func()->init();
}

bool MaterialTextField::event(QEvent *event)
{
    Q_D(MaterialTextField);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move: {
        if (d->label)
            d->label->setGeometry(rect());
    }
    case QEvent::ThemeChange: {
        material::updatePalette(this);
        return true;
    }
    default:
        break;
    }
    return QLineEdit::event(event);
}

void MaterialTextField::paintEvent(QPaintEvent* event)
{
    Q_D(MaterialTextField);

    QLineEdit::paintEvent(event);

    QPainter painter(this);

    const qreal progress = d->stateMachine->progress();

    if (text().isEmpty() && progress < 1)
    {
        painter.setOpacity(1 - progress);
        painter.fillRect(rect(), parentWidget()->palette().color(backgroundRole()));
    }

    const int y = height() - 1;
    const int wd = width() - 5;

    if (d->showInputLine)
    {
        QPen pen;
        pen.setWidth(1);
        pen.setColor(palette().color(QPalette::Button));

        if (!isEnabled())
            pen.setStyle(Qt::DashLine);

        painter.setPen(pen);
        painter.setOpacity(1);
        painter.drawLine(QLineF(2.5, y, wd, y));

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(palette().color(QPalette::Button));

        if (progress > 0)
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(brush);
            const int w = (1 - progress)*static_cast<qreal>(wd / 2);
            painter.drawRect(w + 2.5, height() - 2, wd - w * 2, 2);
        }
    }
}
