#ifndef FLATBUTTONSETTINGSMANAGER_H
#define FLATBUTTONSETTINGSMANAGER_H

#include "ui_FlatButtonSettings.h"

class FlatButtonSettings : public QWidget
{
    Q_OBJECT

public:
    explicit FlatButtonSettings(QWidget* parent = nullptr);
    ~FlatButtonSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void applyDefaultPreset();
    void applyCheckablePreset();

private:
    Ui::FlatButtonSettings* ui_;
};

#endif // FLATBUTTONSETTINGSMANAGER_H
