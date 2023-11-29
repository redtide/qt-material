#include "raisedbuttonsettingseditor.hpp"

#include <QtMaterialWidgets/raisedbutton.hpp>

RaisedButtonSettingsEditor::RaisedButtonSettingsEditor(QWidget *parent)
    : FlatButtonSettingsEditor(new MaterialRaisedButton("Rise up"), parent)
{
    ui->transparentCheckBox->setDisabled(true);
    ui->defaultPresetPushButton->setDisabled(true);
    ui->checkablePresetPushButton->setDisabled(true);
}

RaisedButtonSettingsEditor::~RaisedButtonSettingsEditor()
{
}
