#include "drawer_internal.hpp"

#include <QtMaterialWidgets/drawer.hpp>

#include <QSignalTransition>
#include <QState>
#include <QPainter>
#include <QPropertyAnimation>
#include <QtWidgets/QLayout>

MaterialDrawerStateMachine::MaterialDrawerStateMachine(MaterialDrawerWidget* drawer, MaterialDrawer* parent)
    : QStateMachine(parent)
    , drawer_(drawer)
    , main_(parent)
    , openingState_(new QState)
    , openedState_(new QState)
    , closingState_(new QState)
    , closedState_(new QState)
    , opacity_(0)
{
    addState(openingState_);
    addState(openedState_);
    addState(closingState_);
    addState(closedState_);

    setInitialState(closedState_);

    QSignalTransition* transition;
    QPropertyAnimation* animation;

    transition = new QSignalTransition(this, SIGNAL(signalOpen()));
    transition->setTargetState(openingState_);
    closedState_->addTransition(transition);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(openedState_);
    openingState_->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(signalClose()));
    transition->setTargetState(closingState_);
    openingState_->addTransition(transition);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(closedState_);
    closingState_->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(signalClose()));
    transition->setTargetState(closingState_);
    openedState_->addTransition(transition);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(closedState_);
    closingState_->addTransition(transition);

    updatePropertyAssignments();
}

MaterialDrawerStateMachine::~MaterialDrawerStateMachine()
{
}

void MaterialDrawerStateMachine::setOpacity(qreal opacity)
{
    opacity_ = opacity;
    main_->update();
}

bool MaterialDrawerStateMachine::isInClosedState() const
{
    return closedState_->active();
}

void MaterialDrawerStateMachine::updatePropertyAssignments()
{
    const qreal closedOffset = -(drawer_->width()+32);

    closingState_->assignProperty(drawer_, "offset", closedOffset);
    closedState_->assignProperty(drawer_, "offset", closedOffset);

    closingState_->assignProperty(this, "opacity", 0);
    closedState_->assignProperty(this, "opacity", 0);

    openingState_->assignProperty(drawer_, "offset", 0);
    openingState_->assignProperty(this, "opacity", 0.4);
}

MaterialDrawerWidget::MaterialDrawerWidget(QWidget* parent)
    : MaterialOverlayWidget(parent)
    , offset_(0)
{
}

MaterialDrawerWidget::~MaterialDrawerWidget()
{
}

void MaterialDrawerWidget::setOffset(int offset)
{
    offset_ = offset;

    QWidget* widget = parentWidget();
    if (widget)
        setGeometry(widget->rect().translated(offset, 0));

    update();
}

void MaterialDrawerWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect().adjusted(0, 0, -16, 0));

    QLinearGradient gradient(QPointF(width()-16, 0), QPointF(width(), 0));
    gradient.setColorAt(0, QColor(0, 0, 0, 80));
    gradient.setColorAt(0.5, QColor(0, 0, 0, 20));
    gradient.setColorAt(1, QColor(0, 0, 0, 0));
    painter.setBrush(QBrush(gradient));

    painter.drawRect(width()-16, 0, 16, height());
}

QRect MaterialDrawerWidget::overlayGeometry() const
{
    return MaterialOverlayWidget::overlayGeometry().translated(offset_, 0);
}
