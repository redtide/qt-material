#include "scrollbar_internal.hpp"

#include <QEventTransition>
#include <QPropertyAnimation>

MaterialScrollBarStateMachine::MaterialScrollBarStateMachine(MaterialScrollBar* parent)
    : QStateMachine(parent)
    , m_scrollBar(parent)
    , focusState_(new QState)
    , m_blurState(new QState)
    , opacity_(0)
{
    Q_ASSERT(parent);

    addState(focusState_);
    addState(m_blurState);
    setInitialState(m_blurState);

    QEventTransition* transition;
    transition = new QEventTransition(parent, QEvent::Enter);
    transition->setTargetState(focusState_);
    m_blurState->addTransition(transition);

    transition = new QEventTransition(parent, QEvent::Leave);
    transition->setTargetState(m_blurState);
    focusState_->addTransition(transition);
    focusState_->assignProperty(this, "opacity", 1);
    m_blurState->assignProperty(this, "opacity", 0);

    QPropertyAnimation* animation;
    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(340);
    addDefaultAnimation(animation);
}

MaterialScrollBarStateMachine::~MaterialScrollBarStateMachine()
{
}
