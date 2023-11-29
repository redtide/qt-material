#include "switch_internal.hpp"

#include <QtMaterialWidgets/ripple.hpp>
#include <QtMaterialWidgets/switch.hpp>

#include <QEvent>
#include <QPainter>
#include <QtWidgets/QGraphicsDropShadowEffect>

/*!
 *  \class MaterialSwitchRippleOverlay
 *  \internal
 */

MaterialSwitchRippleOverlay::MaterialSwitchRippleOverlay(
        MaterialSwitchThumb *thumb,
        MaterialSwitchTrack *track,
        MaterialSwitch      *parent)
    : MaterialRippleOverlay(parent->parentWidget()),
      m_toggle(parent),
      m_thumb(thumb),
      m_track(track)
{
    connect(parent, SIGNAL(toggled(bool)), this, SLOT(addToggleRipple()));

    thumb->installEventFilter(this);
}

MaterialSwitchRippleOverlay::~MaterialSwitchRippleOverlay()
{
}

void MaterialSwitchRippleOverlay::addToggleRipple()
{
    if (!m_toggle->isEnabled()) {
        return;
    }

    int t, w;

    if (Qt::Horizontal == m_toggle->orientation()) {
        t = m_toggle->height()/2;
        w = m_thumb->height()/2+10;
    } else {
        t = m_toggle->width()/2;
        w = m_thumb->width()/2+10;
    }

    MaterialRipple *ripple = new MaterialRipple(QPoint(10+t, 20+t));
    ripple->setColor(m_track->trackColor());
    ripple->setRadiusEndValue(w);
    ripple->setOpacityStartValue(0.8);

    addRipple(ripple);
}

bool MaterialSwitchRippleOverlay::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Paint == event->type()) {
        setGeometry(overlayGeometry());
        QList<MaterialRipple *>::const_iterator i;
        QList<MaterialRipple *> items = ripples();
        QColor color = m_track->trackColor();
        for (i = items.begin(); i != items.end(); ++i) {
            (*i)->setColor(color);
        }
    }
    return MaterialRippleOverlay::eventFilter(obj, event);
}

QRect MaterialSwitchRippleOverlay::overlayGeometry() const
{
    const qreal offset = m_thumb->offset();
    if (Qt::Horizontal == m_toggle->orientation()) {
        return m_toggle->geometry().adjusted(-10+offset, -20, 10+offset, 20);
    } else {
        return m_toggle->geometry().adjusted(-10, -20+offset, 10, 20+offset);
    }
}

/*!
 *  \class MaterialSwitchThumb
 *  \internal
 */

MaterialSwitchThumb::MaterialSwitchThumb(MaterialSwitch *parent)
    : QWidget(parent),
      m_toggle(parent),
      m_shift(0),
      m_offset(0)
{
    Q_ASSERT(parent);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
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
    if (m_shift == shift) {
        return;
    }

    m_shift = shift;
    updateOffset();
}

bool MaterialSwitchThumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type)
    {
        setGeometry(m_toggle->rect().adjusted(8, 8, -8, -8));
        updateOffset();
    }
    return QWidget::eventFilter(obj, event);
}

void MaterialSwitchThumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(m_toggle->isEnabled() ? m_thumbColor : Qt::white);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    int s;
    QRectF r;

    if (Qt::Horizontal == m_toggle->orientation()) {
        s = height()-10;
        r = QRectF(5+m_offset, 5, s, s);
    } else {
        s = width()-10;
        r = QRectF(5, 5+m_offset, s, s);
    }

    painter.drawEllipse(r);

    if (!m_toggle->isEnabled()) {
        brush.setColor(m_toggle->disabledColor());
        painter.setBrush(brush);
        painter.drawEllipse(r);
    }
}

void MaterialSwitchThumb::updateOffset()
{
    const QSize s(Qt::Horizontal == m_toggle->orientation()
        ? size() : size().transposed());
    m_offset = m_shift*static_cast<qreal>(s.width()-s.height());
    update();
}

/*!
 *  \class MaterialSwitchTrack
 *  \internal
 */

MaterialSwitchTrack::MaterialSwitchTrack(MaterialSwitch *parent)
    : QWidget(parent),
      m_toggle(parent)
{
    Q_ASSERT(parent);

    parent->installEventFilter(this);
}

MaterialSwitchTrack::~MaterialSwitchTrack()
{
}

void MaterialSwitchTrack::setTrackColor(const QColor &color)
{
    m_trackColor = color;
    update();
}

bool MaterialSwitchTrack::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(m_toggle->rect());
    }
    return QWidget::eventFilter(obj, event);
}

void MaterialSwitchTrack::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    if (m_toggle->isEnabled()) {
        brush.setColor(m_trackColor);
        painter.setOpacity(0.8);
    } else {
        brush.setColor(m_toggle->disabledColor());
        painter.setOpacity(0.6);
    }
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == m_toggle->orientation()) {
        const int h = height()/2;
        const QRect r(0, h/2, width(), h);
        painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h/2-4, h/2-4);
    } else {
        const int w = width()/2;
        const QRect r(w/2, 0, w, height());
        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w/2-4, w/2-4);
    }
}
