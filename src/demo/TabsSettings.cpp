#include "TabsSettings.hpp"

#include <QtMaterialWidgets/tabs.hpp>

#include <QColorDialog>

TabsSettings::TabsSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::TabsSettings)
{
    ui_->setupUi(this);

    setupForm();
}

TabsSettings::~TabsSettings()
{
    delete ui_;
}

void TabsSettings::setupForm()
{
}

void TabsSettings::updateWidget()
{
}
