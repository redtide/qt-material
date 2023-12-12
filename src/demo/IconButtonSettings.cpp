#include "IconButtonSettings.hpp"

#include <QtMaterialWidgets/iconbutton.hpp>
#include <QtMaterialWidgets/resources.hpp>

#include <QColorDialog>

namespace md = material::resources;

IconButtonSettings::IconButtonSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::IconButtonSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->disabledCheckBox, &QCheckBox::toggled, this, &IconButtonSettings::updateWidget);
    connect(ui_->sizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &IconButtonSettings::updateWidget);
}

IconButtonSettings::~IconButtonSettings()
{
    delete ui_;
}

void IconButtonSettings::setupForm()
{
    ui_->disabledCheckBox->setChecked(!ui_->iconBtn->isEnabled());
    ui_->sizeSpinBox->setValue(ui_->iconBtn->iconSize().width());
}

void IconButtonSettings::updateWidget()
{
    ui_->iconBtn->setDisabled(ui_->disabledCheckBox->isChecked());
    ui_->iconBtn->setIconSize(QSize(ui_->sizeSpinBox->value(), ui_->sizeSpinBox->value()));
}
