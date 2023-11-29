#ifndef FABSETTINGSEDITOR_H
#define FABSETTINGSEDITOR_H

#include <QWidget>
#include "ui_fabsettingsform.h"

class MaterialFloatingActionButton;

class FloatingActionButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FloatingActionButtonSettingsEditor(QWidget* parent = nullptr);
    ~FloatingActionButtonSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::FloatingActionButtonSettingsForm *const ui;
    MaterialFloatingActionButton       *const m_fab;
};

#endif // FABSETTINGSEDITOR_H
