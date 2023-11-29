#ifndef MATERIAL_CIRCULARPROGRESS_P_H
#define MATERIAL_CIRCULARPROGRESS_P_H

#include <QtMaterialWidgets/defs.hpp>

#include <QtGlobal>
#include <QColor>

class MaterialCircularProgress;
class MaterialCircularProgressDelegate;

class MaterialCircularProgressPrivate
{
    Q_DISABLE_COPY(MaterialCircularProgressPrivate)
    Q_DECLARE_PUBLIC(MaterialCircularProgress)

public:
    MaterialCircularProgressPrivate(MaterialCircularProgress *q);
    ~MaterialCircularProgressPrivate();

    void init();

    MaterialCircularProgress         *const q_ptr;
    MaterialCircularProgressDelegate *delegate;
    Material::ProgressType           progressType;
    qreal                            penWidth;
    int                              size;

    bool                             useThemeColors;
    QColor                           color;
};

#endif // MATERIAL_CIRCULARPROGRESS_P_H
