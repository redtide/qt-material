#ifndef MATERIAL_SCROLLBAR_P_H
#define MATERIAL_SCROLLBAR_P_H

#include <QtGlobal>
#include <QColor>

class MaterialScrollBar;
class MaterialScrollBarStateMachine;

class MaterialScrollBarPrivate
{
    Q_DISABLE_COPY(MaterialScrollBarPrivate)
    Q_DECLARE_PUBLIC(MaterialScrollBar)

public:
    MaterialScrollBarPrivate(MaterialScrollBar *q);
    ~MaterialScrollBarPrivate();

    void init();

    MaterialScrollBar             *const q_ptr;
    MaterialScrollBarStateMachine *stateMachine;
    QColor                        sliderColor;
    QColor                        canvasColor;
    bool                          hideOnMouseOut;

    bool                          useThemeColors;
    QColor                        backgroundColor;
};

#endif // MATERIAL_SCROLLBAR_P_H
