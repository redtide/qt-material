#pragma once

#include "palette-system.hpp"

#include <QtGlobal>

#if 0 // QT_VERSION >= 0x060500
#include <QGuiApplication>
#include <QStyleHints>
#endif
#include <QColor>
#include <QWidget>

namespace material {

static QColor fromRgba(rgba color)
{
    return QColor((color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
}

#if QT_VERSION < 0x060000
    using color_comp_t = qreal; // double
    static constexpr qreal color_comp_min { 0.0 };
    static constexpr qreal color_comp_max { 1.0 };
#else
    using color_comp_t = float;
    static constexpr float color_comp_min { 0.0f };
    static constexpr float color_comp_max { 1.0f };
#endif
static constexpr std::array<color_comp_t, 3> ry = { 0.2126, 0.7152, 0.0722 };

static constexpr color_comp_t relative_luminance(color_comp_t r, color_comp_t g, color_comp_t b)
{
    return ry[0] * r + ry[1] * g + ry[2] * b;
}

static bool isDark()
{
#if 0 // QT_VERSION >= 0x060500
    // FIXME: This doesn't work with some styles
    Qt::ColorScheme colorScheme = QGuiApplication::styleHints()->colorScheme();
    bool isdark = (colorScheme == Qt::ColorScheme::Dark);
#elif 0
    // FIXME: This probably is not reliable for all cases, just a momentary "works for me" case, see
    // https://stackoverflow.com/questions/75457687
    const QPalette defaultPalette;
    bool isdark = (defaultPalette.color(QPalette::ButtonText).lightness()
         > defaultPalette.color(QPalette::Button).lightness());
#else
    const QPalette palette;
    QColor color = palette.color(QPalette::Button);
    color_comp_t lightness = relative_luminance(color.redF(), color.greenF(), color.blueF());
    // https://vishald.com/blog/is-a-color-dark/#rec-601-luminance-function
    bool isdark = (lightness < 0.55);
#endif
    return isdark;
}

static void updatePalette(QWidget* widget, bool simple = false)
{
    QBrush brush;
    QPalette palette;
    namespace md    = material;
    namespace dark  = md::palette_system::dark;
    namespace light = md::palette_system::light;

    // TODO: Check Material 3 documentation for a precise implementation
    if (md::isDark()) {
        brush.setColor(material::fromRgba(dark::on_surface));
        palette.setBrush(QPalette::Window,          md::fromRgba(dark::surface));
        palette.setBrush(QPalette::WindowText,      md::fromRgba(dark::on_surface));
        if (simple) {
            palette.setBrush(QPalette::Button,      md::fromRgba(dark::surface));
            palette.setBrush(QPalette::ButtonText,  md::fromRgba(dark::on_surface));
        } else {
            palette.setBrush(QPalette::Button,      md::fromRgba(dark::primary));
            palette.setBrush(QPalette::ButtonText,  md::fromRgba(dark::on_primary));
        }
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
        if (simple) {
            palette.setBrush(QPalette::Button,      md::fromRgba(light::surface));
            palette.setBrush(QPalette::ButtonText,  md::fromRgba(light::on_surface));
        } else {
            palette.setBrush(QPalette::Button,          md::fromRgba(light::primary));
            palette.setBrush(QPalette::ButtonText,      md::fromRgba(light::on_primary));
        }
        palette.setBrush(QPalette::Highlight,       md::fromRgba(light::secondary));
        palette.setBrush(QPalette::HighlightedText, md::fromRgba(light::on_secondary));
        palette.setBrush(QPalette::Link,            md::fromRgba(light::secondary));
        palette.setBrush(QPalette::LinkVisited,     md::fromRgba(light::on_secondary));
        palette.setBrush(QPalette::Base,            md::fromRgba(light::surface));
        palette.setBrush(QPalette::Text,            md::fromRgba(light::on_surface));
    }
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Text,       brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base,       brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button,     brush);
    palette.setBrush(QPalette::Disabled, QPalette::Mid,        brush);

    widget->setPalette(palette);
}
} // namespace material
