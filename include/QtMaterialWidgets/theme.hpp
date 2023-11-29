#ifndef MATERIAL_THEME_H
#define MATERIAL_THEME_H

#include "defs.hpp"
#include "dlimpexp.hpp"

#include <QColor>
#include <QIcon>
#include <QScopedPointer>

class MaterialThemePrivate;

class QT_MATERIAL_EXPORT MaterialTheme : public QObject
{
    Q_OBJECT

public:
    explicit MaterialTheme(QObject* parent = nullptr);
    ~MaterialTheme();

    QColor getColor(const QString &key) const;

    void setColor(const QString &key, const QColor &color);
    void setColor(const QString &key, Material::Color color);

    static QIcon icon(QString category, QString icon);

protected:
    const QScopedPointer<MaterialThemePrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialTheme)
    Q_DECLARE_PRIVATE(MaterialTheme)
};

#endif // MATERIAL_THEME_H
