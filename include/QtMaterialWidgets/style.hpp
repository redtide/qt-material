#pragma once

#include "dlimpexp.hpp"

#include <QProxyStyle>

namespace Material {
extern bool isDark();
extern void updatePalette(QWidget* widget);
}

using ParentStyle = QProxyStyle;

class QT_MATERIAL_EXPORT MaterialStyle : public ParentStyle
{
    Q_OBJECT

public:
    MaterialStyle();

    QPalette standardPalette() const override;

    void drawPrimitive(PrimitiveElement    pe,
                       const QStyleOption* option,
                       QPainter*           painter,
                       const QWidget*      widget = nullptr) const override;

    void drawControl(ControlElement      ce,
                     const QStyleOption* option,
                     QPainter*           painter,
                     const QWidget*      widget = nullptr) const override;

    void drawComplexControl(ComplexControl             cc,
                            const QStyleOptionComplex* option,
                            QPainter*                  painter,
                            const QWidget*             widget = nullptr) const override;

    SubControl hitTestComplexControl(ComplexControl             cc,
                                     const QStyleOptionComplex* option,
                                     const QPoint&              point,
                                     const QWidget*             widget = nullptr) const override;

    QRect subControlRect(ComplexControl             cc,
                         const QStyleOptionComplex* option,
                         SubControl                 subControl,
                         const QWidget*             widget = nullptr) const override;

    QRect subElementRect(SubElement          se,
                         const QStyleOption* option,
                         const QWidget*      widget = nullptr) const override;

    QSize sizeFromContents(ContentsType        contentsType,
                           const QStyleOption* option,
                           const QSize&        contentsSize,
                           const QWidget*      widget = nullptr) const override;

    int pixelMetric(PixelMetric         pm,
                    const QStyleOption* option = nullptr,
                    const QWidget*      widget = nullptr) const override;

    int styleHint(StyleHint           sh,
                  const QStyleOption* option = nullptr,
                  const QWidget*      widget = nullptr,
                  QStyleHintReturn*   styleHintReturn = nullptr) const override;

    QIcon standardIcon(StandardPixmap      sp,
                       const QStyleOption* option = nullptr,
                       const QWidget*      widget = nullptr) const override;

    QPixmap standardPixmap(StandardPixmap      sp,
                           const QStyleOption* option = nullptr,
                           const QWidget*      widget = nullptr) const override;

    QPixmap generatedIconPixmap(QIcon::Mode         iconMode,
                                const QPixmap&      pixmap,
                                const QStyleOption* option) const override;
    void polish(QPalette& palette) override;
    void polish(QApplication* app) override;
    void unpolish(QApplication *app) override;

    void polish(QWidget* widget) override;
    void unpolish(QWidget* widget) override;

private:
    mutable QPalette standardPalette_;
};
