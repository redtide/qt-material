#ifndef APPBARSETTINGS_H
#define APPBARSETTINGS_H

#include "ui_AppBarSettings.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class AppBarSettings : public QWidget
{
    Q_OBJECT

friend class MainWindow;

public:
    explicit AppBarSettings(QWidget* parent = nullptr);
    ~AppBarSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    bool event(QEvent* event) override;

    Ui::AppBarSettings* ui_;
    QLabel* lblInbox_;
};

#endif // APPBARSETTINGS_H
