#ifndef APPBARSETTINGSEDITOR_H
#define APPBARSETTINGSEDITOR_H

#include <QWidget>
#include "ui_appbarsettingsform.h"

class MaterialAppBar;

class AppBarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AppBarSettingsEditor(QWidget* parent = nullptr);
    ~AppBarSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::AppBarSettingsForm *const ui;
    MaterialAppBar       *const m_appBar;
};

#endif // APPBARSETTINGSEDITOR_H
