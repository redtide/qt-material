#ifndef MATERIAL_FLATBUTTON_P_H
#define MATERIAL_FLATBUTTON_P_H

#include <QtMaterialWidgets/defs.hpp>

#include <QtGlobal>
#include <QColor>

class MaterialFlatButton;
class MaterialRippleOverlay;
class MaterialFlatButtonStateMachine;

class MaterialFlatButtonPrivate
{
    Q_DISABLE_COPY(MaterialFlatButtonPrivate)
    Q_DECLARE_PUBLIC(MaterialFlatButton)

public:
    MaterialFlatButtonPrivate(MaterialFlatButton *q);
    virtual ~MaterialFlatButtonPrivate();

    void init();

    MaterialFlatButton             *const q_ptr;
    MaterialRippleOverlay          *rippleOverlay;
    MaterialFlatButtonStateMachine *stateMachine;
    Material::Role                 role;
    Material::RippleStyle          rippleStyle;
    Material::ButtonIconPlacement  iconPlacement;
    Material::OverlayStyle         overlayStyle;
    Qt::BGMode                     bgMode;
    Qt::Alignment                  textAlignment;
    QColor                         overlayColor;
    QColor                         disabledColor;
    QColor                         disabledBackgroundColor;
    qreal                          fixedRippleRadius;
    qreal                          cornerRadius;
    qreal                          baseOpacity;
    qreal                          fontSize;
    bool                           useFixedRippleRadius;

    bool                           haloVisible;

    bool                           useThemeColors;
    QColor                         backgroundColor;
    QColor                         foregroundColor;
};

#endif // MATERIAL_FLATBUTTON_P_H
