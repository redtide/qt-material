#ifndef MATERIAL_TABS_P_H
#define MATERIAL_TABS_P_H

#include <QtMaterialWidgets/defs.hpp>

#include <QtGlobal>
#include <QColor>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
QT_END_NAMESPACE

class MaterialTabs;
class MaterialTabsIndicatorBar;

class MaterialTabsPrivate
{
    Q_DISABLE_COPY(MaterialTabsPrivate)
    Q_DECLARE_PUBLIC(MaterialTabs)

public:
    MaterialTabsPrivate(MaterialTabs *q);
    ~MaterialTabsPrivate();

    void init();

    MaterialTabs*             const q_ptr;
    MaterialTabsIndicatorBar* indicator;
    QHBoxLayout*              tabLayout;
    Material::RippleStyle     rippleStyle;
    int                       currentIndex;
    bool                      isHaloVisible;
};

#endif // MATERIAL_TABS_P_H
