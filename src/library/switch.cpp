#include "switch_internal.hpp"
#include "switch_p.hpp"

#include <QtMaterialWidgets/switch.hpp>
#include "palette-helper.hpp"

#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QStateMachine>
#include <QtWidgets/QApplication>

MaterialSwitchPrivate::MaterialSwitchPrivate(MaterialSwitch* q)
    : q_ptr(q)
{
}

MaterialSwitchPrivate::~MaterialSwitchPrivate()
{
}

void MaterialSwitchPrivate::init()
{
    Q_Q(MaterialSwitch);

    material::updatePalette(q);

    track          = new MaterialSwitchTrack(q);
    thumb          = new MaterialSwitchThumb(q);
    rippleOverlay  = new MaterialSwitchRippleOverlay(thumb, track, q);
    stateMachine   = new QStateMachine(q);
    offState       = new QState;
    onState        = new QState;
    orientation    = Qt::Horizontal;

    q->setCheckable(true);
    q->setChecked(false);
    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    stateMachine->addState(offState);
    stateMachine->addState(onState);
    stateMachine->setInitialState(offState);

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    QSignalTransition* transition;
    QPropertyAnimation* animation;

    //

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    setupProperties();

    stateMachine->start();
    QCoreApplication::processEvents();
}

void MaterialSwitchPrivate::setupProperties()
{
    Q_Q(MaterialSwitch);

    if (q->isEnabled()) {
        const qreal shift = thumb->shift();
        if (qFuzzyCompare(shift, 1)) {
            thumb->setThumbColor(q->palette().color(QPalette::Button));
            track->setTrackColor(q->palette().color(QPalette::Button).lighter(110));
        } else if (qFuzzyCompare(1 + shift, 1)) {
            thumb->setThumbColor(q->palette().color(QPalette::Button).darker());
            track->setTrackColor(q->palette().color(QPalette::WindowText));
        }
    }
    offState->assignProperty(track, "trackColor", q->palette().color(QPalette::Button).lighter(110));
    onState->assignProperty(track, "trackColor", q->palette().color(QPalette::Button).lighter(110));

    offState->assignProperty(thumb, "thumbColor", q->palette().color(QPalette::Button).darker());
    onState->assignProperty(thumb, "thumbColor", q->palette().color(QPalette::Button));

    q->update();
}

MaterialSwitch::MaterialSwitch(QWidget* parent)
    : QAbstractButton(parent),
      d_ptr(new MaterialSwitchPrivate(this))
{
    d_func()->init();
}

MaterialSwitch::~MaterialSwitch()
{
}

void MaterialSwitch::setOrientation(Qt::Orientation orientation)
{
    Q_D(MaterialSwitch);

    if (d->orientation == orientation)
        return;

    d->orientation = orientation;
    updateGeometry();
}

Qt::Orientation MaterialSwitch::orientation() const
{
    Q_D(const MaterialSwitch);

    return d->orientation;
}

QSize MaterialSwitch::sizeHint() const
{
    Q_D(const MaterialSwitch);

    return Qt::Horizontal == d->orientation
        ? QSize(64, 48)
        : QSize(48, 64);
}

bool MaterialSwitch::event(QEvent* event)
{
    Q_D(MaterialSwitch);

    switch (event->type())
    {
    case QEvent::ParentChange:
    {
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

void MaterialSwitch::paintEvent(QPaintEvent*)
{
}
