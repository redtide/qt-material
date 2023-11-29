#ifndef AUTOCOMPLETESETTINGSEDITOR_H
#define AUTOCOMPLETESETTINGSEDITOR_H

//#include "ui_autocompletesettingsform.h"

#include <QtMaterialWidgets/overlaywidget.hpp>

class MaterialAutoComplete;

class AutoCompleteSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AutoCompleteSettingsEditor(QWidget* parent = nullptr);
    ~AutoCompleteSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    //Ui::AutoCompleteSettingsForm *const ui;
    MaterialAutoComplete       *const m_autocomplete;
};

#endif // AUTOCOMPLETESETTINGSEDITOR_H
