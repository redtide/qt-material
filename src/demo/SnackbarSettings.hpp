#ifndef SNACKBARSETTINGSEDITOR_H
#define SNACKBARSETTINGSEDITOR_H

#include "ui_SnackbarSettings.h"

class SnackbarSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SnackbarSettings(QWidget* parent = nullptr);
    ~SnackbarSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void showSnackbar();

private:
    Ui::SnackbarSettings* ui_;
};

#endif // SNACKBARSETTINGSEDITOR_H
