#ifndef FABSETTINGSEDITOR_H
#define FABSETTINGSEDITOR_H

#include "ui_FABSettings.h"

class FABSettings : public QWidget
{
    Q_OBJECT

public:
    explicit FABSettings(QWidget* parent = nullptr);
    ~FABSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::FABSettings* ui_;
};

#endif // FABSETTINGSEDITOR_H
