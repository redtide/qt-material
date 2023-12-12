#include "flatbutton_internal.hpp"
#include "statetransition.hpp"

#include "QtMaterialWidgets/flatbutton.hpp"

#include <QEventTransition>
#include <QFocusEvent>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

MaterialFlatButtonStateMachine::MaterialFlatButtonStateMachine(MaterialFlatButton* parent)
    : QStateMachine(parent)
    , button_(parent)
    , topLevelState_(new QState(QState::ParallelStates))
    , configState_(new QState(topLevelState_))
    , checkableState_(new QState(topLevelState_))
    , checkedState_(new QState(checkableState_))
    , uncheckedState_(new QState(checkableState_))
    , neutralState_(new QState(configState_))
    , neutralFocusedState_(new QState(configState_))
    , hoveredState_(new QState(configState_))
    , hoveredFocusedState_(new QState(configState_))
    , pressedState_(new QState(configState_))
    , haloAnimation_(new QSequentialAnimationGroup(this))
    , overlayOpacity_(0)
    , checkedOverlayProgress_(parent->isChecked() ? 1 : 0)
    , haloOpacity_(0)
    , haloSize_(0.8)
    , haloScaleFactor_(1)
    , wasChecked_(false)
{
    Q_ASSERT(parent);

    parent->installEventFilter(this);

    configState_->setInitialState(neutralState_);
    addState(topLevelState_);
    setInitialState(topLevelState_);

    checkableState_->setInitialState(parent->isChecked() ? checkedState_
                                                          : uncheckedState_);
    MaterialStateTransition* transition;
    QPropertyAnimation* animation;

    transition = new MaterialStateTransition(FlatButtonCheckedTransition);
    transition->setTargetState(checkedState_);
    uncheckedState_->addTransition(transition);

    animation = new QPropertyAnimation(this, "checkedOverlayProgress", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    transition = new MaterialStateTransition(FlatButtonUncheckedTransition);
    transition->setTargetState(uncheckedState_);
    checkedState_->addTransition(transition);

    animation = new QPropertyAnimation(this, "checkedOverlayProgress", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    addTransition(button_, QEvent::FocusIn, neutralState_, neutralFocusedState_);
    addTransition(button_, QEvent::FocusOut, neutralFocusedState_, neutralState_);
    addTransition(button_, QEvent::Enter, neutralState_, hoveredState_);
    addTransition(button_, QEvent::Leave, hoveredState_, neutralState_);
    addTransition(button_, QEvent::Enter, neutralFocusedState_, hoveredFocusedState_);
    addTransition(button_, QEvent::Leave, hoveredFocusedState_, neutralFocusedState_);
    addTransition(button_, QEvent::FocusIn, hoveredState_, hoveredFocusedState_);
    addTransition(button_, QEvent::FocusOut, hoveredFocusedState_, hoveredState_);

    transition = new MaterialStateTransition(FlatButtonPressedTransition);
    transition->setTargetState(pressedState_);
    hoveredState_->addTransition(transition);

    addTransition(button_, QEvent::Leave, pressedState_, neutralFocusedState_);
    addTransition(button_, QEvent::FocusOut, pressedState_, hoveredState_);

    neutralState_->assignProperty(this, "haloSize", 0);
    neutralFocusedState_->assignProperty(this, "haloSize", 0.7);
    hoveredState_->assignProperty(this, "haloSize", 0);
    pressedState_->assignProperty(this, "haloSize", 4);
    hoveredFocusedState_->assignProperty(this, "haloSize", 0.7);

    QPropertyAnimation* grow = new QPropertyAnimation(this);
    QPropertyAnimation* shrink = new QPropertyAnimation(this);

    grow->setTargetObject(this);
    grow->setPropertyName("haloScaleFactor");
    grow->setStartValue(0.56);
    grow->setEndValue(0.63);
    grow->setEasingCurve(QEasingCurve::InOutSine);
    grow->setDuration(840);

    shrink->setTargetObject(this);
    shrink->setPropertyName("haloScaleFactor");
    shrink->setStartValue(0.63);
    shrink->setEndValue(0.56);
    shrink->setEasingCurve(QEasingCurve::InOutSine);
    shrink->setDuration(840);

    haloAnimation_->addAnimation(grow);
    haloAnimation_->addAnimation(shrink);
    haloAnimation_->setLoopCount(-1);
}

MaterialFlatButtonStateMachine::~MaterialFlatButtonStateMachine()
{
}

void MaterialFlatButtonStateMachine::setOverlayOpacity(qreal opacity)
{
    overlayOpacity_ = opacity;
    button_->update();
}

void MaterialFlatButtonStateMachine::setCheckedOverlayProgress(qreal progress)
{
    checkedOverlayProgress_ = progress;
    button_->update();
}

void MaterialFlatButtonStateMachine::setHaloOpacity(qreal opacity)
{
    haloOpacity_ = opacity;
    button_->update();
}

void MaterialFlatButtonStateMachine::setHaloSize(qreal size)
{
    haloSize_ = size;
    button_->update();
}

void MaterialFlatButtonStateMachine::setHaloScaleFactor(qreal factor)
{
    haloScaleFactor_ = factor;
    button_->update();
}

void MaterialFlatButtonStateMachine::startAnimations()
{
    haloAnimation_->start();
    start();
}

void MaterialFlatButtonStateMachine::setupProperties()
{
    const qreal baseOpacity = button_->baseOpacity();

    neutralState_->assignProperty(this, "overlayOpacity", 0);
    neutralState_->assignProperty(this, "haloOpacity", 0);
    neutralFocusedState_->assignProperty(this, "overlayOpacity", 0);
    neutralFocusedState_->assignProperty(this, "haloOpacity", baseOpacity);
    hoveredState_->assignProperty(this, "overlayOpacity", baseOpacity);
    hoveredState_->assignProperty(this, "haloOpacity", 0);
    hoveredFocusedState_->assignProperty(this, "overlayOpacity", baseOpacity);
    hoveredFocusedState_->assignProperty(this, "haloOpacity", baseOpacity);
    pressedState_->assignProperty(this, "overlayOpacity", baseOpacity);
    pressedState_->assignProperty(this, "haloOpacity", 0);
    checkedState_->assignProperty(this, "checkedOverlayProgress", 1);
    uncheckedState_->assignProperty(this, "checkedOverlayProgress", 0);

    button_->update();
}

void MaterialFlatButtonStateMachine::updateCheckedStatus()
{
    const bool checked = button_->isChecked();
    if (wasChecked_ != checked) {
        wasChecked_ = checked;
        if (checked)
            postEvent(new MaterialStateTransitionEvent(FlatButtonCheckedTransition));
        else
            postEvent(new MaterialStateTransitionEvent(FlatButtonUncheckedTransition));
    }
}

bool MaterialFlatButtonStateMachine::eventFilter(QObject* watched,
                                                   QEvent*  event)
{
    if (QEvent::FocusIn == event->type()) {
        QFocusEvent* focusEvent = static_cast<QFocusEvent* >(event);
        if (focusEvent && Qt::MouseFocusReason == focusEvent->reason()) {
            postEvent(new MaterialStateTransitionEvent(FlatButtonPressedTransition));
            return true;
        }
    }
    return QStateMachine::eventFilter(watched, event);
}

void MaterialFlatButtonStateMachine::addTransition(QObject* object,
                                                     QEvent::Type eventType,
                                                     QState* fromState,
                                                     QState* toState)
{
    addTransition(new QEventTransition(object, eventType), fromState, toState);
}

void MaterialFlatButtonStateMachine::addTransition(QAbstractTransition* transition,
                                                     QState* fromState,
                                                     QState* toState)
{
    transition->setTargetState(toState);

    QPropertyAnimation* animation;

    animation = new QPropertyAnimation(this, "overlayOpacity", this);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "haloOpacity", this);
    animation->setDuration(170);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "haloSize", this);
    animation->setDuration(350);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    transition->addAnimation(animation);

    fromState->addTransition(transition);
}
