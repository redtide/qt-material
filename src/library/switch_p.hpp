#ifndef MATERIAL_TOGGLE_P_H
#define MATERIAL_TOGGLE_P_H

#include <Qt>
#include <QColor>

QT_BEGIN_NAMESPACE
class QStateMachine;
class QState;
QT_END_NAMESPACE

class MaterialSwitch;
class MaterialSwitchTrack;
class MaterialSwitchThumb;
class MaterialSwitchRippleOverlay;

class MaterialSwitchPrivate
{
    Q_DISABLE_COPY(MaterialSwitchPrivate)
    Q_DECLARE_PUBLIC(MaterialSwitch)

public:
    MaterialSwitchPrivate(MaterialSwitch *q);
    ~MaterialSwitchPrivate();

    void init();
    void setupProperties();

    MaterialSwitch              *const q_ptr;
    MaterialSwitchTrack         *track;
    MaterialSwitchThumb         *thumb;
    MaterialSwitchRippleOverlay *rippleOverlay;
    QStateMachine               *stateMachine;
    QState                      *offState;
    QState                      *onState;
    Qt::Orientation              orientation;
    QColor                       disabledColor;
    QColor                       activeColor;
    QColor                       inactiveColor;
    QColor                       trackColor;

    bool                         useThemeColors;
};

#endif // MATERIAL_TOGGLE_P_H
