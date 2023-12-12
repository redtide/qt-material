#ifndef MATERIAL_RIPPLE_H
#define MATERIAL_RIPPLE_H

#include "dlimpexp.hpp"

#include <QBrush>
#include <QEasingCurve>
#include <QParallelAnimationGroup>
#include <QPoint>
#include <QPropertyAnimation>

class MaterialRippleOverlay;

class QT_MATERIAL_EXPORT MaterialRipple : public QParallelAnimationGroup
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialRipple)

    Q_PROPERTY(qreal radius  READ radius  WRITE setRadius)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit MaterialRipple(const QPoint& center, QObject* parent = nullptr);
    MaterialRipple(const QPoint& center, MaterialRippleOverlay* overlay, QObject* parent = nullptr);
    ~MaterialRipple();

    inline void setOverlay(MaterialRippleOverlay* overlay);

    void setRadius(qreal radius);
    inline qreal radius() const;

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    void setColor(const QColor& color);
    inline QColor color() const;

    void setBrush(const QBrush& brush);
    inline QBrush brush() const;

    inline QPoint center() const;

    inline QPropertyAnimation* radiusAnimation() const;
    inline QPropertyAnimation* opacityAnimation() const;

    inline void setOpacityStartValue(qreal value);
    inline void setOpacityEndValue(qreal value);
    inline void setRadiusStartValue(qreal value);
    inline void setRadiusEndValue(qreal value);
    inline void setDuration(int msecs);

protected Q_SLOTS:
    void destroy();

private:
    QPropertyAnimation* animate(const QByteArray& property,
                                const QEasingCurve& easing = QEasingCurve::OutQuad,
                                int duration = 800);
    void init();

    MaterialRippleOverlay* overlay_;
    QPropertyAnimation* const radiusAnimation_;
    QPropertyAnimation* const opacityAnimation_;
    qreal                     radius_;
    qreal                     opacity_;
    QPoint                    center_;
    QBrush                    brush_;
};

inline void MaterialRipple::setOverlay(MaterialRippleOverlay* overlay)
{
    overlay_ = overlay;
}

inline qreal MaterialRipple::radius() const
{
    return radius_;
}

inline qreal MaterialRipple::opacity() const
{
    return opacity_;
}

inline QColor MaterialRipple::color() const
{
    return brush_.color();
}

inline QBrush MaterialRipple::brush() const
{
    return brush_;
}

inline QPoint MaterialRipple::center() const
{
    return center_;
}

inline QPropertyAnimation* MaterialRipple::radiusAnimation() const
{
    return radiusAnimation_;
}

inline QPropertyAnimation* MaterialRipple::opacityAnimation() const
{
    return opacityAnimation_;
}

inline void MaterialRipple::setOpacityStartValue(qreal value)
{
    opacityAnimation_->setStartValue(value);
}

inline void MaterialRipple::setOpacityEndValue(qreal value)
{
    opacityAnimation_->setEndValue(value);
}

inline void MaterialRipple::setRadiusStartValue(qreal value)
{
    radiusAnimation_->setStartValue(value);
}

inline void MaterialRipple::setRadiusEndValue(qreal value)
{
    radiusAnimation_->setEndValue(value);
}

inline void MaterialRipple::setDuration(int msecs)
{
    radiusAnimation_->setDuration(msecs);
    opacityAnimation_->setDuration(msecs);
}

#endif // MATERIAL_RIPPLE_H
