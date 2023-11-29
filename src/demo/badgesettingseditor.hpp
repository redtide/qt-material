#ifndef BADGESETTINGSEDITOR_H
#define BADGESETTINGSEDITOR_H

#include <QWidget>
#include "ui_badgesettingsform.h"

class MaterialAvatar;
class MaterialBadge;

class BadgeSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BadgeSettingsEditor(QWidget* parent = nullptr);
    ~BadgeSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::BadgeSettingsForm *const ui;
    MaterialAvatar      *const m_avatar;
    MaterialBadge       *const m_badge;
};

#endif // BADGESETTINGSEDITOR_H
