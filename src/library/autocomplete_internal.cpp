#include "autocomplete_internal.hpp"

#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QtWidgets/QGraphicsOpacityEffect>

MaterialAutoCompleteStateMachine::MaterialAutoCompleteStateMachine(QWidget* menu)
    : QStateMachine(menu)
    , closedState_(new QState)
    , openState_(new QState)
    , closingState_(new QState)
{
    addState(closedState_);
    addState(openState_);
    addState(closingState_);
    setInitialState(closedState_);

    QSignalTransition* transition;

    transition = new QSignalTransition(this, SIGNAL(shouldOpen()));
    transition->setTargetState(openState_);
    closedState_->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(shouldClose()));
    transition->setTargetState(closedState_);
    openState_->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(shouldFade()));
    transition->setTargetState(closingState_);
    openState_->addTransition(transition);

    closedState_->assignProperty(menu, "visible", false);
    openState_->assignProperty(menu, "visible", true);

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    menu->setGraphicsEffect(effect);

    openState_->assignProperty(effect, "opacity", 1);
    closingState_->assignProperty(effect, "opacity", 0);
    closedState_->assignProperty(effect, "opacity", 0);

    QPropertyAnimation* animation;

    animation = new QPropertyAnimation(effect, "opacity", this);
    animation->setDuration(240);
    addDefaultAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(closedState_);
    closingState_->addTransition(transition);
}

MaterialAutoCompleteStateMachine::~MaterialAutoCompleteStateMachine()
{
}
