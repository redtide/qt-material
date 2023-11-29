#ifndef MATERIAL_PROGRESS_P_H
#define MATERIAL_PROGRESS_P_H

#include <QtMaterialWidgets/defs.hpp>

#include <QtGlobal>
#include <QColor>

class MaterialProgress;
class MaterialProgressDelegate;

class MaterialProgressPrivate
{
    Q_DISABLE_COPY(MaterialProgressPrivate)
    Q_DECLARE_PUBLIC(MaterialProgress)

public:
    MaterialProgressPrivate(MaterialProgress *q);
    ~MaterialProgressPrivate();

    void init();

    MaterialProgress         *const q_ptr;
    MaterialProgressDelegate *delegate;
    Material::ProgressType   progressType;
    QColor                   progressColor;

    bool                     useThemeColors;
    QColor                   backgroundColor;
};

#endif // MATERIAL_PROGRESS_P_H
