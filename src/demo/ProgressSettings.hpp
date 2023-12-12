#ifndef PROGRESSSETTINGSEDITOR_H
#define PROGRESSSETTINGSEDITOR_H

#include "ui_ProgressSettings.h"

class ProgressSettings : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressSettings(QWidget* parent = nullptr);
    ~ProgressSettings();

private Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::ProgressSettings* ui_;
};

#endif // PROGRESSSETTINGSEDITOR_H
