#ifndef DRAWERSETTINGSEDITOR_H
#define DRAWERSETTINGSEDITOR_H

#include "ui_DrawerSettings.h"

class DrawerSettings : public QWidget
{
    Q_OBJECT

public:
    explicit DrawerSettings(QWidget* parent = nullptr);
    ~DrawerSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::DrawerSettings* ui_;
};

#endif // DRAWERSETTINGSEDITOR_H
