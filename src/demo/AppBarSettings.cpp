#include "AppBarSettings.hpp"

#include <QtMaterialWidgets/appbar.hpp>
#include <QtMaterialWidgets/iconbutton.hpp>
#include <QtMaterialWidgets/resources.hpp>
#include <QtMaterialWidgets/style.hpp>

#include <QLabel>

namespace md = material::resources;

AppBarSettings::AppBarSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::AppBarSettings)
{
    ui_->setupUi(this);

    QVBoxLayout*        layAppBar = static_cast<QVBoxLayout*>(ui_->appBar->layout());
    MaterialIconButton* icnButton = new MaterialIconButton(md::icon("navigation", "menu"), ui_->appBar);
                        lblInbox_ = new QLabel("Title", ui_->appBar);

//  Material::updatePalette(lblInbox_);

    icnButton->setFixedWidth(42);
    icnButton->setIconSize(QSize(24, 24));

    layAppBar->addWidget(icnButton);
    layAppBar->addWidget(lblInbox_);
    layAppBar->addStretch(1);
}

AppBarSettings::~AppBarSettings()
{
    delete ui_;
}

void AppBarSettings::setupForm()
{
}

void AppBarSettings::updateWidget()
{
}

bool AppBarSettings::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
//      Material::updatePalette(lblInbox_);
        return true;
    }
    return QWidget::event(event);
}
