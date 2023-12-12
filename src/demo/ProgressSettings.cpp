#include "ProgressSettings.hpp"

#include <QtMaterialWidgets/progress.hpp>

#include <QCheckBox>
#include <QComboBox>

ProgressSettings::ProgressSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ProgressSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->chkDisabled, &QCheckBox::toggled, this, &ProgressSettings::updateWidget);
    connect(ui_->cbxProgressType, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &ProgressSettings::updateWidget);
    connect(ui_->sldValue, &QSlider::valueChanged, this, &ProgressSettings::updateWidget);
}

ProgressSettings::~ProgressSettings()
{
    delete ui_;
}

void ProgressSettings::setupForm()
{
    switch (ui_->progress->progressType())
    {
    case Material::DeterminateProgress:
        ui_->cbxProgressType->setCurrentIndex(0);
        break;
    case Material::IndeterminateProgress:
        ui_->cbxProgressType->setCurrentIndex(1);
        break;
    default:
        break;
    }
    ui_->chkDisabled->setChecked(!ui_->progress->isEnabled());
    ui_->progress->setValue(ui_->sldValue->value());
}

void ProgressSettings::updateWidget()
{
    switch (ui_->cbxProgressType->currentIndex())
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
    ui_->progress->setDisabled(ui_->chkDisabled->isChecked());
    ui_->progress->setValue(ui_->sldValue->value());
}
