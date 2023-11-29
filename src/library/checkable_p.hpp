#ifndef MATERIAL_CHECKABLE_P_H
#define MATERIAL_CHECKABLE_P_H

#include <QtMaterialWidgets/checkable.hpp>

#include <QtGlobal>
#include <QColor>

QT_BEGIN_NAMESPACE
class QStateMachine;
class QState;
class QSignalTransition;
QT_END_NAMESPACE

class MaterialRippleOverlay;
class MaterialCheckableIcon;

class MaterialCheckablePrivate
{
    Q_DECLARE_PUBLIC(MaterialCheckable)

public:
    MaterialCheckablePrivate(MaterialCheckable *q);
    virtual ~MaterialCheckablePrivate();

    void init();

    MaterialCheckable                 *const q_ptr;
    MaterialRippleOverlay             *rippleOverlay;
    MaterialCheckableIcon             *checkedIcon;
    MaterialCheckableIcon             *uncheckedIcon;
    QStateMachine                     *stateMachine;
    QState                            *uncheckedState;
    QState                            *checkedState;
    QState                            *disabledUncheckedState;
    QState                            *disabledCheckedState;
    QSignalTransition                 *uncheckedTransition;
    QSignalTransition                 *checkedTransition;
    MaterialCheckable::LabelPosition  labelPosition;
    QColor                            checkedColor;
    QColor                            uncheckedColor;
    QColor                            disabledColor;

    bool                              useThemeColors;
    QColor                            textColor;
};

#endif // MATERIAL_CHECKABLE_P_H
