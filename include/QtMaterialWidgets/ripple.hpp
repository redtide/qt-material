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

    Q_PROPERTY(qreal radius WRITE setRadius READ radius)
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit MaterialRipple(const QPoint &center, QObject* parent = nullptr);
    MaterialRipple(const QPoint &center, MaterialRippleOverlay *overlay, QObject* parent = nullptr);
    ~MaterialRipple();

    inline void setOverlay(MaterialRippleOverlay *overlay);

    void setRadius(qreal radius);
    inline qreal radius() const;

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    void setColor(const QColor &color);
    inline QColor color() const;

    void setBrush(const QBrush &brush);
    inline QBrush brush() const;

    inline QPoint center() const;

    inline QPropertyAnimation *radiusAnimation() const;
    inline QPropertyAnimation *opacityAnimation() const;

    inline void setOpacityStartValue(qreal value);
    inline void setOpacityEndValue(qreal value);
    inline void setRadiusStartValue(qreal value);
    inline void setRadiusEndValue(qreal value);
    inline void setDuration(int msecs);

protected Q_SLOTS:
    void destroy();

private:
    Q_DISABLE_COPY(MaterialRipple)

    QPropertyAnimation *animate(const QByteArray &property,
                                const QEasingCurve &easing = QEasingCurve::OutQuad,
                                int duration = 800);

    void init();

    MaterialRippleOverlay  *m_overlay;
    QPropertyAnimation *const m_radiusAnimation;
    QPropertyAnimation *const m_opacityAnimation;
    qreal                     m_radius;
    qreal                     m_opacity;
    QPoint                    m_center;
    QBrush                    m_brush;
};

inline void MaterialRipple::setOverlay(MaterialRippleOverlay *overlay)
{
    m_overlay = overlay;
}

inline qreal MaterialRipple::radius() const
{
    return m_radius;
}

inline qreal MaterialRipple::opacity() const
{
    return m_opacity;
}

inline QColor MaterialRipple::color() const
{
    return m_brush.color();
}

inline QBrush MaterialRipple::brush() const
{
    return m_brush;
}

inline QPoint MaterialRipple::center() const
{
    return m_center;
}

inline QPropertyAnimation *MaterialRipple::radiusAnimation() const
{
    return m_radiusAnimation;
}

inline QPropertyAnimation *MaterialRipple::opacityAnimation() const
{
    return m_opacityAnimation;
}

inline void MaterialRipple::setOpacityStartValue(qreal value)
{
    m_opacityAnimation->setStartValue(value);
}

inline void MaterialRipple::setOpacityEndValue(qreal value)
{
    m_opacityAnimation->setEndValue(value);
}

inline void MaterialRipple::setRadiusStartValue(qreal value)
{
    m_radiusAnimation->setStartValue(value);
}

inline void MaterialRipple::setRadiusEndValue(qreal value)
{
    m_radiusAnimation->setEndValue(value);
}

inline void MaterialRipple::setDuration(int msecs)
{
    m_radiusAnimation->setDuration(msecs);
    m_opacityAnimation->setDuration(msecs);
}

#endif // MATERIAL_RIPPLE_H
