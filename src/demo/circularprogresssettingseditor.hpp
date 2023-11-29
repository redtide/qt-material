#ifndef CIRCULARPROGRESSSETTINGSEDITOR_H
#define CIRCULARPROGRESSSETTINGSEDITOR_H

#include <QWidget>
#include "ui_circularprogresssettingsform.h"

class MaterialCircularProgress;

class CircularProgressSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CircularProgressSettingsEditor(QWidget* parent = nullptr);
    ~CircularProgressSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::CircularProgressSettingsForm *const ui;
    MaterialCircularProgress       *const m_progress;
};

#endif // CIRCULARPROGRESSSETTINGSEDITOR_H
