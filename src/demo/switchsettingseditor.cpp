#include "switchsettingseditor.hpp"

#include <QtMaterialWidgets/switch.hpp>

#include <QColorDialog>

SwitchSettingsEditor::SwitchSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SwitchSettingsForm),
      m_switch(new MaterialSwitch)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    m_switch->setOrientation(Qt::Vertical);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_switch);
    layout->setAlignment(m_switch, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->checkedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->orientationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->disabledColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->activeColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->inactiveColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->trackColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    connect(m_switch, SIGNAL(toggled(bool)), this, SLOT(setupForm()));
}

SwitchSettingsEditor::~SwitchSettingsEditor()
{
}

void SwitchSettingsEditor::setupForm()
{
    switch (m_switch->orientation())
    {
    case Qt::Horizontal:
        ui->orientationComboBox->setCurrentIndex(0);
        break;
    case Qt::Vertical:
        ui->orientationComboBox->setCurrentIndex(1);
        break;
    default:
        break;
    }

    ui->disabledCheckBox->setChecked(!m_switch->isEnabled());
    ui->checkedCheckBox->setChecked(m_switch->isChecked());
    ui->useThemeColorsCheckBox->setChecked(m_switch->useThemeColors());
}

void SwitchSettingsEditor::updateWidget()
{
    switch (ui->orientationComboBox->currentIndex())
    {
    case 0:
        m_switch->setOrientation(Qt::Horizontal);
        break;
    case 1:
        m_switch->setOrientation(Qt::Vertical);
        break;
    default:
        break;
    }

    m_switch->setDisabled(ui->disabledCheckBox->isChecked());
    m_switch->setChecked(ui->checkedCheckBox->isChecked());
    m_switch->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void SwitchSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("disabledColorToolButton" == senderName) {
            m_switch->setDisabledColor(color);
            ui->disabledColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("activeColorToolButton" == senderName) {
            m_switch->setActiveColor(color);
            ui->activeColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("inactiveColorToolButton" == senderName) {
            m_switch->setInactiveColor(color);
            ui->inactiveColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("trackColorToolButton" == senderName) {
            m_switch->setTrackColor(color);
            ui->trackColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
