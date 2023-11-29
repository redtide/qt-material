#ifndef RADIOBUTTONSETTINGSEDITOR_H
#define RADIOBUTTONSETTINGSEDITOR_H

#include <QWidget>
#include "ui_radiobuttonsettingsform.h"

class MaterialRadioButton;
class RadioButton;

class RadioButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit RadioButtonSettingsEditor(QWidget* parent = nullptr);
    ~RadioButtonSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::RadioButtonSettingsForm *const ui;
    MaterialRadioButton       *const m_radioButton1;
    MaterialRadioButton       *const m_radioButton2;
    MaterialRadioButton       *const m_radioButton3;
};

#endif // RADIOBUTTONSETTINGSEDITOR_H
