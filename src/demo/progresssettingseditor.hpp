#ifndef PROGRESSSETTINGSEDITOR_H
#define PROGRESSSETTINGSEDITOR_H

#include <QWidget>
#include "ui_progresssettingsform.h"

class MaterialProgress;

class ProgressSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressSettingsEditor(QWidget* parent = nullptr);
    ~ProgressSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::ProgressSettingsForm *const ui;
    MaterialProgress       *const m_progress;
};

#endif // PROGRESSSETTINGSEDITOR_H
