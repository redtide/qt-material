#ifndef MATERIAL_AVATAR_P_H
#define MATERIAL_AVATAR_P_H

#include <QtMaterialWidgets/avatar.hpp>

#include <QtGlobal>
#include <QChar>
#include <QColor>
#include <QIcon>
#include <QPixmap>

class MaterialAvatarPrivate
{
    Q_DISABLE_COPY(MaterialAvatarPrivate)
    Q_DECLARE_PUBLIC(MaterialAvatar)

public:
    MaterialAvatarPrivate(MaterialAvatar* q);
    ~MaterialAvatarPrivate();

    void init();

    MaterialAvatar* const      q_ptr;
    MaterialAvatar::AvatarType type;
    int     size;
    QChar   letter;
    QIcon   icon;
    QPixmap pixmap;
};

#endif // MATERIAL_AVATAR_P_H
