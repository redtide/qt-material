#include "SliderSettings.hpp"

#include <QtMaterialWidgets/slider.hpp>

#include <QVBoxLayout>

SliderSettings::SliderSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::SliderSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->valueLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui_->orientationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->invertedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->slider, SIGNAL(valueChanged(int)), this, SLOT(setupForm()));
}

SliderSettings::~SliderSettings()
{
    delete ui_;
}

void SliderSettings::setupForm()
{
    switch (ui_->slider->orientation())
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
    ui_->disabledCheckBox->setChecked(!ui_->slider->isEnabled());
    ui_->valueLineEdit->setText(QString::number(ui_->slider->value()));
    ui_->invertedCheckBox->setChecked(ui_->slider->invertedAppearance());
}

void SliderSettings::updateWidget()
{
    switch (ui_->orientationComboBox->currentIndex())
    {
    case 0:
        ui_->slider->setOrientation(Qt::Horizontal);
        break;
    case 1:
        ui_->slider->setOrientation(Qt::Vertical);
        break;
    default:
        break;
    }
    ui_->slider->setDisabled(ui_->disabledCheckBox->isChecked());
    ui_->slider->setValue(ui_->valueLineEdit->text().toInt());
    ui_->slider->setInvertedAppearance(ui_->invertedCheckBox->isChecked());
}
