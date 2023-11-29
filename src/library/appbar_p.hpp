#ifndef MATERIAL_APPBAR_P_H
#define MATERIAL_APPBAR_P_H

#include <QtGlobal>
#include <QColor>

class MaterialAppBar;

class MaterialAppBarPrivate
{
    Q_DISABLE_COPY(MaterialAppBarPrivate)
    Q_DECLARE_PUBLIC(MaterialAppBar)

public:
    MaterialAppBarPrivate(MaterialAppBar *q);
    ~MaterialAppBarPrivate();

    void init();

    MaterialAppBar *const q_ptr;

    bool                    useThemeColors;
    QColor                  foregroundColor;
    QColor                  backgroundColor;
};

#endif // MATERIAL_APPBAR_P_H
