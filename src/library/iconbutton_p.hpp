#ifndef MATERIAL_ICONBUTTON_P_H
#define MATERIAL_ICONBUTTON_P_H

#include <QtGlobal>
#include <QColor>

class MaterialIconButton;
class MaterialRippleOverlay;

class MaterialIconButtonPrivate
{
    Q_DISABLE_COPY(MaterialIconButtonPrivate)
    Q_DECLARE_PUBLIC(MaterialIconButton)

public:
    MaterialIconButtonPrivate(MaterialIconButton* q);
    virtual ~MaterialIconButtonPrivate();

    void init();
    void updateRipple();

    MaterialIconButton    *const q_ptr;
    MaterialRippleOverlay *rippleOverlay;
};

#endif // MATERIAL_ICONBUTTON_P_H
