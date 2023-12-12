#include <QtMaterialWidgets/rippleoverlay.hpp>
#include <QtMaterialWidgets/ripple.hpp>

#include <QPainter>

MaterialRippleOverlay::MaterialRippleOverlay(QWidget* parent)
    : MaterialOverlayWidget(parent)
    , useClip_(false)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

MaterialRippleOverlay::~MaterialRippleOverlay()
{
}

void MaterialRippleOverlay::addRipple(MaterialRipple* ripple)
{
    ripple->setOverlay(this);
    ripples_.push_back(ripple);
    ripple->start();

    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(stop()));
    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(deleteLater()));
}

void MaterialRippleOverlay::addRipple(const QPoint &position, qreal radius)
{
    MaterialRipple* ripple = new MaterialRipple(position);
    ripple->setRadiusEndValue(radius);
    addRipple(ripple);
}

void MaterialRippleOverlay::removeRipple(MaterialRipple* ripple)
{
    if (ripples_.removeOne(ripple)) {
        delete ripple;
        update();
    }
}

void MaterialRippleOverlay::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if (useClip_)
        painter.setClipPath(clipPath_);

    for (auto* ripple : std::as_const(ripples_))
        paintRipple(&painter, ripple);
}

void MaterialRippleOverlay::paintRipple(QPainter* painter, MaterialRipple* ripple)
{
    const qreal radius = ripple->radius();
    const QPointF center = ripple->center();
    painter->setOpacity(ripple->opacity());
    painter->setBrush(ripple->brush());
    painter->drawEllipse(center, radius, radius);
}
