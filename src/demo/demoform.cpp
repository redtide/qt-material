#include "demoform.hpp"
#include "ui_demoform.h"

#include <QtMaterialWidgets/flatbutton.hpp>

#include <QMessageBox>

PluginDemoForm::PluginDemoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginDemoForm)
{
    ui->setupUi(this);

//    QStringList list1 = {"Hello", "Material", "Auto Complete"};
//    ui->qtmaterialautocomplete->setDataSource(list1);

    m_dialog = new MaterialDialog;
    m_dialog->setParent(this);

    QWidget *dialogWidget = new QWidget;
    QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;
    dialogWidget->setLayout(dialogWidgetLayout);

    MaterialFlatButton *closeButton = new MaterialFlatButton("Close");
    dialogWidgetLayout->addWidget(closeButton);
    dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom | Qt::AlignCenter);

    closeButton->setMaximumWidth(150);

    QVBoxLayout *dialogLayout = new QVBoxLayout;
    m_dialog->setWindowLayout(dialogLayout);

    dialogWidget->setMinimumHeight(300);

    dialogLayout->addWidget(dialogWidget);

    connect(closeButton, SIGNAL(pressed()), m_dialog, SLOT(hideDialog()));
}

PluginDemoForm::~PluginDemoForm()
{
    delete ui;
}

void PluginDemoForm::on_qtmaterialflatbutton_3_clicked()
{
    m_dialog->showDialog();
}

void PluginDemoForm::tabIndexChanged(int index)
{
}
