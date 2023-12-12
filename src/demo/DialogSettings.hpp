#ifndef DIALOGSETTINGSEDITOR_H
#define DIALOGSETTINGSEDITOR_H

#include "ui_DialogSettings.h"

class DialogSettings : public QWidget
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget* parent = nullptr);
    ~DialogSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::DialogSettings* ui_;
};

#endif // DIALOGSETTINGSEDITOR_H
