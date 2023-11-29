#ifndef MATERIAL_RIPPLEOVERLAY_H
#define MATERIAL_RIPPLEOVERLAY_H

#include "overlaywidget.hpp"
#include "dlimpexp.hpp"

#include <QPainterPath>

class MaterialRipple;

class QT_MATERIAL_EXPORT MaterialRippleOverlay : public MaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit MaterialRippleOverlay(QWidget* parent = nullptr);
    ~MaterialRippleOverlay();

    void addRipple(MaterialRipple *ripple);
    void addRipple(const QPoint &position, qreal radius = 300);

    void removeRipple(MaterialRipple *ripple);

    inline void setClipping(bool enable);
    inline bool hasClipping() const;

    inline void setClipPath(const QPainterPath &path);

protected:
    void paintEvent(QPaintEvent *event) override;

    inline QList<MaterialRipple *> ripples() const;

private:
    Q_DISABLE_COPY(MaterialRippleOverlay)

    void paintRipple(QPainter *painter, MaterialRipple *ripple);

    QList<MaterialRipple *> m_ripples;
    QPainterPath              m_clipPath;
    bool                      m_useClip;
};

inline void MaterialRippleOverlay::setClipping(bool enable)
{
    m_useClip = enable;
    update();
}

inline bool MaterialRippleOverlay::hasClipping() const
{
    return m_useClip;
}

inline void MaterialRippleOverlay::setClipPath(const QPainterPath &path)
{
    m_clipPath = path;
    update();
}

inline QList<MaterialRipple *> MaterialRippleOverlay::ripples() const
{
    return m_ripples;
}

#endif // MATERIAL_RIPPLEOVERLAY_H
