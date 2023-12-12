#include "RadioButtonSettings.hpp"

#include <QtMaterialWidgets/radiobutton.hpp>

#include <QColorDialog>
#include <QRadioButton>
#include <QVBoxLayout>

RadioButtonSettings::RadioButtonSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::RadioButtonSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->cbxLabelPosition, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &RadioButtonSettings::updateWidget);
    connect(ui_->chkDisabled,      &QCheckBox::toggled,     this, &RadioButtonSettings::updateWidget);
    connect(ui_->txtLabelText,     &QLineEdit::textChanged, this, &RadioButtonSettings::updateWidget);
}

RadioButtonSettings::~RadioButtonSettings()
{
    delete ui_;
}

void RadioButtonSettings::setupForm()
{
    switch (ui_->radioBtn1->labelPosition())
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
    ui_->chkDisabled->setChecked(!ui_->radioBtn1->isEnabled());
    ui_->txtLabelText->setText(ui_->radioBtn1->text());
}

void RadioButtonSettings::updateWidget()
{
    switch (ui_->cbxLabelPosition->currentIndex())
    {
    case 0:
        ui_->radioBtn1->setLabelPosition(MaterialCheckable::LabelPositionLeft);
        ui_->radioBtn2->setLabelPosition(MaterialCheckable::LabelPositionLeft);
        ui_->radioBtn3->setLabelPosition(MaterialCheckable::LabelPositionLeft);
        break;
    case 1:
        ui_->radioBtn1->setLabelPosition(MaterialCheckable::LabelPositionRight);
        ui_->radioBtn2->setLabelPosition(MaterialCheckable::LabelPositionRight);
        ui_->radioBtn3->setLabelPosition(MaterialCheckable::LabelPositionRight);
        break;
    default:
        break;
    }
    ui_->radioBtn1->setDisabled(ui_->chkDisabled->isChecked());
    ui_->radioBtn1->setText(ui_->txtLabelText->text());
}
