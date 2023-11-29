#ifndef SWITCHSETTINGSEDITOR_H
#define SWITCHSETTINGSEDITOR_H

#include <QWidget>
#include "ui_switchsettingsform.h"

class MaterialSwitch;

class SwitchSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchSettingsEditor(QWidget *parent = nullptr);
    ~SwitchSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::SwitchSettingsForm *const ui;
    MaterialSwitch         *const m_switch;
};

#endif // SWITCHSETTINGSEDITOR_H
