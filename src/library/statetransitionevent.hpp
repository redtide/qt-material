#ifndef MATERIAL_STATETRANSITIONEVENT_H
#define MATERIAL_STATETRANSITIONEVENT_H

#include <QEvent>

enum MaterialStateTransitionType {
    // Snackbar
    SnackbarShowTransition = 1,
    SnackbarHideTransition,
    SnackbarWaitTransition,
    SnackbarNextTransition,
    // FlatButton
    FlatButtonPressedTransition,
    FlatButtonCheckedTransition,
    FlatButtonUncheckedTransition,
    // CollapsibleMenu
    CollapsibleMenuExpand,
    CollapsibleMenuCollapse,
    // Slider
    SliderChangedToMinimum,
    SliderChangedFromMinimum,
    SliderNoFocusMouseEnter,
    SliderNoFocusMouseLeave,
    // Dialog
    DialogShowTransition,
    DialogHideTransition,
    //
    MaxTransitionType = 65535
};

struct MaterialStateTransitionEvent : public QEvent
{
    MaterialStateTransitionEvent(MaterialStateTransitionType type)
        : QEvent(QEvent::Type(QEvent::User + 1)),
          type(type)
    {
    }

    MaterialStateTransitionType type;
};

#endif // MATERIAL_STATETRANSITIONEVENT_H
