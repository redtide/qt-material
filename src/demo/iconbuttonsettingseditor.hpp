#ifndef ICONBUTTONSETTINGSMANAGER_H
#define ICONBUTTONSETTINGSMANAGER_H

#include <QWidget>
#include "ui_iconbuttonsettingsform.h"

class MaterialIconButton;

class IconButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit IconButtonSettingsEditor(QWidget* parent = nullptr);
    ~IconButtonSettingsEditor();

protected:
    explicit IconButtonSettingsEditor(MaterialIconButton *button, QWidget* parent = nullptr);

    Ui::IconButtonSettingsForm *const ui;

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    void init();

    MaterialIconButton *const m_button;
};

#endif // ICONBUTTONSETTINGSMANAGER_H
