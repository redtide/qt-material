#include <QtMaterialWidgets/ripple.hpp>
#include <QtMaterialWidgets/rippleoverlay.hpp>

MaterialRipple::MaterialRipple(const QPoint& center, QObject* parent)
    : QParallelAnimationGroup(parent)
    , overlay_(0)
    , radiusAnimation_(animate("radius"))
    , opacityAnimation_(animate("opacity"))
    , radius_(0)
    , opacity_(0)
    , center_(center)
{
    init();
}

MaterialRipple::MaterialRipple(const QPoint& center,
                               MaterialRippleOverlay* overlay,
                               QObject* parent)
    : QParallelAnimationGroup(parent)
    , overlay_(overlay)
    , radiusAnimation_(animate("radius"))
    , opacityAnimation_(animate("opacity"))
    , radius_(0)
    , opacity_(0)
    , center_(center)
{
    init();
}

MaterialRipple::~MaterialRipple()
{
}

void MaterialRipple::setRadius(qreal radius)
{
    Q_ASSERT(overlay_);

    if (radius_ == radius)
        return;

    radius_ = radius;
    overlay_->update();
}

void MaterialRipple::setOpacity(qreal opacity)
{
    Q_ASSERT(overlay_);

    if (opacity_ == opacity)
        return;

    opacity_ = opacity;
    overlay_->update();
}

void MaterialRipple::setColor(const QColor& color)
{
    if (brush_.color() == color)
        return;

    brush_.setColor(color);

    if (overlay_)
        overlay_->update();
}

void MaterialRipple::setBrush(const QBrush& brush)
{
    brush_ = brush;

    if (overlay_)
        overlay_->update();
}

void MaterialRipple::destroy()
{
    Q_ASSERT(overlay_);

    overlay_->removeRipple(this);
}

QPropertyAnimation* MaterialRipple::animate(const QByteArray& property,
                                            const QEasingCurve& easing,
                                            int duration)
{
    QPropertyAnimation* animation = new QPropertyAnimation;
    animation->setTargetObject(this);
    animation->setPropertyName(property);
    animation->setEasingCurve(easing);
    animation->setDuration(duration);
    addAnimation(animation);
    return animation;
}

void MaterialRipple::init()
{
    setOpacityStartValue(0.5);
    setOpacityEndValue(0);
    setRadiusStartValue(0);
    setRadiusEndValue(300);

    brush_.setColor(Qt::black);
    brush_.setStyle(Qt::SolidPattern);

    connect(this, SIGNAL(finished()), this, SLOT(destroy()));
}
