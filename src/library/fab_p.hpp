#ifndef MATERIAL_FAB_P_H
#define MATERIAL_FAB_P_H

#include "raisedbutton_p.hpp"

#include <QtMaterialWidgets/fab.hpp>

#include <QRect>

class MaterialFloatingActionButton;

class MaterialFloatingActionButtonPrivate : public MaterialRaisedButtonPrivate
{
    Q_DISABLE_COPY(MaterialFloatingActionButtonPrivate)
    Q_DECLARE_PUBLIC(MaterialFloatingActionButton)

public:
    enum {
        DefaultDiameter = 56,
        MiniDiameter = 40
    };

    enum {
        DefaultIconSize = 24,
        MiniIconSize = 18
    };

    MaterialFloatingActionButtonPrivate(MaterialFloatingActionButton *q);
    ~MaterialFloatingActionButtonPrivate();

    void init();
    QRect fabGeometry() const;
    void setupProperties();

    inline int diameter() const;
    inline int iconSize() const;

    Qt::Corner corner;
    bool       mini;
    int        offsX;
    int        offsY;
};

inline int MaterialFloatingActionButtonPrivate::diameter() const
{
    return mini ? MiniDiameter : DefaultDiameter;
}

inline int MaterialFloatingActionButtonPrivate::iconSize() const
{
    return mini ? MiniIconSize : DefaultIconSize;
}

#endif // MATERIAL_FAB_P_H
