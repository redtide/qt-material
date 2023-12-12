#include "BadgeSettings.hpp"

#include <QtMaterialWidgets/avatar.hpp>
#include <QtMaterialWidgets/badge.hpp>
#include <QtMaterialWidgets/resources.hpp>

#include <QColorDialog>

namespace md = material::resources;

BadgeSettings::BadgeSettings(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::BadgeSettings)
{
    ui_->setupUi(this);
    ui_->badge->setParent(ui_->avatar);

    setupForm();

    connect(ui_->cbxType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BadgeSettings::updateWidget);
    connect(ui_->chkDisabled, &QCheckBox::toggled, this, &BadgeSettings::updateWidget);
    connect(ui_->sbxOffsetH, QOverload<int>::of(&QSpinBox::valueChanged), this, &BadgeSettings::updateWidget);
    connect(ui_->sbxOffsetV, QOverload<int>::of(&QSpinBox::valueChanged), this, &BadgeSettings::updateWidget);
}

BadgeSettings::~BadgeSettings()
{
    delete ui_;
}

void BadgeSettings::setupForm()
{
    if (ui_->badge->icon().isNull()) {
        ui_->cbxType->setCurrentIndex(0);
    } else {
        ui_->cbxType->setCurrentIndex(1);
    }
    ui_->sbxOffsetV->setValue(ui_->badge->relativeYPosition());
    ui_->sbxOffsetH->setValue(ui_->badge->relativeXPosition());
    ui_->chkDisabled->setChecked(!ui_->badge->isEnabled());
}

void BadgeSettings::updateWidget()
{
    switch (ui_->cbxType->currentIndex())
    {
    case 0:
        ui_->badge->setText("3");
        break;
    case 1:
        ui_->badge->setIcon(md::icon("communication", "message"));
        break;
    default:
        break;
    }
    ui_->badge->setRelativeYPosition(ui_->sbxOffsetV->value());
    ui_->badge->setRelativeXPosition(ui_->sbxOffsetH->value());
    ui_->badge->setDisabled(ui_->chkDisabled->isChecked());
}
