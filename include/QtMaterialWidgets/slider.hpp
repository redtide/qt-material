#ifndef MATERIAL_SLIDER_H
#define MATERIAL_SLIDER_H

#include "dlimpexp.hpp"

#include <QScopedPointer>
#include <QtWidgets/QAbstractSlider>

#define QT_MATERIAL_SLIDER_MARGIN 10

class MaterialSliderPrivate;

class QT_MATERIAL_EXPORT MaterialSlider : public QAbstractSlider
{
    Q_OBJECT
    Q_PROPERTY(bool   useThemeColors     WRITE setUseThemeColors     READ useThemeColors)
    Q_PROPERTY(QColor thumbColor         WRITE setThumbColor         READ thumbColor)
    Q_PROPERTY(QColor trackColor         WRITE setTrackColor         READ trackColor)
    Q_PROPERTY(QColor disabledColor      WRITE setDisabledColor      READ disabledColor)
    Q_PROPERTY(bool   pageStepMode       WRITE setPageStepMode       READ pageStepMode)
//  Q_PROPERTY(bool   invertedAppearance WRITE setInvertedAppearance READ invertedAppearance)

public:
    explicit MaterialSlider(QWidget* parent = nullptr);
    ~MaterialSlider();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setThumbColor(const QColor &color);
    QColor thumbColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setPageStepMode(bool pageStep);
    bool pageStepMode() const;

    QSize minimumSizeHint() const override;

    void setInvertedAppearance(bool value);

protected:
    void sliderChange(SliderChange change) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void updateThumbOffset();

    const QScopedPointer<MaterialSliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialSlider)
    Q_DECLARE_PRIVATE(MaterialSlider)
};

#endif // MATERIAL_SLIDER_H
