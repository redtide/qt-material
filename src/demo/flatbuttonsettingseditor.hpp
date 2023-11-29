#ifndef FLATBUTTONSETTINGSMANAGER_H
#define FLATBUTTONSETTINGSMANAGER_H

#include <QWidget>
#include "ui_flatbuttonsettingsform.h"

class MaterialFlatButton;

class FlatButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FlatButtonSettingsEditor(QWidget* parent = nullptr);
    ~FlatButtonSettingsEditor();

protected:
    explicit FlatButtonSettingsEditor(MaterialFlatButton *button, QWidget* parent = nullptr);

    Ui::FlatButtonSettingsForm *const ui;

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();
    void applyDefaultPreset();
    void applyCheckablePreset();

private:
    void init();

    MaterialFlatButton *const m_button;
};

#endif // FLATBUTTONSETTINGSMANAGER_H
