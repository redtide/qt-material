#include "CircularProgressSettings.hpp"

#include <QtMaterialWidgets/circularprogress.hpp>

#include <QColorDialog>
#include <QVBoxLayout>

CircularProgressSettings::CircularProgressSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::CircularProgressSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->progressTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CircularProgressSettings::updateWidget);
    connect(ui_->sizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &CircularProgressSettings::updateWidget);
    connect(ui_->lineWidthDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &CircularProgressSettings::updateWidget);
    connect(ui_->disabledCheckBox, &QCheckBox::toggled,    this, &CircularProgressSettings::updateWidget);
    connect(ui_->progressSlider,   &QSlider::valueChanged, this, &CircularProgressSettings::updateWidget);
}

CircularProgressSettings::~CircularProgressSettings()
{
    delete ui_;
}

void CircularProgressSettings::setupForm()
{
    switch (ui_->progress->progressType())
    {
    case Material::DeterminateProgress:
        ui_->progressTypeComboBox->setCurrentIndex(0);
        break;
    case Material::IndeterminateProgress:
        ui_->progressTypeComboBox->setCurrentIndex(1);
        break;
    default:
        break;
    }
    ui_->disabledCheckBox->setChecked(!ui_->progress->isEnabled());
    ui_->progressSlider->setValue(ui_->progress->value());
    ui_->lineWidthDoubleSpinBox->setValue(ui_->progress->lineWidth());
    ui_->sizeSpinBox->setValue(ui_->progress->size());
}

void CircularProgressSettings::updateWidget()
{
    switch (ui_->progressTypeComboBox->currentIndex())
    {
    case 0:
        ui_->progress->setProgressType(Material::DeterminateProgress);
        break;
    case 1:
        ui_->progress->setProgressType(Material::IndeterminateProgress);
        break;
    default:
        break;
    }
    ui_->progress->setDisabled(ui_->disabledCheckBox->isChecked());
    ui_->progress->setValue(ui_->progressSlider->value());
    ui_->progress->setLineWidth(ui_->lineWidthDoubleSpinBox->value());
    ui_->progress->setSize(ui_->sizeSpinBox->value());
}
