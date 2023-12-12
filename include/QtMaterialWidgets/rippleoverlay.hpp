#ifndef MATERIAL_RIPPLEOVERLAY_H
#define MATERIAL_RIPPLEOVERLAY_H

#include "overlaywidget.hpp"
#include "dlimpexp.hpp"

#include <QPainterPath>

class MaterialRipple;

class QT_MATERIAL_EXPORT MaterialRippleOverlay : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialRippleOverlay)

public:
    explicit MaterialRippleOverlay(QWidget* parent = nullptr);
    ~MaterialRippleOverlay();

    void addRipple(MaterialRipple* ripple);
    void addRipple(const QPoint& position, qreal radius = 300);

    void removeRipple(MaterialRipple* ripple);

    inline void setClipping(bool enable);
    inline bool hasClipping() const;

    inline void setClipPath(const QPainterPath &path);

protected:
    void paintEvent(QPaintEvent* event) override;

    inline QList<MaterialRipple* > ripples() const;

private:
    void paintRipple(QPainter* painter, MaterialRipple* ripple);

    QList<MaterialRipple*> ripples_;
    QPainterPath clipPath_;
    bool         useClip_;
};

inline void MaterialRippleOverlay::setClipping(bool enable)
{
    useClip_ = enable;
    update();
}

inline bool MaterialRippleOverlay::hasClipping() const
{
    return useClip_;
}

inline void MaterialRippleOverlay::setClipPath(const QPainterPath &path)
{
    clipPath_ = path;
    update();
}

inline QList<MaterialRipple*> MaterialRippleOverlay::ripples() const
{
    return ripples_;
}

#endif // MATERIAL_RIPPLEOVERLAY_H
