#ifndef SCROLLBARSETTINGSEDITOR_H
#define SCROLLBARSETTINGSEDITOR_H

#include "ui_ScrollBarSettings.h"

class MaterialScrollBar;

class ScrollBarSettings : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollBarSettings(QWidget* parent = nullptr);
    ~ScrollBarSettings();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::ScrollBarSettings* ui_;
    MaterialScrollBar*     vScrollbar_;
    MaterialScrollBar*     hScrollbar_;
};

#endif // SCROLLBARSETTINGSEDITOR_H
