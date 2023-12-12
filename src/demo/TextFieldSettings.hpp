#ifndef TEXTFIELDSETTINGSEDITOR_H
#define TEXTFIELDSETTINGSEDITOR_H

#include "ui_TextFieldSettings.h"

class TextFieldSettings : public QWidget
{
    Q_OBJECT

public:
    explicit TextFieldSettings(QWidget* parent = nullptr);
    ~TextFieldSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void setShowInputLine();

private:
    Ui::TextFieldSettings* ui_;
};

#endif // TEXTFIELDSETTINGSEDITOR_H
