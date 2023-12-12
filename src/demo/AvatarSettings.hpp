#ifndef AVATARSETTINGSEDITOR_H
#define AVATARSETTINGSEDITOR_H

#include "ui_AvatarSettings.h"

class AvatarSettings : public QWidget
{
    Q_OBJECT

public:
    explicit AvatarSettings(QWidget* parent = nullptr);
    ~AvatarSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::AvatarSettings* ui_;
};

#endif // AVATARSETTINGSEDITOR_H
