#ifndef MATERIAL_STYLE_H
#define MATERIAL_STYLE_H

// FIXME: This should be included in cpp but gives build error if not here
#include "private/style_p.hpp"
#include "dlimpexp.hpp"

#include <QScopedPointer>
#include <QtWidgets/QCommonStyle>

class MaterialStylePrivate;
class MaterialTheme;

class QT_MATERIAL_EXPORT MaterialStyle : public QCommonStyle
{
    Q_OBJECT

public:
    inline static MaterialStyle &instance();

    void setTheme(MaterialTheme *theme);
    QColor themeColor(const QString &key) const;

protected:
    const QScopedPointer<MaterialStylePrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(MaterialStyle)

    MaterialStyle();

    MaterialStyle(MaterialStyle const &);
    void operator=(MaterialStyle const &);
};

inline MaterialStyle &MaterialStyle::instance()
{
    static MaterialStyle instance;
    return instance;
}

#endif // MATERIAL_STYLE_H
