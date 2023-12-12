#include "SnackbarSettings.hpp"

#include <QtMaterialWidgets/snackbar.hpp>

#include <QColorDialog>
#include <QVBoxLayout>

SnackbarSettings::SnackbarSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::SnackbarSettings)
{
    ui_->setupUi(this);

    setupForm();

    connect(ui_->showSnackbarButton, SIGNAL(pressed()), this, SLOT(showSnackbar()));
}

SnackbarSettings::~SnackbarSettings()
{
    delete ui_;
}

void SnackbarSettings::setupForm()
{
}

void SnackbarSettings::updateWidget()
{
}

void SnackbarSettings::showSnackbar()
{
    ui_->snackbar->addMessage(QStringLiteral("Snack attack!"));
}
