#include "radiobutton_p.hpp"
#include "checkable_internal.hpp"

#include <QtMaterialWidgets/radiobutton.hpp>

#include <QColor>
#include <QPropertyAnimation>
#include <QState>
#include <QStateMachine>

MaterialRadioButtonPrivate::MaterialRadioButtonPrivate(MaterialRadioButton* q)
    : MaterialCheckablePrivate(q)
{
}

MaterialRadioButtonPrivate::~MaterialRadioButtonPrivate()
{
}

void MaterialRadioButtonPrivate::init()
{
    Q_Q(MaterialRadioButton);

    q->setAutoExclusive(true);

    q->setCheckedIcon(QIcon(":/icons/toggle/svg/production/ic_radio_button_checked_24px.svg"));
    q->setUncheckedIcon(QIcon(":/icons/toggle/svg/production/ic_radio_button_unchecked_24px.svg"));

    uncheckedState->assignProperty(checkedIcon, "iconSize", 0);
    uncheckedState->assignProperty(uncheckedIcon, "iconSize", 24);

    disabledUncheckedState->assignProperty(checkedIcon, "iconSize", 0);
    disabledUncheckedState->assignProperty(uncheckedIcon, "iconSize", 24);

    checkedState->assignProperty(uncheckedIcon, "iconSize", 0);
    checkedState->assignProperty(checkedIcon, "iconSize", 24);

    disabledCheckedState->assignProperty(uncheckedIcon, "iconSize", 0);
    disabledCheckedState->assignProperty(checkedIcon, "iconSize", 24);

    uncheckedState->assignProperty(checkedIcon, "opacity", 0);
    uncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    checkedState->assignProperty(uncheckedIcon, "opacity", 0);
    checkedState->assignProperty(checkedIcon, "opacity", 1);

    checkedIcon->setIconSize(0);

    checkedState->assignProperty(checkedIcon, "color", q->palette().color(QPalette::ButtonText));
    checkedState->assignProperty(uncheckedIcon, "color", q->palette().color(QPalette::Button));
    uncheckedState->assignProperty(uncheckedIcon, "color", q->palette().color(QPalette::Button));

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(250);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "iconSize", q);
    animation->setDuration(250);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(250);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(250);
    stateMachine->addDefaultAnimation(animation);
}

MaterialRadioButton::MaterialRadioButton(QWidget *parent)
    : MaterialCheckable(*new MaterialRadioButtonPrivate(this), parent)
{
    d_func()->init();
}

MaterialRadioButton::~MaterialRadioButton()
{
}

void MaterialRadioButton::setupProperties()
{
    MaterialCheckable::setupProperties();

    Q_D(MaterialRadioButton);

    d->checkedState->assignProperty(d->checkedIcon, "color", palette().color(QPalette::ButtonText));
    d->checkedState->assignProperty(d->uncheckedIcon, "color", palette().color(QPalette::Button));
    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", palette().color(QPalette::Button));
}
