#ifndef CHECKBOXSETTINGSEDITOR_H
#define CHECKBOXSETTINGSEDITOR_H

#include <QWidget>
#include "ui_checkboxsettingsform.h"

class MaterialCheckable;

class CheckBoxSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CheckBoxSettingsEditor(QWidget* parent = nullptr);
    ~CheckBoxSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::CheckBoxSettingsForm *const ui;
    MaterialCheckable        *const m_checkBox;
};

#endif // CHECKBOXSETTINGSEDITOR_H
