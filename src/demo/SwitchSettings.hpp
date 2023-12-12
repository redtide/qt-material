#ifndef SWITCHSETTINGSEDITOR_H
#define SWITCHSETTINGSEDITOR_H

#include "ui_SwitchSettings.h"

class SwitchSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchSettings(QWidget* parent = nullptr);
    ~SwitchSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::SwitchSettings* ui_;
};

#endif // SWITCHSETTINGSEDITOR_H
