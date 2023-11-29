#ifndef SCROLLBARSETTINGSEDITOR_H
#define SCROLLBARSETTINGSEDITOR_H

#include <QWidget>
#include "ui_scrollbarsettingsform.h"

class MaterialScrollBar;

class ScrollBarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollBarSettingsEditor(QWidget* parent = nullptr);
    ~ScrollBarSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();

private:
    Ui::ScrollBarSettingsForm *const ui;
    MaterialScrollBar       *const m_verticalScrollbar;
    MaterialScrollBar       *const m_horizontalScrollbar;
};

#endif // SCROLLBARSETTINGSEDITOR_H
