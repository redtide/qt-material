#ifndef RAISEDBUTTONSETTINGSEDITOR_H
#define RAISEDBUTTONSETTINGSEDITOR_H

#include "ui_RaisedButtonSettings.h"

class RaisedButtonSettings : public QWidget
{
    Q_OBJECT

public:
    explicit RaisedButtonSettings(QWidget* parent = nullptr);
    ~RaisedButtonSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::RaisedButtonSettings* ui_;
};

#endif // RAISEDBUTTONSETTINGSEDITOR_H
