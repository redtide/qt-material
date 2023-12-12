#include "statetransition.hpp"

MaterialStateTransition::MaterialStateTransition(MaterialStateTransitionType type)
    : type_(type)
{
}

bool MaterialStateTransition::eventTest(QEvent* event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1))
        return false;

    MaterialStateTransitionEvent* transition =
        static_cast<MaterialStateTransitionEvent* >(event);

    return (type_ == transition->type);
}

void MaterialStateTransition::onTransition(QEvent*)
{
}
