#ifndef MATERIAL_TABS_P_H
#define MATERIAL_TABS_P_H

#include <QtMaterialWidgets/defs.hpp>

#include <QtGlobal>
#include <QColor>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
QT_END_NAMESPACE

class MaterialTabs;
class MaterialTabsInkBar;

class MaterialTabsPrivate
{
    Q_DISABLE_COPY(MaterialTabsPrivate)
    Q_DECLARE_PUBLIC(MaterialTabs)

public:
    MaterialTabsPrivate(MaterialTabs *q);
    ~MaterialTabsPrivate();

    void init();

    MaterialTabs         *const q_ptr;
    MaterialTabsInkBar   *inkBar;
    QHBoxLayout          *tabLayout;
    Material::RippleStyle rippleStyle;
    QColor                inkColor;
    int                   currentIndex;

    bool                  showHalo;

    bool                  useThemeColors;
    QColor                backgroundColor;
    QColor                textColor;
};

#endif // MATERIAL_TABS_P_H
