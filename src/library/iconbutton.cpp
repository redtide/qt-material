#include "iconbutton_p.hpp"

#include <QtMaterialWidgets/iconbutton.hpp>
#include <QtMaterialWidgets/rippleoverlay.hpp>
#include "palette-helper.hpp"

#include <QEvent>
#include <QPainter>

MaterialIconButtonPrivate::MaterialIconButtonPrivate(MaterialIconButton* q)
    : q_ptr(q)
{
}

MaterialIconButtonPrivate::~MaterialIconButtonPrivate()
{
}

void MaterialIconButtonPrivate::init()
{
    Q_Q(MaterialIconButton);

    material::updatePalette(q, true);

    rippleOverlay  = new MaterialRippleOverlay(q->parentWidget());
    rippleOverlay->installEventFilter(q);

    QSizePolicy policy;
    policy.setWidthForHeight(true);
    q->setSizePolicy(policy);
}

void MaterialIconButtonPrivate::updateRipple()
{
    Q_Q(MaterialIconButton);

    QRect r(q->rect());
    r.setSize(QSize(q->width()*2, q->height()*2));
    r.moveCenter(q->geometry().center());
    rippleOverlay->setGeometry(r);
}

MaterialIconButton::MaterialIconButton(QWidget* parent)
    : QAbstractButton(parent)
    , d_ptr(new MaterialIconButtonPrivate(this))
{
    d_func()->init();
}

MaterialIconButton::MaterialIconButton(const QIcon& icon, QWidget* parent)
    : QAbstractButton(parent)
    , d_ptr(new MaterialIconButtonPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

MaterialIconButton::~MaterialIconButton()
{
}

QSize MaterialIconButton::sizeHint() const
{
    return iconSize();
}

MaterialIconButton::MaterialIconButton(MaterialIconButtonPrivate& d, QWidget* parent)
    : QAbstractButton(parent)
    , d_ptr(&d)
{
    d_func()->init();
}

bool MaterialIconButton::event(QEvent *event)
{
    Q_D(MaterialIconButton);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        d->updateRipple();
        break;
    case QEvent::ParentChange: {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    }
    case QEvent::ThemeChange: {
        material::updatePalette(this, true);
        return true;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

bool MaterialIconButton::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(MaterialIconButton);

        d->updateRipple();
    }
    return QAbstractButton::eventFilter(obj, event);
}

void MaterialIconButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(MaterialIconButton);

    d->rippleOverlay->addRipple(QPoint(d->rippleOverlay->width(),
                                       d->rippleOverlay->height()) / 2,
                                iconSize().width());
    Q_EMIT clicked();

    QAbstractButton::mousePressEvent(event);
}

void MaterialIconButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pixmap = icon().pixmap(iconSize());
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), isEnabled()
        ? palette().color(QPalette::ButtonText)
        : palette().color(QPalette::Disabled, QPalette::ButtonText));

    QRect r(rect());
    const qreal w = pixmap.width();
    const qreal h = pixmap.height();
    painter.drawPixmap(QRect((r.width() - w) /2, (r.height() - h) / 2, w, h), pixmap);
}
