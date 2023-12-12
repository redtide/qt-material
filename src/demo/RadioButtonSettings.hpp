#ifndef RADIOBUTTONSETTINGSEDITOR_H
#define RADIOBUTTONSETTINGSEDITOR_H

#include "ui_RadioButtonSettings.h"

class RadioButtonSettings : public QWidget
{
    Q_OBJECT

public:
    explicit RadioButtonSettings(QWidget* parent = nullptr);
    ~RadioButtonSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::RadioButtonSettings* ui_;
};

#endif // RADIOBUTTONSETTINGSEDITOR_H
