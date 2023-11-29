#ifndef MATERIAL_RAISEDBUTTON_P_H
#define MATERIAL_RAISEDBUTTON_P_H

#include "flatbutton_p.hpp"

#include <QtMaterialWidgets/raisedbutton.hpp>

QT_BEGIN_NAMESPACE
class QStateMachine;
class QState;
class QGraphicsDropShadowEffect;
QT_END_NAMESPACE

class MaterialRaisedButtonPrivate : public MaterialFlatButtonPrivate
{
    Q_DISABLE_COPY(MaterialRaisedButtonPrivate)
    Q_DECLARE_PUBLIC(MaterialRaisedButton)

public:
    MaterialRaisedButtonPrivate(MaterialRaisedButton *q);
    ~MaterialRaisedButtonPrivate();

    void init();

    QStateMachine             *shadowStateMachine;
    QState                    *normalState;
    QState                    *pressedState;
    QGraphicsDropShadowEffect *effect;
};

#endif // MATERIAL_RAISEDBUTTON_P_H
