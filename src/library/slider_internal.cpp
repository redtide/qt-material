#include "slider_internal.hpp"
#include "statetransition.hpp"

#include <QtMaterialWidgets/slider.hpp>

#include <QAbstractTransition>
#include <QEventTransition>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>

MaterialSliderStateMachine::MaterialSliderStateMachine(
    MaterialSlider*      slider,
    MaterialSliderThumb* thumb,
    MaterialSliderTrack* track
)
    : QStateMachine(slider)
    , slider_(slider)
    , thumb_(thumb)
    , track_(track)
    , topState_(new QState(QState::ParallelStates))
    , fstState_(new QState(topState_))
    , sndState_(new QState(topState_))
    , inactiveState_(new QState(fstState_))
    , focusState_(new QState(fstState_))
    , slidingState_(new QState(fstState_))
    , pulseOutState_(new QState(focusState_))
    , pulseInState_(new QState(focusState_))
    , minState_(new QState(sndState_))
    , normalState_(new QState(sndState_))
{
    addState(topState_);
    setInitialState(topState_);

    fstState_->setInitialState(inactiveState_);
    focusState_->setInitialState(pulseOutState_);

    inactiveState_->assignProperty(thumb, "haloSize", 0);
    slidingState_->assignProperty(thumb, "haloSize", 0);

    pulseOutState_->assignProperty(thumb, "haloSize", 35);
    pulseInState_->assignProperty(thumb, "haloSize", 28);

    inactiveState_->assignProperty(thumb, "diameter", 15);
    focusState_->assignProperty(thumb, "diameter", 15);
    slidingState_->assignProperty(thumb, "diameter", 20);

    QAbstractTransition* transition;
    MaterialStateTransition* customTransition;
    QPropertyAnimation* animation;

    // Show halo on mouse enter

    customTransition = new MaterialStateTransition(SliderNoFocusMouseEnter);
    customTransition->setTargetState(focusState_);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    customTransition->addAnimation(animation);
    customTransition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    inactiveState_->addTransition(customTransition);

    // Show halo on focus in

    transition = new QEventTransition(slider, QEvent::FocusIn);
    transition->setTargetState(focusState_);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    inactiveState_->addTransition(transition);

    // Hide halo on focus out

    transition = new QEventTransition(slider, QEvent::FocusOut);
    transition->setTargetState(inactiveState_);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    focusState_->addTransition(transition);

    // Hide halo on mouse leave, except if widget has focus

    customTransition = new MaterialStateTransition(SliderNoFocusMouseLeave);
    customTransition->setTargetState(inactiveState_);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    customTransition->addAnimation(animation);
    customTransition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    focusState_->addTransition(customTransition);

    // Pulse in

    transition = new QSignalTransition(pulseOutState_, SIGNAL(propertiesAssigned()));
    transition->setTargetState(pulseInState_);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    pulseOutState_->addTransition(transition);

    // Pulse out

    transition = new QSignalTransition(pulseInState_, SIGNAL(propertiesAssigned()));
    transition->setTargetState(pulseOutState_);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    pulseInState_->addTransition(transition);

    // Slider pressed

    transition = new QSignalTransition(slider, SIGNAL(sliderPressed()));
    transition->setTargetState(slidingState_);
    animation = new QPropertyAnimation(thumb, "diameter", this);
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    focusState_->addTransition(transition);

    // Slider released

    transition = new QSignalTransition(slider, SIGNAL(sliderReleased()));
    transition->setTargetState(focusState_);
    animation = new QPropertyAnimation(thumb, "diameter", this);
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    slidingState_->addTransition(transition);

    // Min. value transitions

    minState_->assignProperty(thumb, "borderWidth", 2);
    normalState_->assignProperty(thumb, "borderWidth", 0);

    sndState_->setInitialState(minState_);

    customTransition = new MaterialStateTransition(SliderChangedFromMinimum);
    customTransition->setTargetState(normalState_);

    animation = new QPropertyAnimation(thumb, "fillColor", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloColor", this);
    animation->setDuration(300);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderColor", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderWidth", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    minState_->addTransition(customTransition);

    customTransition = new MaterialStateTransition(SliderChangedToMinimum);
    customTransition->setTargetState(minState_);

    animation = new QPropertyAnimation(thumb, "fillColor", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloColor", this);
    animation->setDuration(300);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderColor", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderWidth", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    normalState_->addTransition(customTransition);

    setupProperties();
}

MaterialSliderStateMachine::~MaterialSliderStateMachine()
{
}

void MaterialSliderStateMachine::setupProperties()
{
    QColor holeColor  = slider_->palette().color(QPalette::Base);
    QColor thumbColor = slider_->palette().color(QPalette::Button);;
    QColor trackColor = slider_->palette().color(QPalette::WindowText);

    inactiveState_->assignProperty(track_, "fillColor", trackColor.lighter(130));
    slidingState_->assignProperty(track_, "fillColor", trackColor);
    focusState_->assignProperty(track_, "fillColor", trackColor);

    if (slider_->parentWidget())
        holeColor = slider_->parentWidget()->palette().color(slider_->backgroundRole());

    minState_->assignProperty(thumb_, "fillColor", holeColor);

    minState_->assignProperty(thumb_, "haloColor", trackColor);
    minState_->assignProperty(thumb_, "borderColor", trackColor);

    normalState_->assignProperty(thumb_, "fillColor", thumbColor);
    normalState_->assignProperty(thumb_, "haloColor", thumbColor);
    normalState_->assignProperty(thumb_, "borderColor", thumbColor);

    slider_->update();
}

MaterialSliderThumb::MaterialSliderThumb(MaterialSlider* slider)
    : MaterialOverlayWidget(slider->parentWidget())
    , slider_(slider)
    , diameter_(11)
    , borderWidth_(2)
    , haloSize_(0)
    , offset_(0)
{
    slider->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

MaterialSliderThumb::~MaterialSliderThumb()
{
}

bool MaterialSliderThumb::eventFilter(QObject* obj, QEvent* event)
{
    if (QEvent::ParentChange == event->type())
        setParent(slider_->parentWidget());

    return MaterialOverlayWidget::eventFilter(obj, event);
}

void MaterialSliderThumb::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Halo

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(haloColor_);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPointF disp = Qt::Horizontal == slider_->orientation()
        ? QPointF(SliderMargin + offset_, slider_->height() / 2)
        : QPointF(slider_->width() / 2, SliderMargin + offset_);

    QRectF halo((slider_->pos() - QPointF(haloSize_, haloSize_) / 2) + disp,
                QSizeF(haloSize_, haloSize_));

    painter.setOpacity(0.15);
    painter.drawEllipse(halo);

    // Knob

    const bool isMin = slider_->value() == slider_->minimum();

    brush.setColor(slider_->isEnabled()
           ? fillColor_
           : slider_->palette().color(QPalette::Disabled, QPalette::Button));
    painter.setBrush(!slider_->isEnabled() && isMin
           ? Qt::NoBrush
           : brush);

    if (slider_->isEnabled() || isMin) {
        QPen pen;
        pen.setColor(borderColor_);
        pen.setWidthF((isMin && !slider_->isEnabled()) ? 1.7 : borderWidth_);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF geometry = Qt::Horizontal == slider_->orientation()
        ? QRectF(offset_, slider_->height() / 2 - SliderMargin,
                 SliderMargin * 2, SliderMargin * 2).translated(slider_->pos())
        : QRectF(slider_->width() / 2 - SliderMargin, offset_,
                 SliderMargin * 2, SliderMargin * 2).translated(slider_->pos());

    qreal s = slider_->isEnabled() ? diameter_ : 7;

    QRectF thumb(0, 0, s, s);

    thumb.moveCenter(geometry.center());

    painter.setOpacity(1);
    painter.drawEllipse(thumb);
}

MaterialSliderTrack::MaterialSliderTrack(MaterialSliderThumb* thumb, MaterialSlider* slider)
    : MaterialOverlayWidget(slider->parentWidget()),
      slider_(slider),
      thumb_(thumb),
      m_trackWidth(2)
{
    slider->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(update()));
}

MaterialSliderTrack::~MaterialSliderTrack()
{
}

bool MaterialSliderTrack::eventFilter(QObject* obj, QEvent* event)
{
    if (QEvent::ParentChange == event->type())
        setParent(slider_->parentWidget());

    return MaterialOverlayWidget::eventFilter(obj, event);
}

void MaterialSliderTrack::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(slider_->isEnabled() ? slider_->palette().color(QPalette::Button)
                                     : slider_->palette().color(QPalette::Disabled, QPalette::Button));
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(slider_->isEnabled() ? fillColor_
                                      : slider_->palette().color(QPalette::Disabled, QPalette::Button));

    qreal offset = thumb_->offset();

    if (Qt::Horizontal == slider_->orientation()) {
        painter.translate(slider_->x() + SliderMargin,
                          slider_->y() + slider_->height() / 2
                                        - static_cast<qreal>(m_trackWidth) / 2);
    } else {
        painter.translate(slider_->x() + slider_->width() / 2
                                        - static_cast<qreal>(m_trackWidth) / 2,
                          slider_->y() + SliderMargin);
    }

    QRectF geometry = Qt::Horizontal == slider_->orientation()
        ? QRectF(0, 0, slider_->width() - SliderMargin * 2, m_trackWidth)
        : QRectF(0, 0, m_trackWidth, slider_->height() - SliderMargin * 2);

    QRectF bgRect;
    QRectF fgRect;

    if (Qt::Horizontal == slider_->orientation()) {
        fgRect = QRectF(0, 0, offset, m_trackWidth);
        bgRect = QRectF(offset, 0, slider_->width(), m_trackWidth).intersected(geometry);
    } else {
        fgRect = QRectF(0, 0, m_trackWidth, offset);
        bgRect = QRectF(0, offset, m_trackWidth, slider_->height()).intersected(geometry);
    }

    if (!slider_->isEnabled()) {
        fgRect = fgRect.width() < 9 ? QRectF() : fgRect.adjusted(0, 0, -6, 0);
        bgRect = bgRect.width() < 9 ? QRectF() : bgRect.adjusted(6, 0, 0, 0);
    }

    if (slider_->invertedAppearance())
        qSwap(bgRect, fgRect);

    painter.fillRect(bgRect, bg);
    painter.fillRect(fgRect, fg);
}
