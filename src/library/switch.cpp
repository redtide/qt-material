#include "switch_internal.hpp"
#include "switch_p.hpp"

#include <QtMaterialWidgets/style.hpp>
#include <QtMaterialWidgets/switch.hpp>

#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QStateMachine>
#include <QtWidgets/QApplication>

/*!
 *  \class MaterialSwitchPrivate
 *  \internal
 */

MaterialSwitchPrivate::MaterialSwitchPrivate(MaterialSwitch *q)
    : q_ptr(q)
{
}

MaterialSwitchPrivate::~MaterialSwitchPrivate()
{
}

void MaterialSwitchPrivate::init()
{
    Q_Q(MaterialSwitch);

    track          = new MaterialSwitchTrack(q);
    thumb          = new MaterialSwitchThumb(q);
    rippleOverlay  = new MaterialSwitchRippleOverlay(thumb, track, q);
    stateMachine   = new QStateMachine(q);
    offState       = new QState;
    onState        = new QState;
    orientation    = Qt::Horizontal;
    useThemeColors = true;

    q->setCheckable(true);
    q->setChecked(false);
    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    stateMachine->addState(offState);
    stateMachine->addState(onState);
    stateMachine->setInitialState(offState);

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

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
            thumb->setThumbColor(q->activeColor());
            track->setTrackColor(q->activeColor().lighter(110));
        } else if (qFuzzyCompare(1+shift, 1)) {
            thumb->setThumbColor(q->inactiveColor());
            track->setTrackColor(q->trackColor());
        }
    }

    offState->assignProperty(track, "trackColor", q->trackColor().lighter(110));
    onState->assignProperty(track, "trackColor", q->activeColor().lighter(110));

    offState->assignProperty(thumb, "thumbColor", q->inactiveColor());
    onState->assignProperty(thumb, "thumbColor", q->activeColor());

    q->update();
}

/*!
 *  \class MaterialSwitch
 */

MaterialSwitch::MaterialSwitch(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new MaterialSwitchPrivate(this))
{
    d_func()->init();
}

MaterialSwitch::~MaterialSwitch()
{
}

void MaterialSwitch::setUseThemeColors(bool value)
{
    Q_D(MaterialSwitch);

    d->useThemeColors = value;
    d->setupProperties();
}

bool MaterialSwitch::useThemeColors() const
{
    Q_D(const MaterialSwitch);

    return d->useThemeColors;
}

void MaterialSwitch::setDisabledColor(const QColor &color)
{
    Q_D(MaterialSwitch);

    d->disabledColor = color;
    d->useThemeColors = false;

    d->setupProperties();
}

QColor MaterialSwitch::disabledColor() const
{
    Q_D(const MaterialSwitch);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return MaterialStyle::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void MaterialSwitch::setActiveColor(const QColor &color)
{
    Q_D(MaterialSwitch);

    d->activeColor = color;
    d->useThemeColors = false;

    d->setupProperties();
}

QColor MaterialSwitch::activeColor() const
{
    Q_D(const MaterialSwitch);

    if (d->useThemeColors || !d->activeColor.isValid()) {
        return MaterialStyle::instance().themeColor("primary1");
    } else {
        return d->activeColor;
    }
}

void MaterialSwitch::setInactiveColor(const QColor &color)
{
    Q_D(MaterialSwitch);

    d->inactiveColor = color;
    d->useThemeColors = false;

    d->setupProperties();
}

QColor MaterialSwitch::inactiveColor() const
{
    Q_D(const MaterialSwitch);

    if (d->useThemeColors || !d->inactiveColor.isValid()) {
        return MaterialStyle::instance().themeColor("canvas");
    } else {
        return d->inactiveColor;
    }
}

void MaterialSwitch::setTrackColor(const QColor &color)
{
    Q_D(MaterialSwitch);

    d->trackColor = color;
    d->useThemeColors = false;

    d->setupProperties();
}

QColor MaterialSwitch::trackColor() const
{
    Q_D(const MaterialSwitch);

    if (d->useThemeColors || !d->trackColor.isValid()) {
        return MaterialStyle::instance().themeColor("accent3");
    } else {
        return d->trackColor;
    }
}

void MaterialSwitch::setOrientation(Qt::Orientation orientation)
{
    Q_D(MaterialSwitch);

    if (d->orientation == orientation) {
        return;
    }

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

bool MaterialSwitch::event(QEvent *event)
{
    Q_D(MaterialSwitch);

    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

void MaterialSwitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}
