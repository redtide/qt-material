#ifndef BADGESETTINGSEDITOR_H
#define BADGESETTINGSEDITOR_H

#include "ui_BadgeSettings.h"

class BadgeSettings : public QWidget
{
    Q_OBJECT

public:
    explicit BadgeSettings(QWidget* parent = nullptr);
    ~BadgeSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::BadgeSettings* ui_;
};

#endif // BADGESETTINGSEDITOR_H
