#include "textfield_internal.hpp"
#include "defaults.hpp"

#include <QtMaterialWidgets/textfield.hpp>

#include <QEventTransition>
#include <QPainter>
#include <QPropertyAnimation>

namespace defaults = material::defaults::global;

MaterialTextFieldStateMachine::MaterialTextFieldStateMachine(MaterialTextField* parent)
    : QStateMachine(parent)
    , textField_(parent)
    , normalState_(new QState)
    , focusedState_(new QState)
    , label_(0)
    , offsetAnimation_(0)
    , colorAnimation_(0)
    , progress_(0.0)
{
    Q_ASSERT(parent);

    addState(normalState_);
    addState(focusedState_);

    setInitialState(normalState_);

    QEventTransition*   transition;
    QPropertyAnimation* animation;

    transition = new QEventTransition(parent, QEvent::FocusIn);
    transition->setTargetState(focusedState_);
    normalState_->addTransition(transition);

    animation = new QPropertyAnimation(this, "progress", this);
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->setDuration(310);
    transition->addAnimation(animation);

    transition = new QEventTransition(parent, QEvent::FocusOut);
    transition->setTargetState(normalState_);
    focusedState_->addTransition(transition);

    animation = new QPropertyAnimation(this, "progress", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setDuration(310);
    transition->addAnimation(animation);

    normalState_->assignProperty(this, "progress", 0);
    focusedState_->assignProperty(this, "progress", 1);

    setupProperties();

    connect(textField_, SIGNAL(textChanged(QString)), this, SLOT(setupProperties()));
}

MaterialTextFieldStateMachine::~MaterialTextFieldStateMachine()
{
}

void MaterialTextFieldStateMachine::setLabel(MaterialTextFieldLabel* label)
{
    if (label_)
        delete label_;

    if (offsetAnimation_) {
        removeDefaultAnimation(offsetAnimation_);
        delete offsetAnimation_;
    }

    if (colorAnimation_) {
        removeDefaultAnimation(colorAnimation_);
        delete colorAnimation_;
    }

    label_ = label;

    if (label_)
    {
        offsetAnimation_ = new QPropertyAnimation(label_, "offset", this);
        offsetAnimation_->setDuration(210);
        offsetAnimation_->setEasingCurve(QEasingCurve::OutCubic);
        addDefaultAnimation(offsetAnimation_);

        colorAnimation_ = new QPropertyAnimation(label_, "color", this);
        colorAnimation_->setDuration(210);
        addDefaultAnimation(colorAnimation_);
    }

    setupProperties();
}

void MaterialTextFieldStateMachine::setupProperties()
{
    if (label_)
    {
        const int m = textField_->textMargins().top();

        if (textField_->text().isEmpty())
            normalState_->assignProperty(label_, "offset", QPointF(0, 26));
        else
            normalState_->assignProperty(label_, "offset", QPointF(0, 0-m));

        focusedState_->assignProperty(label_, "offset", QPointF(0, 0-m));
        focusedState_->assignProperty(label_, "color", textField_->palette().color(QPalette::Button));
        normalState_->assignProperty(label_, "color", textField_->palette().color(QPalette::Button));

        if (label_->offset().y() != 0 && !textField_->text().isEmpty())
            label_->setOffset(QPointF(0, 0 - m));
        else if (!textField_->hasFocus() && label_->offset().y() <= 0 && textField_->text().isEmpty())
            label_->setOffset(QPointF(0, 26));
    }
    textField_->update();
}

MaterialTextFieldLabel::MaterialTextFieldLabel(MaterialTextField* parent)
    : QWidget(parent)
    , textField_(parent)
    , scale_(1)
    , offsetX_(0)
    , offsetY_(26)
{
    Q_ASSERT(parent);

    QFont font(defaults::font::family, parent->labelFontSize(), QFont::Medium);
    font.setLetterSpacing(QFont::PercentageSpacing, 102);
    setFont(font);
}

MaterialTextFieldLabel::~MaterialTextFieldLabel()
{
}

void MaterialTextFieldLabel::paintEvent(QPaintEvent*)
{
    if (!textField_->hasLabel())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(scale_, scale_);
    painter.setPen(palette().color(QPalette::Button));
    painter.setOpacity(1);

    QPointF pos(2 + offsetX_, height() - 36 + offsetY_);
    painter.drawText(pos.x(), pos.y(), textField_->label());
}
