#ifndef MATERIAL_TEXTFIELD_P_H
#define MATERIAL_TEXTFIELD_P_H

#include <QtGlobal>
#include <QColor>

class MaterialTextField;
class MaterialTextFieldStateMachine;
class MaterialTextFieldLabel;

class MaterialTextFieldPrivate
{
    Q_DISABLE_COPY(MaterialTextFieldPrivate)
    Q_DECLARE_PUBLIC(MaterialTextField)

public:
    MaterialTextFieldPrivate(MaterialTextField *q);
    virtual ~MaterialTextFieldPrivate();

    void init();

    MaterialTextField             *const q_ptr;
    MaterialTextFieldStateMachine *stateMachine;
    MaterialTextFieldLabel        *label;
    QColor                        labelColor;
    QColor                        inkColor;
    QColor                        inputLineColor;
    QString                       labelString;
    qreal                         labelFontSize;
    bool                          showLabel;
    bool                          showInputLine;

    bool                          useThemeColors;
    QColor                        textColor;
};

#endif // MATERIAL_TEXTFIELD_P_H
