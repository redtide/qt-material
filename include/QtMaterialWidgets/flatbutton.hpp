#ifndef MATERIAL_FLATBUTTON_H
#define MATERIAL_FLATBUTTON_H

#include "defs.hpp"
#include "dlimpexp.hpp"

#include <QScopedPointer>
#include <QtWidgets/QPushButton>

class MaterialFlatButtonPrivate;

class QT_MATERIAL_EXPORT MaterialFlatButton : public QPushButton
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialFlatButton)
    Q_DECLARE_PRIVATE(MaterialFlatButton)

    Q_PROPERTY(bool                          isHaloVisible  READ isHaloVisible  WRITE setHaloVisible)
    Q_PROPERTY(qreal                         baseOpacity    READ baseOpacity    WRITE setBaseOpacity)
    Q_PROPERTY(qreal                         cornerRadius   READ cornerRadius   WRITE setCornerRadius)
    Q_PROPERTY(qreal                         fontSize       READ fontSize       WRITE setFontSize)
    Q_PROPERTY(Qt::BGMode                    backgroundMode READ backgroundMode WRITE setBackgroundMode)
    Q_PROPERTY(Material::Role                role           READ role           WRITE setRole)
    Q_PROPERTY(Material::OverlayStyle        overlayStyle   READ overlayStyle   WRITE setOverlayStyle)
    Q_PROPERTY(Material::RippleStyle         rippleStyle    READ rippleStyle    WRITE setRippleStyle)
    Q_PROPERTY(Material::ButtonIconPlacement iconPlacement  READ iconPlacement  WRITE setIconPlacement)

public:
    explicit MaterialFlatButton(QWidget* parent = nullptr,
                                Material::ButtonPreset preset = Material::FlatPreset);
    explicit MaterialFlatButton(const QString& text,
                                QWidget* parent = nullptr,
                                Material::ButtonPreset preset = Material::FlatPreset);
    MaterialFlatButton(const QString& text,
                       Material::Role role,
                       QWidget* parent = nullptr,
                       Material::ButtonPreset preset = Material::FlatPreset);
    ~MaterialFlatButton();

    void applyPreset(Material::ButtonPreset preset);

    void setRole(Material::Role role);
    Material::Role role() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setHaloVisible(bool visible);
    bool isHaloVisible() const;

    void setOverlayStyle(Material::OverlayStyle style);
    Material::OverlayStyle overlayStyle() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    void setIconPlacement(Material::ButtonIconPlacement placement);
    Material::ButtonIconPlacement iconPlacement() const;

    void setCornerRadius(qreal radius);
    qreal cornerRadius() const;

    void setBackgroundMode(Qt::BGMode mode);
    Qt::BGMode backgroundMode() const;

    void setBaseOpacity(qreal opacity);
    qreal baseOpacity() const;

    void setCheckable(bool value);

    void setHasFixedRippleRadius(bool value);
    bool hasFixedRippleRadius() const;

    void setFixedRippleRadius(qreal radius);

    void setTextAlignment(Qt::Alignment alignment);
    Qt::Alignment textAlignment() const;

    QSize sizeHint() const override;

protected:
    MaterialFlatButton(MaterialFlatButtonPrivate& d,
                       QWidget* parent = nullptr,
                       Material::ButtonPreset preset = Material::FlatPreset);

    void checkStateSet() override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;

    virtual void paintBackground(QPainter* painter);
    virtual void paintHalo(QPainter* painter);
    virtual void paintForeground(QPainter* painter);

    virtual void updateClipPath();

    const QScopedPointer<MaterialFlatButtonPrivate> d_ptr;
};

#endif // MATERIAL_FLATBUTTON_H
