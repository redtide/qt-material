#ifndef AUTOCOMPLETESETTINGSEDITOR_H
#define AUTOCOMPLETESETTINGSEDITOR_H

#include "ui_AutoCompleteSettings.h"

class AutoCompleteSettings : public QWidget
{
    Q_OBJECT

public:
    explicit AutoCompleteSettings(QWidget* parent = nullptr);
    ~AutoCompleteSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::AutoCompleteSettings* ui_;
};

#endif // AUTOCOMPLETESETTINGSEDITOR_H
