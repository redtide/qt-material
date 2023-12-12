#include "FABSettings.hpp"

#include <QtMaterialWidgets/fab.hpp>
#include <QtMaterialWidgets/resources.hpp>

#include <QDebug>
#include <QColorDialog>
#include <QVBoxLayout>

FABSettings::FABSettings(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::FABSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->chkDisabled,         &QCheckBox::toggled, this, &FABSettings::updateWidget);
    connect(ui_->chkMini,             &QCheckBox::toggled, this, &FABSettings::updateWidget);
    connect(ui_->cbxButtonRole,       &QComboBox::currentIndexChanged, this, &FABSettings::updateWidget);
    connect(ui_->cbxCorner,           &QComboBox::currentIndexChanged, this, &FABSettings::updateWidget);
    connect(ui_->cbxRippleStyle,      &QComboBox::currentIndexChanged, this, &FABSettings::updateWidget);
    connect(ui_->sbxHorizontalOffset, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FABSettings::updateWidget);
    connect(ui_->sbxVerticalOffset,   QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FABSettings::updateWidget);
}

FABSettings::~FABSettings()
{
    delete ui_;
}

void FABSettings::setupForm()
{
    switch (ui_->fab->role())
    {
    case Material::Default:
        ui_->cbxButtonRole->setCurrentIndex(0);
        break;
    case Material::Primary:
        ui_->cbxButtonRole->setCurrentIndex(1);
        break;
    case Material::Secondary:
        ui_->cbxButtonRole->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (ui_->fab->corner())
    {
    case Qt::TopLeftCorner:
        ui_->cbxCorner->setCurrentIndex(0);
        break;
    case Qt::TopRightCorner:
        ui_->cbxCorner->setCurrentIndex(1);
        break;
    case Qt::BottomLeftCorner:
        ui_->cbxCorner->setCurrentIndex(2);
        break;
    case Qt::BottomRightCorner:
        ui_->cbxCorner->setCurrentIndex(3);
        break;
    default:
        break;
    }

    switch (ui_->fab->rippleStyle())
    {
    case Material::CenteredRipple:
        ui_->cbxRippleStyle->setCurrentIndex(0);
        break;
    case Material::PositionedRipple:
        ui_->cbxRippleStyle->setCurrentIndex(1);
        break;
    case Material::NoRipple:
        ui_->cbxRippleStyle->setCurrentIndex(2);
        break;
    default:
        break;
    }
    ui_->chkDisabled->setChecked(!ui_->fab->isEnabled());
    ui_->sbxHorizontalOffset->setValue(ui_->fab->xOffset());
    ui_->sbxVerticalOffset->setValue(ui_->fab->yOffset());
    ui_->chkMini->setChecked(ui_->fab->isMini());
}

void FABSettings::updateWidget()
{
    switch (ui_->cbxButtonRole->currentIndex())
    {
    case 0:
        ui_->fab->setRole(Material::Default);
        break;
    case 1:
        ui_->fab->setRole(Material::Primary);
        break;
    case 2:
        ui_->fab->setRole(Material::Secondary);
        break;
    default:
        break;
    }

    switch (ui_->cbxCorner->currentIndex())
    {
    case 0:
        ui_->fab->setCorner(Qt::TopLeftCorner);
        break;
    case 1:
        ui_->fab->setCorner(Qt::TopRightCorner);
        break;
    case 2:
        ui_->fab->setCorner(Qt::BottomLeftCorner);
        break;
    case 3:
        ui_->fab->setCorner(Qt::BottomRightCorner);
        break;
    default:
        break;
    }

    switch (ui_->cbxRippleStyle->currentIndex())
    {
    case 0:
        ui_->fab->setRippleStyle(Material::CenteredRipple);
        break;
    case 1:
        ui_->fab->setRippleStyle(Material::PositionedRipple);
        break;
    case 2:
        ui_->fab->setRippleStyle(Material::NoRipple);
        break;
    default:
        break;
    }
    ui_->fab->setDisabled(ui_->chkDisabled->isChecked());
    ui_->fab->setXOffset(ui_->sbxHorizontalOffset->value());
    ui_->fab->setYOffset(ui_->sbxVerticalOffset->value());
    ui_->fab->setMini(ui_->chkMini->isChecked());
}
