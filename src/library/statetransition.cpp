#include "statetransition.hpp"

MaterialStateTransition::MaterialStateTransition(MaterialStateTransitionType type)
    : m_type(type)
{
}

bool MaterialStateTransition::eventTest(QEvent *event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1)) {
        return false;
    }
    MaterialStateTransitionEvent *transition = static_cast<MaterialStateTransitionEvent *>(event);
    return (m_type == transition->type);
}

void MaterialStateTransition::onTransition(QEvent *)
{
}
