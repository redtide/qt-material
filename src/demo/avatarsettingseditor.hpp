#ifndef AVATARSETTINGSEDITOR_H
#define AVATARSETTINGSEDITOR_H

#include <QWidget>
#include "ui_avatarsettingsform.h"

class MaterialAvatar;

class AvatarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AvatarSettingsEditor(QWidget* parent = nullptr);
    ~AvatarSettingsEditor();

protected Q_SLOTS:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::AvatarSettingsForm *const ui;
    MaterialAvatar       *const m_avatar;
};

#endif // AVATARSETTINGSEDITOR_H
