#include "slider_internal.hpp"
#include "slider_p.hpp"
#include "statetransitionevent.hpp"

#include <QtMaterialWidgets/slider.hpp>
#include <QtMaterialWidgets/style.hpp>

#include <QMouseEvent>
#include <QtWidgets/QApplication>

/*!
 *  \class MaterialSliderPrivate
 *  \internal
 */

MaterialSliderPrivate::MaterialSliderPrivate(MaterialSlider *q)
    : q_ptr(q)
{
}

MaterialSliderPrivate::~MaterialSliderPrivate()
{
}

void MaterialSliderPrivate::init()
{
    Q_Q(MaterialSlider);

    thumb          = new MaterialSliderThumb(q);
    track          = new MaterialSliderTrack(thumb, q);
    stateMachine   = new MaterialSliderStateMachine(q, thumb, track);
    stepTo         = 0;
    oldValue       = q->value();
    trackWidth     = 4;
    hoverTrack     = false;
    hoverThumb     = false;
    hover          = false;
    step           = false;
    pageStepMode   = true;
    useThemeColors = true;

    q->setMouseTracking(true);
    q->setFocusPolicy(Qt::StrongFocus);
    q->setPageStep(1);

    QSizePolicy sp(QSizePolicy::Expanding,
                   QSizePolicy::Fixed);

    if (q->orientation() == Qt::Vertical) {
        sp.transpose();
    }

    q->setSizePolicy(sp);
    q->setAttribute(Qt::WA_WState_OwnSizePolicy, false);

    stateMachine->start();
    QCoreApplication::processEvents();
}

QRectF MaterialSliderPrivate::trackBoundingRect() const
{
    Q_Q(const MaterialSlider);

    qreal hw = static_cast<qreal>(trackWidth)/2;

    return Qt::Horizontal == q->orientation()
        ? QRectF(QT_MATERIAL_SLIDER_MARGIN, q->height()/2 - hw,
                 q->width() - QT_MATERIAL_SLIDER_MARGIN*2, hw*2)
        : QRectF(q->width()/2 - hw, QT_MATERIAL_SLIDER_MARGIN, hw*2,
                 q->height() - QT_MATERIAL_SLIDER_MARGIN*2);
}

QRectF MaterialSliderPrivate::thumbBoundingRect() const
{
    Q_Q(const MaterialSlider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(thumb->offset(), q->height()/2 - QT_MATERIAL_SLIDER_MARGIN,
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2)
        : QRectF(q->width()/2 - QT_MATERIAL_SLIDER_MARGIN, thumb->offset(),
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2);
}

int MaterialSliderPrivate::valueFromPosition(const QPoint &pos) const
{
    Q_Q(const MaterialSlider);

    const int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

    const int span = Qt::Horizontal == q->orientation()
        ? q->width() - QT_MATERIAL_SLIDER_MARGIN*2
        : q->height() - QT_MATERIAL_SLIDER_MARGIN*2;

    return MaterialStyle::sliderValueFromPosition(
                q->minimum(),
                q->maximum(),
                position - QT_MATERIAL_SLIDER_MARGIN,
                span,
                q->invertedAppearance());
}

void MaterialSliderPrivate::setHovered(bool status)
{
    Q_Q(MaterialSlider);

    if (hover == status) {
        return;
    }

    hover = status;

    if (!q->hasFocus()) {
        if (status) {
            stateMachine->postEvent(new MaterialStateTransitionEvent(SliderNoFocusMouseEnter));
        } else {
            stateMachine->postEvent(new MaterialStateTransitionEvent(SliderNoFocusMouseLeave));
        }
    }

    q->update();
}

/*!
 *  \class MaterialSlider
 */

MaterialSlider::MaterialSlider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new MaterialSliderPrivate(this))
{
    d_func()->init();
}

MaterialSlider::~MaterialSlider()
{
}

void MaterialSlider::setUseThemeColors(bool value)
{
    Q_D(MaterialSlider);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool MaterialSlider::useThemeColors() const
{
    Q_D(const MaterialSlider);

    return d->useThemeColors;
}

void MaterialSlider::setThumbColor(const QColor &color)
{
    Q_D(MaterialSlider);

    d->thumbColor = color;
    d->useThemeColors = false;
    d->stateMachine->setupProperties();

    update();
}

QColor MaterialSlider::thumbColor() const
{
    Q_D(const MaterialSlider);

    if (d->useThemeColors || !d->thumbColor.isValid()) {
        return MaterialStyle::instance().themeColor("primary1");
    } else {
        return d->thumbColor;
    }
}

void MaterialSlider::setTrackColor(const QColor &color)
{
    Q_D(MaterialSlider);

    d->trackColor = color;
    d->useThemeColors = false;
    d->stateMachine->setupProperties();

    update();
}

QColor MaterialSlider::trackColor() const
{
    Q_D(const MaterialSlider);

    if (d->useThemeColors || !d->trackColor.isValid()) {
        return MaterialStyle::instance().themeColor("accent3");
    } else {
        return d->trackColor;
    }
}

void MaterialSlider::setDisabledColor(const QColor &color)
{
    Q_D(MaterialSlider);

    d->disabledColor = color;
    d->useThemeColors = false;
    d->stateMachine->setupProperties();

    update();
}

QColor MaterialSlider::disabledColor() const
{
    Q_D(const MaterialSlider);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return MaterialStyle::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void MaterialSlider::setPageStepMode(bool pageStep)
{
    Q_D(MaterialSlider);

    d->pageStepMode = pageStep;
}

bool MaterialSlider::pageStepMode() const
{
    Q_D(const MaterialSlider);

    return d->pageStepMode;
}

/*!
 *  \remip
 */
QSize MaterialSlider::minimumSizeHint() const
{
    return Qt::Horizontal == orientation()
            ? QSize(130, 34)
            : QSize(34, 130);
}

void MaterialSlider::setInvertedAppearance(bool value)
{
    QAbstractSlider::setInvertedAppearance(value);

    updateThumbOffset();
}

/*!
 *  \remip
 */
void MaterialSlider::sliderChange(SliderChange change)
{
    Q_D(MaterialSlider);

    if (SliderOrientationChange == change)
    {
        QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (orientation() == Qt::Vertical) {
            sp.transpose();
        }
        setSizePolicy(sp);
    }
    else if (SliderValueChange == change)
    {
        if (minimum() == value()) {
            triggerAction(SliderToMinimum);
            d->stateMachine->postEvent(new MaterialStateTransitionEvent(SliderChangedToMinimum));
        } else if (maximum() == value()) {
            triggerAction(SliderToMaximum);
        }
        if (minimum() == d->oldValue) {
            d->stateMachine->postEvent(new MaterialStateTransitionEvent(SliderChangedFromMinimum));
        }
        d->oldValue = value();
    }

    updateThumbOffset();

    QAbstractSlider::sliderChange(change);
}

/*!
 *  \remip
 */
void MaterialSlider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(MaterialSlider);

    if (isSliderDown())
    {
        setSliderPosition(d->valueFromPosition(event->pos()));
    }
    else
    {
        QRectF track(d->trackBoundingRect().adjusted(-2, -2, 2, 2));

        if (track.contains(event->pos()) != d->hoverTrack) {
            d->hoverTrack = !d->hoverTrack;
            update();
        }

        QRectF thumb(0, 0, 16, 16);
        thumb.moveCenter(d->thumbBoundingRect().center());

        if (thumb.contains(event->pos()) != d->hoverThumb) {
            d->hoverThumb = !d->hoverThumb;
            update();
        }

        d->setHovered(d->hoverTrack || d->hoverThumb);
    }

    QAbstractSlider::mouseMoveEvent(event);
}

/*!
 *  \remip
 */
void MaterialSlider::mousePressEvent(QMouseEvent *event)
{
    Q_D(MaterialSlider);

    const QPoint pos = event->pos();

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(d->thumbBoundingRect().center());

    if (thumb.contains(pos)) {
        setSliderDown(true);
        return;
    }

    if (!d->pageStepMode) {
        setSliderPosition(d->valueFromPosition(event->pos()));
        d->thumb->setHaloSize(0);
        setSliderDown(true);
        return;
    }

    d->step = true;
    d->stepTo = d->valueFromPosition(pos);

    SliderAction action = d->stepTo > sliderPosition()
        ? SliderPageStepAdd
        : SliderPageStepSub;

    triggerAction(action);
    setRepeatAction(action, 400, 8);
}

/*!
 *  \remip
 */
void MaterialSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(MaterialSlider);

    if (isSliderDown()) {
        setSliderDown(false);
    } else if (d->step) {
        d->step = false;
        setRepeatAction(SliderNoAction, 0);
    }

    QAbstractSlider::mouseReleaseEvent(event);
}

/*!
 *  \remip
 */
void MaterialSlider::leaveEvent(QEvent *event)
{
    Q_D(MaterialSlider);

    if (d->hoverTrack) {
        d->hoverTrack = false;
        update();
    }
    if (d->hoverThumb) {
        d->hoverThumb = false;
        update();
    }

    d->setHovered(false);

    QAbstractSlider::leaveEvent(event);
}

void MaterialSlider::updateThumbOffset()
{
    Q_D(MaterialSlider);

    const int offset = MaterialStyle::sliderPositionFromValue(
        minimum(),
        maximum(),
        sliderPosition(),
        Qt::Horizontal == orientation()
            ? width() - QT_MATERIAL_SLIDER_MARGIN*2
            : height() - QT_MATERIAL_SLIDER_MARGIN*2,
        invertedAppearance());

    d->thumb->setOffset(offset);
}
