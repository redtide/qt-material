#include "AutoCompleteSettings.hpp"

AutoCompleteSettings::AutoCompleteSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::AutoCompleteSettings)
{
    ui_->setupUi(this);

    setupForm();
}

AutoCompleteSettings::~AutoCompleteSettings()
{
    delete ui_;
}

void AutoCompleteSettings::setupForm()
{
}

void AutoCompleteSettings::updateWidget()
{
}
