#include "CheckBoxSettings.hpp"

#include <QtMaterialWidgets/checkbox.hpp>

#include <QVBoxLayout>
#include <QColorDialog>

CheckBoxSettings::CheckBoxSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::CheckBoxSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->cbxLabelPosition,  QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CheckBoxSettings::updateWidget);
    connect(ui_->checkBox,          &MaterialCheckBox::toggled, this, &CheckBoxSettings::setupForm);
    connect(ui_->chkDisabled,       &QCheckBox::toggled,        this, &CheckBoxSettings::updateWidget);
    connect(ui_->chkChecked,        &QCheckBox::toggled,        this, &CheckBoxSettings::updateWidget);
    connect(ui_->txtLabelText,      &QLineEdit::textChanged,    this, &CheckBoxSettings::updateWidget);
}

CheckBoxSettings::~CheckBoxSettings()
{
    delete ui_;
}

void CheckBoxSettings::setupForm()
{
    switch (ui_->checkBox->labelPosition())
    {
    case MaterialCheckable::LabelPositionLeft:
        ui_->cbxLabelPosition->setCurrentIndex(0);
        break;
    case MaterialCheckable::LabelPositionRight:
        ui_->cbxLabelPosition->setCurrentIndex(1);
        break;
    default:
        break;
    }
    ui_->chkDisabled->setChecked(!ui_->checkBox->isEnabled());
    ui_->txtLabelText->setText(ui_->checkBox->text());
    ui_->chkChecked->setChecked(ui_->checkBox->isChecked());
}

void CheckBoxSettings::updateWidget()
{
    switch (ui_->cbxLabelPosition->currentIndex())
    {
    case 0:
        ui_->checkBox->setLabelPosition(MaterialCheckable::LabelPositionLeft);
        break;
    case 1:
        ui_->checkBox->setLabelPosition(MaterialCheckable::LabelPositionRight);
        break;
    default:
        break;
    }
    ui_->checkBox->setDisabled(ui_->chkDisabled->isChecked());
    ui_->checkBox->setText(ui_->txtLabelText->text());
    ui_->checkBox->setChecked(ui_->chkChecked->isChecked());
}
