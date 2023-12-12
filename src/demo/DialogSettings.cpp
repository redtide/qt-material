#include "DialogSettings.hpp"

#include <QtMaterialWidgets/dialog.hpp>
#include <QtMaterialWidgets/flatbutton.hpp>

#include <QColorDialog>
#include <QVBoxLayout>

DialogSettings::DialogSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::DialogSettings)
{
    ui_->setupUi(this);

    QWidget* dialogWidget = new QWidget;
    QVBoxLayout* dialogWidgetLayout = new QVBoxLayout;
    dialogWidget->setLayout(dialogWidgetLayout);

    MaterialFlatButton* closeButton = new MaterialFlatButton("Close");
    dialogWidgetLayout->addWidget(closeButton);
    dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom | Qt::AlignCenter);
    closeButton->setMaximumWidth(150);

    QVBoxLayout* dialogLayout = new QVBoxLayout;
    ui_->dialog->setWindowLayout(dialogLayout);

    dialogWidget->setMinimumHeight(300);
    dialogLayout->addWidget(dialogWidget);

    setupForm();

    connect(ui_->showDialogButton, SIGNAL(pressed()), ui_->dialog, SLOT(showDialog()));
    connect(closeButton, SIGNAL(pressed()), ui_->dialog, SLOT(hideDialog()));
}

DialogSettings::~DialogSettings()
{
    delete ui_;
}

void DialogSettings::setupForm()
{
}

void DialogSettings::updateWidget()
{
}
