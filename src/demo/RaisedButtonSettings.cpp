#include "RaisedButtonSettings.hpp"

#include <QtMaterialWidgets/raisedbutton.hpp>

RaisedButtonSettings::RaisedButtonSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::RaisedButtonSettings)
{
    ui_->setupUi(this);

    setupForm();
}

RaisedButtonSettings::~RaisedButtonSettings()
{
}

void RaisedButtonSettings::setupForm()
{
}

void RaisedButtonSettings::updateWidget()
{
}
