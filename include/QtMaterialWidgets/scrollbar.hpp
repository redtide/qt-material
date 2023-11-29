#ifndef MATERIAL_SCROLLBAR_H
#define MATERIAL_SCROLLBAR_H

#include "dlimpexp.hpp"

#include <QtWidgets/QScrollBar>

class MaterialScrollBarPrivate;

class QT_MATERIAL_EXPORT MaterialScrollBar : public QScrollBar
{
    Q_OBJECT
    Q_PROPERTY(bool   useThemeColors  WRITE setUseThemeColors  READ useThemeColors)
    Q_PROPERTY(QColor canvasColor     WRITE setCanvasColor     READ canvasColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor sliderColor     WRITE setSliderColor     READ sliderColor)
    Q_PROPERTY(bool   hideOnMouseOut  WRITE setHideOnMouseOut  READ hideOnMouseOut)

public:
    explicit MaterialScrollBar(QWidget* parent = nullptr);
    ~MaterialScrollBar();

    QSize sizeHint() const override;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setCanvasColor(const QColor &color);
    QColor canvasColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSliderColor(const QColor &color);
    QColor sliderColor() const;

    void setHideOnMouseOut(bool value);
    bool hideOnMouseOut() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialScrollBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialScrollBar)
    Q_DECLARE_PRIVATE(MaterialScrollBar)
};

#endif // MATERIAL_SCROLLBAR_H
