#ifndef MATERIAL_SLIDER_P_H
#define MATERIAL_SLIDER_P_H

#include <QtGlobal>
#include <QColor>
#include <QRectF>

class MaterialSlider;
class MaterialSliderThumb;
class MaterialSliderTrack;
class MaterialSliderStateMachine;

class MaterialSliderPrivate
{
    Q_DISABLE_COPY(MaterialSliderPrivate)
    Q_DECLARE_PUBLIC(MaterialSlider)

public:
    MaterialSliderPrivate(MaterialSlider *q);
    ~MaterialSliderPrivate();

    void init();

    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;

    int valueFromPosition(const QPoint &pos) const;

    void setHovered(bool status);

    MaterialSlider             *const q_ptr;
    MaterialSliderThumb        *thumb;
    MaterialSliderTrack        *track;
    MaterialSliderStateMachine *stateMachine;
    QColor                     thumbColor;
    QColor                     trackColor;
    QColor                     disabledColor;
    int                        stepTo;
    int                        oldValue;
    int                        trackWidth;
    bool                       hoverTrack;
    bool                       hoverThumb;
    bool                       hover;
    bool                       step;
    bool                       pageStepMode;

    bool                       useThemeColors;
};

#endif // MATERIAL_SLIDER_P_H
