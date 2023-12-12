#include "switch_internal.hpp"

#include <QtMaterialWidgets/ripple.hpp>
#include <QtMaterialWidgets/switch.hpp>

#include <QEvent>
#include <QPainter>
#include <QtWidgets/QGraphicsDropShadowEffect>

MaterialSwitchRippleOverlay::MaterialSwitchRippleOverlay(
        MaterialSwitchThumb* thumb,
        MaterialSwitchTrack* track,
        MaterialSwitch*      parent)
    : MaterialRippleOverlay(parent->parentWidget())
    , toggle_(parent)
    , thumb_(thumb)
    , track_(track)
{
    connect(parent, SIGNAL(toggled(bool)), this, SLOT(addToggleRipple()));

    thumb->installEventFilter(this);
}

MaterialSwitchRippleOverlay::~MaterialSwitchRippleOverlay()
{
}

void MaterialSwitchRippleOverlay::addToggleRipple()
{
    if (!toggle_->isEnabled())
        return;

    int t, w;

    if (Qt::Horizontal == toggle_->orientation()) {
        t = toggle_->height() / 2;
        w = thumb_->height() / 2 + 10;
    } else {
        t = toggle_->width() / 2;
        w = thumb_->width() / 2 + 10;
    }
    MaterialRipple* ripple = new MaterialRipple(QPoint(10+t, 20+t));
    ripple->setColor(track_->trackColor());
    ripple->setRadiusEndValue(w);
    ripple->setOpacityStartValue(0.8);

    addRipple(ripple);
}

bool MaterialSwitchRippleOverlay::eventFilter(QObject* obj, QEvent* event)
{
    if (QEvent::Paint == event->type()) {
        setGeometry(overlayGeometry());
        QList<MaterialRipple*>::const_iterator i;
        QList<MaterialRipple*> items = ripples();
        QColor color = track_->trackColor();
        for (i = items.begin(); i != items.end(); ++i)
            (*i)->setColor(color);
    }
    return MaterialRippleOverlay::eventFilter(obj, event);
}

QRect MaterialSwitchRippleOverlay::overlayGeometry() const
{
    const qreal offset = thumb_->offset();
    if (Qt::Horizontal == toggle_->orientation())
        return toggle_->geometry().adjusted(-10 + offset, -20, 10 + offset, 20);
    else
        return toggle_->geometry().adjusted(-10, -20 + offset, 10, 20 + offset);
}

MaterialSwitchThumb::MaterialSwitchThumb(MaterialSwitch* parent)
    : QWidget(parent)
    , toggle_(parent)
    , shift_(0)
    , offset_(0)
{
    Q_ASSERT(parent);

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(6);
    effect->setColor(QColor(0, 0, 0, 80));
    effect->setOffset(QPointF(0, 1));
    setGraphicsEffect(effect);

    parent->installEventFilter(this);
}

MaterialSwitchThumb::~MaterialSwitchThumb()
{
}

void MaterialSwitchThumb::setShift(qreal shift)
{
    if (shift_ == shift)
        return;

    shift_ = shift;
    updateOffset();
}

bool MaterialSwitchThumb::eventFilter(QObject* obj, QEvent* event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type)
    {
        setGeometry(toggle_->rect().adjusted(8, 8, -8, -8));
        updateOffset();
    }
    return QWidget::eventFilter(obj, event);
}

void MaterialSwitchThumb::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(toggle_->isEnabled() ? thumbColor_ : Qt::white);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    int s;
    QRectF r;

    if (Qt::Horizontal == toggle_->orientation()) {
        s = height()-10;
        r = QRectF(5+offset_, 5, s, s);
    } else {
        s = width()-10;
        r = QRectF(5, 5+offset_, s, s);
    }
    painter.drawEllipse(r);

    if (!toggle_->isEnabled()) {
        brush.setColor(toggle_->palette().color(QPalette::Disabled, QPalette::Button));
        painter.setBrush(brush);
        painter.drawEllipse(r);
    }
}

void MaterialSwitchThumb::updateOffset()
{
    const QSize s(Qt::Horizontal == toggle_->orientation()
        ? size() : size().transposed());

    offset_ = shift_*static_cast<qreal>(s.width()-s.height());
    update();
}

MaterialSwitchTrack::MaterialSwitchTrack(MaterialSwitch* parent)
    : QWidget(parent),
      toggle_(parent)
{
    Q_ASSERT(parent);

    parent->installEventFilter(this);
}

MaterialSwitchTrack::~MaterialSwitchTrack()
{
}

void MaterialSwitchTrack::setTrackColor(const QColor &color)
{
    trackColor_ = color;
    update();
}

bool MaterialSwitchTrack::eventFilter(QObject* obj, QEvent* event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type)
        setGeometry(toggle_->rect());

    return QWidget::eventFilter(obj, event);
}

void MaterialSwitchTrack::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    if (toggle_->isEnabled()) {
        brush.setColor(trackColor_);
        painter.setOpacity(0.8);
    } else {
        brush.setColor(toggle_->palette().color(QPalette::Disabled, QPalette::Button));
        painter.setOpacity(0.6);
    }
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == toggle_->orientation()) {
        const int h = height() / 2;
        const QRect r(0, h / 2, width(), h);
        painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h / 2 - 4, h / 2 - 4);
    } else {
        const int w = width() / 2;
        const QRect r(w / 2, 0, w, height());
        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w / 2 - 4, w / 2 - 4);
    }
}
