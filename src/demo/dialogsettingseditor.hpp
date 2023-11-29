#ifndef DIALOGSETTINGSEDITOR_H
#define DIALOGSETTINGSEDITOR_H

#include <QWidget>
#include "ui_dialogsettingsform.h"

class MaterialDialog;

class DialogSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DialogSettingsEditor(QWidget* parent = nullptr);
    ~DialogSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::DialogSettingsForm *const ui;
    MaterialDialog       *const m_dialog;
};

#endif // DIALOGSETTINGSEDITOR_H
