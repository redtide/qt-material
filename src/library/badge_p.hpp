#ifndef MATERIAL_BADGE_P_H
#define MATERIAL_BADGE_P_H

#include <QtGlobal>
#include <QIcon>
#include <QColor>
#include <QSize>

class MaterialBadge;

class MaterialBadgePrivate
{
    Q_DISABLE_COPY(MaterialBadgePrivate)
    Q_DECLARE_PUBLIC(MaterialBadge)

public:
    MaterialBadgePrivate(MaterialBadge *q);
    ~MaterialBadgePrivate();

    void init();

    MaterialBadge *const q_ptr;
    QString                text;
    QSize                  size;
    QIcon                  icon;
    qreal                  x;
    qreal                  y;
    int                    padding;

    bool                   useThemeColors;
    QColor                 textColor;
    QColor                 backgroundColor;
};

#endif // MATERIAL_BADGE_P_H
