#include "snackbar_internal.hpp"
#include "statetransition.hpp"

#include <QtMaterialWidgets/snackbar.hpp>

#include <QDebug>
#include <QPropertyAnimation>

MaterialSnackbarStateMachine::MaterialSnackbarStateMachine(MaterialSnackbar* parent)
    : QStateMachine(parent),
      snackbar_(parent)
{
    m_timer.setSingleShot(true);

    QState* hiddenState = new QState;
    QState* visibleState = new QState;
    QState* finalState = new QState;

    addState(hiddenState);
    addState(visibleState);
    addState(finalState);

    setInitialState(hiddenState);

    MaterialStateTransition* transition;

    transition = new MaterialStateTransition(SnackbarShowTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new MaterialStateTransition(SnackbarHideTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new MaterialStateTransition(SnackbarHideTransition);
    transition->setTargetState(finalState);
    visibleState->addTransition(transition);

    transition = new MaterialStateTransition(SnackbarWaitTransition);
    transition->setTargetState(hiddenState);
    finalState->addTransition(transition);

    transition = new MaterialStateTransition(SnackbarNextTransition);
    transition->setTargetState(visibleState);
    finalState->addTransition(transition);

    connect(visibleState, SIGNAL(propertiesAssigned()),
            this, SLOT(snackbarShown()));
    connect(finalState, SIGNAL(propertiesAssigned()),
            snackbar_, SLOT(dequeue()));

    QPropertyAnimation* animation;

    animation = new QPropertyAnimation(this, "offset", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setDuration(300);
    addDefaultAnimation(animation);

    hiddenState->assignProperty(this, "offset", 1);
    visibleState->assignProperty(this, "offset", 0);
    finalState->assignProperty(this, "offset", 1);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(progress()));

    snackbar_->installEventFilter(this);
}

MaterialSnackbarStateMachine::~MaterialSnackbarStateMachine()
{
}

bool MaterialSnackbarStateMachine::eventFilter(QObject* watched, QEvent* event)
{
    if (QEvent::MouseButtonPress == event->type() && snackbar_->clickToDismissMode())
        progress();

    return QStateMachine::eventFilter(watched, event);
}

void MaterialSnackbarStateMachine::setOffset(qreal offset)
{
    offset_ = offset;
    snackbar_->update();
}

void MaterialSnackbarStateMachine::progress()
{
    m_timer.stop();
    postEvent(new MaterialStateTransitionEvent(SnackbarHideTransition));
    if (snackbar_->clickToDismissMode())
        snackbar_->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void MaterialSnackbarStateMachine::snackbarShown()
{
    m_timer.start(snackbar_->autoHideDuration());
    if (snackbar_->clickToDismissMode())
        snackbar_->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}
