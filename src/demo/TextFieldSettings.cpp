#include "TextFieldSettings.hpp"

#include <QtMaterialWidgets/textfield.hpp>

#include <QLineEdit>
#include <QVBoxLayout>

TextFieldSettings::TextFieldSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::TextFieldSettings)
{
    ui_->setupUi(this);
    ui_->textField->setLabel("What is this");

    setupForm();

    connect(ui_->chkDisabled, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->chkInputLine, SIGNAL(toggled(bool)), this, SLOT(setShowInputLine()));
    connect(ui_->chkLabel, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui_->txtLabel, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui_->txtPlaceholder, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui_->txtText, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui_->textField, SIGNAL(textChanged(QString)), this, SLOT(setupForm()));
}

TextFieldSettings::~TextFieldSettings()
{
    delete ui_;
}

void TextFieldSettings::setupForm()
{
    ui_->chkDisabled->setChecked(!ui_->textField->isEnabled());
    ui_->txtText->setText(ui_->textField->text());
    ui_->txtPlaceholder->setText(ui_->textField->placeholderText());
    ui_->chkLabel->setChecked(ui_->textField->hasLabel());
    ui_->txtLabel->setText(ui_->textField->label());
    ui_->chkInputLine->setChecked(ui_->textField->hasInputLine());
}

void TextFieldSettings::updateWidget()
{
    ui_->textField->setDisabled(ui_->chkDisabled->isChecked());
    ui_->textField->setText(ui_->txtText->text());
    ui_->textField->setPlaceholderText(ui_->txtPlaceholder->text());
    ui_->textField->setLabel(ui_->txtLabel->text());
    ui_->textField->setShowLabel(ui_->chkLabel->isChecked());
    ui_->textField->setShowInputLine(ui_->chkInputLine->isChecked());
}

void TextFieldSettings::setShowInputLine()
{
    ui_->textField->setShowInputLine( ui_->chkInputLine->isChecked() );
}
