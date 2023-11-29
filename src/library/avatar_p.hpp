#ifndef MATERIAL_AVATAR_P_H
#define MATERIAL_AVATAR_P_H

#include <QtMaterialWidgets/defs.hpp>

#include <QtGlobal>
#include <QChar>
#include <QColor>
#include <QIcon>
#include <QImage>
#include <QPixmap>

class MaterialAvatar;

class MaterialAvatarPrivate
{
    Q_DISABLE_COPY(MaterialAvatarPrivate)
    Q_DECLARE_PUBLIC(MaterialAvatar)

public:
    MaterialAvatarPrivate(MaterialAvatar *q);
    ~MaterialAvatarPrivate();

    void init();

    MaterialAvatar *const q_ptr;
    int                     size;
    Material::AvatarType    type;
    QChar                   letter;
    QImage                  image;
    QIcon                   icon;
    QPixmap                 pixmap;

    bool                    useThemeColors;
    QColor                  textColor;
    QColor                  backgroundColor;
};

#endif // MATERIAL_AVATAR_P_H
