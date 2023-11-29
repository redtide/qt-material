#ifndef MATERIAL_THEME_P_H
#define MATERIAL_THEME_P_H

#include <QColor>
#include <QHash>

class MaterialTheme;

class MaterialThemePrivate
{
    Q_DISABLE_COPY(MaterialThemePrivate)
    Q_DECLARE_PUBLIC(MaterialTheme)

public:
    MaterialThemePrivate(MaterialTheme *q);
    ~MaterialThemePrivate();

    QColor rgba(int r, int g, int b, qreal a) const;

    MaterialTheme *const q_ptr;
    QHash<QString, QColor> colors;
};

#endif // MATERIAL_THEME_P_H
