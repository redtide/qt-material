#ifndef TABSSETTINGSEDITOR_H
#define TABSSETTINGSEDITOR_H

#include "ui_TabsSettings.h"

class TabsSettings : public QWidget
{
    Q_OBJECT

public:
    explicit TabsSettings(QWidget* parent = nullptr);
    ~TabsSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::TabsSettings* ui_;
};

#endif // TABSSETTINGSEDITOR_H
