#ifndef TEXTFIELDSETTINGSEDITOR_H
#define TEXTFIELDSETTINGSEDITOR_H

#include <QWidget>
#include "ui_textfieldsettingsform.h"

class MaterialTextField;

class TextFieldSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TextFieldSettingsEditor(QWidget* parent = nullptr);
    ~TextFieldSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();
    void setShowInputLine();

private:
    Ui::TextFieldSettingsForm *const ui;
    MaterialTextField       *const m_textField;
};

#endif // TEXTFIELDSETTINGSEDITOR_H
