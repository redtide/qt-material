#include "DrawerSettings.hpp"

#include <QtMaterialWidgets/drawer.hpp>

#include <QColorDialog>
#include <QLabel>

DrawerSettings::DrawerSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::DrawerSettings)
{
    ui_->setupUi(this);
    ui_->drawer->setClickOutsideToClose(true);
    ui_->drawer->setOverlayMode(true);

    QVector<QString> labels = {"Motion", "Style", "Layout", "Components", "Patterns", "Growth & communications", "Usability", "Platforms", "Resources"};
    QVector<QString>::iterator it;
    QVBoxLayout* drawerLayout = new QVBoxLayout(ui_->drawer);
    ui_->drawer->setLayout(drawerLayout);

    for (it = labels.begin(); it != labels.end(); ++it) {
        QLabel* label = new QLabel(*it);
        label->setMinimumHeight(30);
        label->setFont(QFont("Roboto", 10, QFont::Medium));
        drawerLayout->addWidget(label);
    }
    ui_->drawer->setContentsMargins(10, 0, 0, 0);
    drawerLayout->addWidget(new QPushButton("abc"));

    setupForm();

    connect(ui_->showDrawerButton, SIGNAL(pressed()), ui_->drawer, SLOT(openDrawer()));
    connect(ui_->hideDrawerButton, SIGNAL(pressed()), ui_->drawer, SLOT(closeDrawer()));
    connect(ui_->clickToCloseCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->overlayModeCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
}

DrawerSettings::~DrawerSettings()
{
    delete ui_;
}

void DrawerSettings::setupForm()
{
    ui_->clickToCloseCheckBox->setChecked(ui_->drawer->clickOutsideToClose());
    ui_->overlayModeCheckBox->setChecked(ui_->drawer->overlayMode());
}

void DrawerSettings::updateWidget()
{
    ui_->drawer->setClickOutsideToClose(ui_->clickToCloseCheckBox->isChecked());
    ui_->drawer->setOverlayMode(ui_->overlayModeCheckBox->isChecked());
}
