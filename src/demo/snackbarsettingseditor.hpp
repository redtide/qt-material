#ifndef SNACKBARSETTINGSEDITOR_H
#define SNACKBARSETTINGSEDITOR_H

#include <QWidget>
#include "ui_snackbarsettingsform.h"

class MaterialSnackbar;

class SnackbarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SnackbarSettingsEditor(QWidget* parent = nullptr);
    ~SnackbarSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void showSnackbar();

private:
    Ui::SnackbarSettingsForm *const ui;
    MaterialSnackbar       *const m_snackbar;
};

#endif // SNACKBARSETTINGSEDITOR_H
