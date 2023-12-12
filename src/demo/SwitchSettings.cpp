#include "SwitchSettings.hpp"

#include <QtMaterialWidgets/switch.hpp>

SwitchSettings::SwitchSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::SwitchSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->checkedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->orientationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->switch_, SIGNAL(toggled(bool)), this, SLOT(setupForm()));
}

SwitchSettings::~SwitchSettings()
{
}

void SwitchSettings::setupForm()
{
    switch (ui_->switch_->orientation())
    {
    case Qt::Horizontal:
        ui_->orientationComboBox->setCurrentIndex(0);
        break;
    case Qt::Vertical:
        ui_->orientationComboBox->setCurrentIndex(1);
        break;
    default:
        break;
    }
    ui_->disabledCheckBox->setChecked(!ui_->switch_->isEnabled());
    ui_->checkedCheckBox->setChecked(ui_->switch_->isChecked());
}

void SwitchSettings::updateWidget()
{
    switch (ui_->orientationComboBox->currentIndex())
    {
    case 0:
        ui_->switch_->setOrientation(Qt::Horizontal);
        break;
    case 1:
        ui_->switch_->setOrientation(Qt::Vertical);
        break;
    default:
        break;
    }
    ui_->switch_->setDisabled(ui_->disabledCheckBox->isChecked());
    ui_->switch_->setChecked(ui_->checkedCheckBox->isChecked());
}
