#ifndef TABSSETTINGSEDITOR_H
#define TABSSETTINGSEDITOR_H

#include <QWidget>
#include "ui_tabssettingsform.h"

class MaterialTabs;

class TabsSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TabsSettingsEditor(QWidget* parent = nullptr);
    ~TabsSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::TabsSettingsForm *const ui;
    MaterialTabs         *const m_tabs;
};

#endif // TABSSETTINGSEDITOR_H
