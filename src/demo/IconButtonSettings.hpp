#ifndef ICONBUTTONSETTINGSMANAGER_H
#define ICONBUTTONSETTINGSMANAGER_H

#include "ui_IconButtonSettings.h"

class IconButtonSettings : public QWidget
{
    Q_OBJECT

public:
    explicit IconButtonSettings(QWidget* parent = nullptr);
    ~IconButtonSettings();

private Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::IconButtonSettings* ui_;
};

#endif // ICONBUTTONSETTINGSMANAGER_H
