#include <QtMaterialWidgets/rippleoverlay.hpp>
#include <QtMaterialWidgets/ripple.hpp>

#include <QPainter>

/*!
 *  \class MaterialRippleOverlay
 *  \internal
 */

MaterialRippleOverlay::MaterialRippleOverlay(QWidget *parent)
    : MaterialOverlayWidget(parent),
      m_useClip(false)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

MaterialRippleOverlay::~MaterialRippleOverlay()
{
}

void MaterialRippleOverlay::addRipple(MaterialRipple *ripple)
{
    ripple->setOverlay(this);
    m_ripples.push_back(ripple);
    ripple->start();

    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(stop()));
    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(deleteLater()));
}

void MaterialRippleOverlay::addRipple(const QPoint &position, qreal radius)
{
    MaterialRipple *ripple = new MaterialRipple(position);
    ripple->setRadiusEndValue(radius);
    addRipple(ripple);
}

void MaterialRippleOverlay::removeRipple(MaterialRipple *ripple)
{
    if (m_ripples.removeOne(ripple)) {
        delete ripple;
        update();
    }
}

/*!
 *  \reimp
 */
void MaterialRippleOverlay::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if (m_useClip)
        painter.setClipPath(m_clipPath);

    for (auto* ripple : qAsConst(m_ripples))
        paintRipple(&painter, ripple);
}

void MaterialRippleOverlay::paintRipple(QPainter *painter, MaterialRipple *ripple)
{
    const qreal radius = ripple->radius();
    const QPointF center = ripple->center();
    painter->setOpacity(ripple->opacity());
    painter->setBrush(ripple->brush());
    painter->drawEllipse(center, radius, radius);
}
