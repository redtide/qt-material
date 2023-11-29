#ifndef MATERIAL_STYLE_P_H
#define MATERIAL_STYLE_P_H

#include <QtGlobal>

class MaterialStyle;
class MaterialTheme;

class MaterialStylePrivate
{
    Q_DISABLE_COPY(MaterialStylePrivate)
    Q_DECLARE_PUBLIC(MaterialStyle)

public:
    MaterialStylePrivate(MaterialStyle *q);
    ~MaterialStylePrivate();

    void init();

    MaterialStyle *const q_ptr;
    MaterialTheme *theme;
};

#endif // MATERIAL_STYLE_P_H
