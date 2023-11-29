#ifndef SLIDERSETTINGSEDITOR_H
#define SLIDERSETTINGSEDITOR_H

#include <QWidget>
#include "ui_slidersettingsform.h"

class MaterialSlider;

class SliderSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SliderSettingsEditor(QWidget* parent = nullptr);
    ~SliderSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::SliderSettingsForm *const ui;
    MaterialSlider       *const m_slider;
};

#endif // SLIDERSETTINGSEDITOR_H
