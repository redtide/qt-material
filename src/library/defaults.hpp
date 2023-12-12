#pragma once

#include <QColor>
#include <QFont>
#include <QMargins>
#include <QPoint>
#include <QSize>
#include <QString>

namespace material {
namespace defaults {
namespace global   {
    namespace effect {
        static constexpr qreal   blurRadius { 11 };
        static constexpr QColor  color      { 0, 0, 0, 50 };
        static constexpr QPointF offset     { 0, 3 };
    }
    namespace font {
        static const     QString               family         { QStringLiteral("Roboto") };
        static constexpr qreal                 pointSizeF     { 10.0 };
        static constexpr QFont::Weight         weight         { QFont::Medium };
        static constexpr QFont::Capitalization capitalization { QFont::AllUppercase };
    }
} // namespace global
namespace appbar {
    static constexpr QSize sizeHint { -1, 64 };
}
namespace autocomplete {
    static constexpr QMargins contentsMargins { 0, 0, 0, 0 };
} // namespace appbar
namespace checkable {
    static constexpr qreal iconSize { 24.0 };
    static constexpr qreal opacity  { 1.0 };
}
namespace dialog   {
    namespace effect   {
        static constexpr qreal   blurRadius { 7 };
        static constexpr QColor  color      { 0, 0, 0, 75 };
        static constexpr QPointF offset     { 0, 2 };
    }
    static constexpr int minimumWidth { 400 };
} // namespace dialog
namespace raisedbutton {
    namespace effect   {
        static constexpr qreal   blurRadius { 64 };
        static constexpr QColor  color      { 0, 0, 0, 200 };
        static constexpr QPointF offset     { 0, 13 };
    }
} // namespace raisedbutton
namespace snackbar {
    static constexpr int autoHideDuration { 3000 };
} // namespace snackbar
} // namespace defaults
} // namespace material
