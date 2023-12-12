#include "checkbox_p.hpp"
#include "checkable_internal.hpp"
#include "palette-helper.hpp"

#include <QEvent>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>

MaterialCheckBoxPrivate::MaterialCheckBoxPrivate(MaterialCheckBox *q)
    : MaterialCheckablePrivate(q)
{
}

MaterialCheckBoxPrivate::~MaterialCheckBoxPrivate()
{
}

void MaterialCheckBoxPrivate::init()
{
    Q_Q(MaterialCheckBox);

    checkedState->assignProperty(checkedIcon, "iconSize", 24);
    uncheckedState->assignProperty(checkedIcon, "iconSize", 0);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(300);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(1300);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "color", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "color", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);
}

MaterialCheckBox::MaterialCheckBox(QWidget *parent)
    : MaterialCheckable(*new MaterialCheckBoxPrivate(this), parent)
{
    d_func()->init();
}

MaterialCheckBox::~MaterialCheckBox()
{
}
