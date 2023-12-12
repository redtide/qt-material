#ifndef CIRCULARPROGRESSSETTINGSEDITOR_H
#define CIRCULARPROGRESSSETTINGSEDITOR_H

#include "ui_CircularProgressSettings.h"

class CircularProgressSettings : public QWidget
{
    Q_OBJECT

public:
    explicit CircularProgressSettings(QWidget* parent = nullptr);
    ~CircularProgressSettings();

private Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::CircularProgressSettings* ui_;
};

#endif // CIRCULARPROGRESSSETTINGSEDITOR_H
