#include "snackbar_internal.hpp"
#include "statetransition.hpp"

#include <QtMaterialWidgets/snackbar.hpp>

#include <QDebug>
#include <QPropertyAnimation>

MaterialSnackbarStateMachine::MaterialSnackbarStateMachine(MaterialSnackbar *parent)
    : QStateMachine(parent),
      m_snackbar(parent)
{
    m_timer.setSingleShot(true);

    QState *hiddenState = new QState;
    QState *visibleState = new QState;
    QState *finalState = new QState;

    addState(hiddenState);
    addState(visibleState);
    addState(finalState);

    setInitialState(hiddenState);

    MaterialStateTransition *transition;

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
            m_snackbar, SLOT(dequeue()));

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this, "offset", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setDuration(300);
    addDefaultAnimation(animation);

    hiddenState->assignProperty(this, "offset", 1);
    visibleState->assignProperty(this, "offset", 0);
    finalState->assignProperty(this, "offset", 1);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(progress()));

    m_snackbar->installEventFilter(this);
}

MaterialSnackbarStateMachine::~MaterialSnackbarStateMachine()
{
}

bool MaterialSnackbarStateMachine::eventFilter(QObject *watched, QEvent *event)
{
    if (QEvent::MouseButtonPress == event->type() && m_snackbar->clickToDismissMode()) {
        progress();
    }
    return QStateMachine::eventFilter(watched, event);
}

void MaterialSnackbarStateMachine::setOffset(qreal offset)
{
    m_offset = offset;
    m_snackbar->update();
}

void MaterialSnackbarStateMachine::progress()
{
    m_timer.stop();
    postEvent(new MaterialStateTransitionEvent(SnackbarHideTransition));
    if (m_snackbar->clickToDismissMode()) {
        m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
}

void MaterialSnackbarStateMachine::snackbarShown()
{
    m_timer.start(m_snackbar->autoHideDuration());
    if (m_snackbar->clickToDismissMode()) {
        m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
}
