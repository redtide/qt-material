#ifndef SLIDERSETTINGSEDITOR_H
#define SLIDERSETTINGSEDITOR_H

#include "ui_SliderSettings.h"

class SliderSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SliderSettings(QWidget* parent = nullptr);
    ~SliderSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::SliderSettings* ui_;
};

#endif // SLIDERSETTINGSEDITOR_H
