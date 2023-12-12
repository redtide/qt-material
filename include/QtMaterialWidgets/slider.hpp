#ifndef MATERIAL_SLIDER_H
#define MATERIAL_SLIDER_H

#include "dlimpexp.hpp"

#include <QScopedPointer>
#include <QtWidgets/QAbstractSlider>

class MaterialSliderPrivate;

class QT_MATERIAL_EXPORT MaterialSlider : public QAbstractSlider
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialSlider)
    Q_DECLARE_PRIVATE(MaterialSlider)

    Q_PROPERTY(bool pageStepMode       READ pageStepMode       WRITE setPageStepMode)
//  Q_PROPERTY(bool invertedAppearance READ invertedAppearance WRITE setInvertedAppearance)

public:
    explicit MaterialSlider(QWidget* parent = nullptr);
    ~MaterialSlider();

    void setPageStepMode(bool pageStep);
    bool pageStepMode() const;

    void setInvertedAppearance(bool value);

    QSize minimumSizeHint() const override;

protected:
    bool event(QEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void leaveEvent(QEvent* event) override;

    void sliderChange(SliderChange change) override;

    void updateThumbOffset();

    const QScopedPointer<MaterialSliderPrivate> d_ptr;
};

#endif // MATERIAL_SLIDER_H
