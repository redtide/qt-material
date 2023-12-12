#include "AvatarSettings.hpp"

#include <QtMaterialWidgets/avatar.hpp>
#include <QtMaterialWidgets/resources.hpp>

#include <QColorDialog>

namespace md = material::resources;

AvatarSettings::AvatarSettings(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::AvatarSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->cbxType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AvatarSettings::updateWidget);
    connect(ui_->sbxSize, QOverload<int>::of(&QSpinBox::valueChanged),         this, &AvatarSettings::updateWidget);
    connect(ui_->chkDisabled, &QCheckBox::toggled, this, &AvatarSettings::updateWidget);
}

AvatarSettings::~AvatarSettings()
{
    delete ui_;
}

void AvatarSettings::setupForm()
{
    switch (ui_->avatar->type())
    {
    case MaterialAvatar::AvatarType::AvatarLetter:
        ui_->cbxType->setCurrentIndex(0);
        break;
    case MaterialAvatar::AvatarType::AvatarIcon:
        ui_->cbxType->setCurrentIndex(1);
        break;
    case MaterialAvatar::AvatarType::AvatarPixmap:
        ui_->cbxType->setCurrentIndex(2);
        break;
    default:
        break;
    }
    ui_->chkDisabled->setChecked(!ui_->avatar->isEnabled());
    ui_->sbxSize->setValue(ui_->avatar->size());
}

void AvatarSettings::updateWidget()
{
    switch (ui_->cbxType->currentIndex())
    {
    case 0:
        ui_->avatar->setLetter(QChar('X'));
        break;
    case 1:
        ui_->avatar->setIcon(md::icon("communication", "message"));
        break;
    case 2:
        ui_->avatar->setPixmap(QPixmap(":/images/sikh.jpg"));
        break;
    default:
        break;
    }
    ui_->avatar->setDisabled(ui_->chkDisabled->isChecked());
    ui_->avatar->setSize(ui_->sbxSize->value());
}
