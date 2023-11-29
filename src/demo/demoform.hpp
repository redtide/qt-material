#ifndef PLUGINDEMOFORM_H
#define PLUGINDEMOFORM_H

#include <QWidget>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include "QtMaterialWidgets/dialog.hpp"

namespace Ui {
class PluginDemoForm;
}

class PluginDemoForm : public QWidget
{
    Q_OBJECT

public:
    explicit PluginDemoForm(QWidget* parent = nullptr);
    ~PluginDemoForm();

private Q_SLOTS:
    void on_qtmaterialflatbutton_3_clicked();
    void tabIndexChanged(int index);

private:
    Ui::PluginDemoForm* ui;
    MaterialDialog* m_dialog;
};

#endif // PLUGINDEMOFORM_H
