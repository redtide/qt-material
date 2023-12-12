#ifndef CHECKBOXSETTINGSEDITOR_H
#define CHECKBOXSETTINGSEDITOR_H

#include "ui_CheckBoxSettings.h"

class CheckBoxSettings : public QWidget
{
    Q_OBJECT

public:
    explicit CheckBoxSettings(QWidget* parent = nullptr);
    ~CheckBoxSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::CheckBoxSettings* ui_;
};

#endif // CHECKBOXSETTINGSEDITOR_H
