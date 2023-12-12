#include <QtMaterialWidgets/style.hpp>

#include "palette-helper.hpp"

#include <QStyleFactory>

bool Material::isDark() {
    return material::isDark();
}

void Material::updatePalette(QWidget* widget)
{
    material::updatePalette(widget);
}

MaterialStyle::MaterialStyle()
    : ParentStyle(QStyleFactory::create("fusion"))
{
    setObjectName(QStringLiteral("Material"));
}

QPalette MaterialStyle::standardPalette() const
{
    if (standardPalette_.isBrushSet(QPalette::Disabled, QPalette::Mid))
        return standardPalette_;

    QPalette palette;
#if 0
    QBrush brush;
    namespace md    = material;
    namespace dark  = md::palette_system::dark;
    namespace light = md::palette_system::light;

    if (material::isDark()) {
        brush.setColor(material::fromRgba(dark::on_surface));
        palette.setBrush(QPalette::Window,          md::fromRgba(dark::surface));
        palette.setBrush(QPalette::WindowText,      md::fromRgba(dark::on_surface));
        palette.setBrush(QPalette::Button,          md::fromRgba(dark::primary));
        palette.setBrush(QPalette::ButtonText,      md::fromRgba(dark::on_primary));
        palette.setBrush(QPalette::Highlight,       md::fromRgba(dark::secondary));
        palette.setBrush(QPalette::HighlightedText, md::fromRgba(dark::on_secondary));
        palette.setBrush(QPalette::Link,            md::fromRgba(dark::secondary));
        palette.setBrush(QPalette::LinkVisited,     md::fromRgba(dark::on_secondary));
        palette.setBrush(QPalette::Base,            md::fromRgba(dark::surface));
        palette.setBrush(QPalette::Text,            md::fromRgba(dark::on_surface));
    } else {
        brush.setColor(material::fromRgba(light::on_surface));
        palette.setBrush(QPalette::Window,          md::fromRgba(light::surface));
        palette.setBrush(QPalette::WindowText,      md::fromRgba(light::on_surface));
        palette.setBrush(QPalette::Button,          md::fromRgba(light::primary));
        palette.setBrush(QPalette::ButtonText,      md::fromRgba(light::on_primary));
        palette.setBrush(QPalette::Highlight,       md::fromRgba(light::secondary));
        palette.setBrush(QPalette::HighlightedText, md::fromRgba(light::on_secondary));
        palette.setBrush(QPalette::Link,            md::fromRgba(light::secondary));
        palette.setBrush(QPalette::LinkVisited,     md::fromRgba(light::on_secondary));
        palette.setBrush(QPalette::Base,            md::fromRgba(light::surface));
        palette.setBrush(QPalette::Text,            md::fromRgba(light::on_surface));
    }
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);
#endif
    standardPalette_ = palette;
    return standardPalette_;
}

void MaterialStyle::drawPrimitive(PrimitiveElement    pe,
                                  const QStyleOption* option,
                                  QPainter*           painter,
                                  const QWidget*      widget) const
{
    switch(pe) {
    default:
        ParentStyle::drawPrimitive(pe, option, painter, widget);
        break;
    }
}

void MaterialStyle::drawControl(ControlElement      ce,
                                const QStyleOption* option,
                                QPainter*           painter,
                                const QWidget*      widget) const
{
    switch(ce) {
    default:
        ParentStyle::drawControl(ce, option, painter, widget);
        break;
    }
}

void MaterialStyle::drawComplexControl(ComplexControl             cc,
                                       const QStyleOptionComplex* option,
                                       QPainter*                  painter,
                                       const QWidget*             widget) const
{
    switch(cc) {
    default:
        ParentStyle::drawComplexControl(cc, option, painter, widget);
        break;
    }
}

QStyle::SubControl MaterialStyle::hitTestComplexControl(ComplexControl             cc,
                                                        const QStyleOptionComplex* option,
                                                        const QPoint&              point,
                                                        const QWidget*             widget) const
{
    return ParentStyle::hitTestComplexControl(cc, option, point, widget);
}

QRect MaterialStyle::subControlRect(ComplexControl             cc,
                                    const QStyleOptionComplex* option,
                                    SubControl                 subControl,
                                    const QWidget*             widget) const
{
    return ParentStyle::subControlRect(cc, option, subControl, widget);
}

QRect MaterialStyle::subElementRect(SubElement          se,
                                    const QStyleOption* option,
                                    const QWidget*      widget) const
{
    QRect r = ParentStyle::subElementRect(se, option, widget);
    return r;
}

QSize MaterialStyle::sizeFromContents(ContentsType        contentsType,
                                      const QStyleOption* option,
                                      const QSize&        contentsSize,
                                      const QWidget*      widget) const
{
    return ParentStyle::sizeFromContents(contentsType, option, contentsSize, widget);
}

int MaterialStyle::pixelMetric(PixelMetric         pm,
                               const QStyleOption* option,
                               const QWidget*      widget) const
{
    switch(pm) {
    case PM_SliderControlThickness:
        return 2;
    default:
        return ParentStyle::pixelMetric(pm, option, widget);
    }
    return ParentStyle::pixelMetric(pm, option, widget);
}

int MaterialStyle::styleHint(StyleHint           sh,
                             const QStyleOption* option,
                             const QWidget*      widget,
                             QStyleHintReturn*   styleHintReturn) const
{
    return ParentStyle::styleHint(sh, option, widget, styleHintReturn);
}

QIcon MaterialStyle::standardIcon(StandardPixmap      sp,
                                  const QStyleOption* option,
                                  const QWidget*      widget) const
{
    return ParentStyle::standardIcon(sp, option, widget);
}

QPixmap MaterialStyle::standardPixmap(StandardPixmap      sp,
                                      const QStyleOption* option,
                                      const QWidget*      widget) const
{
    return ParentStyle::standardPixmap(sp, option, widget);
}

QPixmap MaterialStyle::generatedIconPixmap(QIcon::Mode         iconMode,
                                           const QPixmap&      pixmap,
                                           const QStyleOption* option) const
{
    return ParentStyle::generatedIconPixmap(iconMode, pixmap, option);
}

void MaterialStyle::polish(QPalette& palette)
{
    ParentStyle::polish(palette);
}
void MaterialStyle::polish(QApplication* app)
{
    ParentStyle::polish(app);
}

void MaterialStyle::unpolish(QApplication* app)
{
    ParentStyle::unpolish(app);
}

void MaterialStyle::polish(QWidget* widget)
{
    ParentStyle::polish(widget);
}

void MaterialStyle::unpolish(QWidget* widget)
{
    ParentStyle::unpolish(widget);
}
