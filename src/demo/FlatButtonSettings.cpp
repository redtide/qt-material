#include "FlatButtonSettings.hpp"

#include <QtMaterialWidgets/flatbutton.hpp>
#include <QtMaterialWidgets/resources.hpp>

#include <QColorDialog>
#include <QDebug>

namespace md = material::resources;

FlatButtonSettings::FlatButtonSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::FlatButtonSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->checkableCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->checkedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->showHaloCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->iconCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->transparentCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->buttonRoleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->rippleStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->hoverStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->iconPlacementComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->textAlignmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->cornerRadiusSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->overlayOpacityDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui_->iconSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->fontSizeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui_->buttonTextLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui_->cornerRadiusSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->overlayOpacityDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui_->iconSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui_->fontSizeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui_->buttonTextLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui_->defaultPresetPushButton, SIGNAL(pressed()), this, SLOT(applyDefaultPreset()));
    connect(ui_->checkablePresetPushButton, SIGNAL(pressed()), this, SLOT(applyCheckablePreset()));
    connect(ui_->flatBtn, SIGNAL(clicked(bool)), ui_->checkedCheckBox, SLOT(setChecked(bool)));

    ui_->buttonRoleComboBox->setCurrentIndex(1);
}

FlatButtonSettings::~FlatButtonSettings()
{
    delete ui_;
}

void FlatButtonSettings::setupForm()
{
    switch (ui_->flatBtn->role())
    {
    case Material::Default:
        ui_->buttonRoleComboBox->setCurrentIndex(0);
        break;
    case Material::Primary:
        ui_->buttonRoleComboBox->setCurrentIndex(1);
        break;
    case Material::Secondary:
        ui_->buttonRoleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (ui_->flatBtn->overlayStyle())
    {
    case Material::NoOverlay:
        ui_->hoverStyleComboBox->setCurrentIndex(0);
        break;
    case Material::TintedOverlay:
        ui_->hoverStyleComboBox->setCurrentIndex(1);
        break;
    case Material::GrayOverlay:
        ui_->hoverStyleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (ui_->flatBtn->rippleStyle())
    {
    case Material::CenteredRipple:
        ui_->rippleStyleComboBox->setCurrentIndex(0);
        break;
    case Material::PositionedRipple:
        ui_->rippleStyleComboBox->setCurrentIndex(1);
        break;
    case Material::NoRipple:
        ui_->rippleStyleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (ui_->flatBtn->iconPlacement())
    {
    case Material::LeftIcon:
        ui_->iconPlacementComboBox->setCurrentIndex(0);
        break;
    case Material::RightIcon:
        ui_->iconPlacementComboBox->setCurrentIndex(1);
        break;
    }

    switch (ui_->textAlignmentComboBox->currentIndex())
    {
    case Qt::AlignLeft:
        ui_->textAlignmentComboBox->setCurrentIndex(0);
        break;
    default:
        ui_->textAlignmentComboBox->setCurrentIndex(1);
    }

    ui_->checkedCheckBox->setEnabled(ui_->flatBtn->isCheckable());

    ui_->disabledCheckBox->setChecked(!ui_->flatBtn->isEnabled());
    ui_->checkableCheckBox->setChecked(ui_->flatBtn->isCheckable());
    ui_->checkedCheckBox->setChecked(ui_->flatBtn->isChecked());
    ui_->showHaloCheckBox->setChecked(ui_->flatBtn->isHaloVisible());
    ui_->iconCheckBox->setChecked(!ui_->flatBtn->icon().isNull());
    ui_->transparentCheckBox->setChecked(Qt::TransparentMode == ui_->flatBtn->backgroundMode());
    ui_->cornerRadiusSpinBox->setValue(ui_->flatBtn->cornerRadius());
    ui_->overlayOpacityDoubleSpinBox->setValue(ui_->flatBtn->baseOpacity());
    ui_->iconSizeSpinBox->setValue(ui_->flatBtn->iconSize().width());
    ui_->fontSizeDoubleSpinBox->setValue(ui_->flatBtn->fontSize());
    ui_->buttonTextLineEdit->setText(ui_->flatBtn->text());
}

void FlatButtonSettings::updateWidget()
{
    switch (ui_->buttonRoleComboBox->currentIndex())
    {
    case 0:
        ui_->flatBtn->setRole(Material::Default);
        break;
    case 1:
        ui_->flatBtn->setRole(Material::Primary);
        break;
    case 2:
        ui_->flatBtn->setRole(Material::Secondary);
        break;
    default:
        break;
    }

    switch (ui_->hoverStyleComboBox->currentIndex())
    {
    case 0:
        ui_->flatBtn->setOverlayStyle(Material::NoOverlay);
        break;
    case 1:
        ui_->flatBtn->setOverlayStyle(Material::TintedOverlay);
        break;
    case 2:
        ui_->flatBtn->setOverlayStyle(Material::GrayOverlay);
        break;
    default:
        break;
    }

    switch (ui_->rippleStyleComboBox->currentIndex())
    {
    case 0:
        ui_->flatBtn->setRippleStyle(Material::CenteredRipple);
        break;
    case 1:
        ui_->flatBtn->setRippleStyle(Material::PositionedRipple);
        break;
    case 2:
        ui_->flatBtn->setRippleStyle(Material::NoRipple);
        break;
    default:
        break;
    }

    switch (ui_->iconPlacementComboBox->currentIndex())
    {
    case 0:
        ui_->flatBtn->setIconPlacement(Material::LeftIcon);
        break;
    case 1:
        ui_->flatBtn->setIconPlacement(Material::RightIcon);
        break;
    default:
        break;
    }

    switch (ui_->textAlignmentComboBox->currentIndex())
    {
    case 0:
        ui_->flatBtn->setTextAlignment(Qt::AlignLeft);
        break;
    case 1:
    default:
        ui_->flatBtn->setTextAlignment(Qt::AlignHCenter);
        break;
    }

    ui_->flatBtn->setDisabled(ui_->disabledCheckBox->isChecked());
    ui_->flatBtn->setCheckable(ui_->checkableCheckBox->isChecked());
    ui_->flatBtn->setChecked(ui_->checkedCheckBox->isChecked());
    ui_->flatBtn->setHaloVisible(ui_->showHaloCheckBox->isChecked());
    ui_->flatBtn->setIcon(ui_->iconCheckBox->isChecked() ? md::icon("toggle", "star") : QIcon());
    ui_->flatBtn->setBackgroundMode(ui_->transparentCheckBox->isChecked()
                                    ? Qt::TransparentMode : Qt::OpaqueMode);
    ui_->flatBtn->setCornerRadius(ui_->cornerRadiusSpinBox->value());
    ui_->flatBtn->setBaseOpacity(ui_->overlayOpacityDoubleSpinBox->value());
    ui_->flatBtn->setIconSize(QSize(ui_->iconSizeSpinBox->value(), ui_->iconSizeSpinBox->value()));
    ui_->flatBtn->setFontSize(ui_->fontSizeDoubleSpinBox->value());
    ui_->flatBtn->setText(ui_->buttonTextLineEdit->text());

    ui_->checkedCheckBox->setEnabled(ui_->flatBtn->isCheckable());
}

void FlatButtonSettings::applyDefaultPreset()
{
    ui_->buttonRoleComboBox->setCurrentIndex(0);
    ui_->rippleStyleComboBox->setCurrentIndex(1);
    ui_->iconPlacementComboBox->setCurrentIndex(0);
    ui_->hoverStyleComboBox->setCurrentIndex(2);
    ui_->textAlignmentComboBox->setCurrentIndex(1);
    ui_->transparentCheckBox->setChecked(true);
    ui_->cornerRadiusSpinBox->setValue(3);
    ui_->overlayOpacityDoubleSpinBox->setValue(0.13);
    ui_->fontSizeDoubleSpinBox->setValue(10);
    ui_->showHaloCheckBox->setChecked(true);
    ui_->checkableCheckBox->setChecked(false);
    ui_->disabledCheckBox->setChecked(false);
    updateWidget();
    ui_->flatBtn->applyPreset(Material::FlatPreset);
}

void FlatButtonSettings::applyCheckablePreset()
{
    ui_->buttonRoleComboBox->setCurrentIndex(0);
    ui_->rippleStyleComboBox->setCurrentIndex(1);
    ui_->iconPlacementComboBox->setCurrentIndex(0);
    ui_->hoverStyleComboBox->setCurrentIndex(2);
    ui_->textAlignmentComboBox->setCurrentIndex(1);
    ui_->transparentCheckBox->setChecked(true);
    ui_->cornerRadiusSpinBox->setValue(3);
    ui_->overlayOpacityDoubleSpinBox->setValue(0.13);
    ui_->fontSizeDoubleSpinBox->setValue(10);
    ui_->showHaloCheckBox->setChecked(true);
    ui_->checkableCheckBox->setChecked(true);
    ui_->disabledCheckBox->setChecked(false);
    updateWidget();
    ui_->flatBtn->applyPreset(Material::CheckablePreset);
}
