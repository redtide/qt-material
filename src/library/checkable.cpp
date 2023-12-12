#include "checkable_p.hpp"
#include "checkable_internal.hpp"

#include <QtMaterialWidgets/rippleoverlay.hpp>
#include <QtMaterialWidgets/ripple.hpp>
#include "palette-helper.hpp"

#include <QCoreApplication>
#include <QColor>
#include <QEvent>
#include <QEventTransition>
#include <QPainter>
#include <QSignalTransition>
#include <QStateMachine>

MaterialCheckablePrivate::MaterialCheckablePrivate(MaterialCheckable* q)
    : q_ptr(q)
{
}

MaterialCheckablePrivate::~MaterialCheckablePrivate()
{
}

void MaterialCheckablePrivate::init()
{
    Q_Q(MaterialCheckable);

    rippleOverlay          = new MaterialRippleOverlay;
    checkedIcon            = new MaterialCheckableIcon(QIcon(":/icons/toggle/svg/production/ic_check_box_24px.svg"), q);
    uncheckedIcon          = new MaterialCheckableIcon(QIcon(":/icons/toggle/svg/production/ic_check_box_outline_blank_24px.svg"), q);
    stateMachine           = new QStateMachine(q);
    uncheckedState         = new QState;
    checkedState           = new QState;
    disabledUncheckedState = new QState;
    disabledCheckedState   = new QState;
    uncheckedTransition    = new QSignalTransition(q, SIGNAL(toggled(bool)));
    checkedTransition      = new QSignalTransition(q, SIGNAL(toggled(bool)));
    labelPosition          = MaterialCheckable::LabelPositionRight;

    rippleOverlay->setParent(q->parentWidget());
    rippleOverlay->installEventFilter(q);

    q->setCheckable(true);
    q->setFont(QFont("Roboto", 11, QFont::Normal));

    material::updatePalette(q);

    stateMachine->addState(uncheckedState);
    stateMachine->addState(checkedState);
    stateMachine->addState(disabledUncheckedState);
    stateMachine->addState(disabledCheckedState);
    stateMachine->setInitialState(uncheckedState);

    // Transition to checked

    uncheckedTransition->setTargetState(checkedState);
    uncheckedState->addTransition(uncheckedTransition);

    // Transition to unchecked

    checkedTransition->setTargetState(uncheckedState);
    checkedState->addTransition(checkedTransition);

    QAbstractTransition* transition;

    // Transitions enabled <==> disabled

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(disabledUncheckedState);
    uncheckedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(uncheckedState);
    disabledUncheckedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(disabledCheckedState);
    checkedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(checkedState);
    disabledCheckedState->addTransition(transition);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(disabledCheckedState);
    disabledUncheckedState->addTransition(transition);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(disabledUncheckedState);
    disabledCheckedState->addTransition(transition);

    checkedState->assignProperty(checkedIcon, "opacity", 1);
    checkedState->assignProperty(uncheckedIcon, "opacity", 0);

    uncheckedState->assignProperty(checkedIcon, "opacity", 0);
    uncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    disabledCheckedState->assignProperty(checkedIcon, "opacity", 1);
    disabledCheckedState->assignProperty(uncheckedIcon, "opacity", 0);

    disabledUncheckedState->assignProperty(checkedIcon, "opacity", 0);
    disabledUncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    checkedState->assignProperty(checkedIcon, "color", q->palette().color(QPalette::Button));
    checkedState->assignProperty(uncheckedIcon, "color", q->palette().color(QPalette::Window));

    uncheckedState->assignProperty(checkedIcon, "color", q->palette().color(QPalette::Button));
    uncheckedState->assignProperty(uncheckedIcon, "color", q->palette().color(QPalette::Window));

    disabledUncheckedState->assignProperty(uncheckedIcon, "color", q->palette().color(QPalette::Disabled, QPalette::Window));
    disabledCheckedState->assignProperty(checkedIcon, "color", q->palette().color(QPalette::Disabled, QPalette::Button));

    stateMachine->start();
    QCoreApplication::processEvents();
}

MaterialCheckable::MaterialCheckable(QWidget* parent)
    : QAbstractButton(parent)
    , d_ptr(new MaterialCheckablePrivate(this))
{
    d_func()->init();
}

MaterialCheckable::~MaterialCheckable()
{
}

void MaterialCheckable::setLabelPosition(LabelPosition placement)
{
    Q_D(MaterialCheckable);

    d->labelPosition = placement;
    update();
}

MaterialCheckable::LabelPosition MaterialCheckable::labelPosition() const
{
    Q_D(const MaterialCheckable);

    return d->labelPosition;
}

void MaterialCheckable::setCheckedIcon(const QIcon &icon)
{
    Q_D(MaterialCheckable);

    d->checkedIcon->setIcon(icon);
    update();
}

QIcon MaterialCheckable::checkedIcon() const
{
    Q_D(const MaterialCheckable);

    return d->checkedIcon->icon();
}

void MaterialCheckable::setUncheckedIcon(const QIcon &icon)
{
    Q_D(MaterialCheckable);

    d->uncheckedIcon->setIcon(icon);
    update();
}

QIcon MaterialCheckable::uncheckedIcon() const
{
    Q_D(const MaterialCheckable);

    return d->uncheckedIcon->icon();
}

QSize MaterialCheckable::sizeHint() const
{
    if (text().isEmpty())
        return QSize(40, 40);

    return QSize(fontMetrics().size(Qt::TextShowMnemonic, text()).width() + 52, 40);
}

MaterialCheckable::MaterialCheckable(MaterialCheckablePrivate& d, QWidget* parent)
    : QAbstractButton(parent)
    , d_ptr(&d)
{
    d_func()->init();
}

bool MaterialCheckable::event(QEvent* event)
{
    Q_D(MaterialCheckable);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move: {
        d->checkedIcon->setGeometry(rect());
        d->uncheckedIcon->setGeometry(rect());
        d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
        break;
    }
    case QEvent::ParentChange: {
        QWidget* widget;
        if ((widget = parentWidget()))
            d->rippleOverlay->setParent(widget);
        break;
    }
    case QEvent::ThemeChange: {
        material::updatePalette(this);
        return true;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

bool MaterialCheckable::eventFilter(QObject* obj, QEvent* event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(MaterialCheckable);

        d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
    }
    return QAbstractButton::eventFilter(obj, event);
}

void MaterialCheckable::mousePressEvent(QMouseEvent*)
{
    Q_D(MaterialCheckable);

    if (!isEnabled())
        return;

    MaterialRipple* ripple;
    if (MaterialCheckable::LabelPositionLeft == d->labelPosition) {
         ripple = new MaterialRipple(QPoint(width()-14, 28));
    } else {
         ripple = new MaterialRipple(QPoint(28, 28));
    }
    ripple->setRadiusEndValue(22);
    ripple->setColor(isChecked()
                     ? palette().color(QPalette::ButtonText)
                     : palette().color(QPalette::Button));
    if (isChecked()) {
        ripple->setOpacityStartValue(1);
    }
    d->rippleOverlay->addRipple(ripple);

    setChecked(!isChecked());
}

void MaterialCheckable::paintEvent(QPaintEvent*)
{
    Q_D(MaterialCheckable);

    QPainter painter(this);
    QPen     pen;

    pen.setColor(isEnabled()
                 ? palette().color(QPalette::Button)
                 : palette().color(QPalette::Disabled, QPalette::Button));
    painter.setPen(pen);

    if (d->labelPosition == MaterialCheckable::LabelPositionLeft) {
        painter.drawText(4, 25, text());
        return;
    }
    painter.drawText(48, 25, text());
}

void MaterialCheckable::setupProperties()
{
    Q_D(MaterialCheckable);

    QColor disabled  = palette().color(QPalette::Disabled, QPalette::Button);
    QColor checked   = palette().color(QPalette::Button);
    QColor unchecked = palette().color(QPalette::Button);

    d->checkedState->assignProperty(d->checkedIcon, "color", checked);
    d->checkedState->assignProperty(d->uncheckedIcon, "color", checked);
    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", unchecked);
    d->disabledUncheckedState->assignProperty(d->uncheckedIcon, "color", disabled);
    d->disabledCheckedState->assignProperty(d->checkedIcon, "color", disabled);

    if (isEnabled()) {
        if (isChecked()) {
            d->checkedIcon->setColor(checked);
        } else {
            d->uncheckedIcon->setColor(unchecked);
        }
    } else {
        d->checkedIcon->setColor(disabled);
        d->uncheckedIcon->setColor(disabled);
    }
    update();
}
