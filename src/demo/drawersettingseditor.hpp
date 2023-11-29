#ifndef DRAWERSETTINGSEDITOR_H
#define DRAWERSETTINGSEDITOR_H

#include <QWidget>
#include "ui_drawersettingsform.h"

class MaterialDrawer;

class DrawerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DrawerSettingsEditor(QWidget* parent = nullptr);
    ~DrawerSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::DrawerSettingsForm *const ui;
    MaterialDrawer       *const m_drawer;
};

#endif // DRAWERSETTINGSEDITOR_H
