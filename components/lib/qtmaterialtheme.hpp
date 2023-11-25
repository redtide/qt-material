#ifndef QTMATERIALTHEME_H
#define QTMATERIALTHEME_H

#include <QtMaterialWidgets/defs.hpp>
#include <QtMaterialWidgets/dlimpexp.hpp>

#include <QObject>
#include <QScopedPointer>
#include <QColor>
#include <QIcon>

class QtMaterialThemePrivate;

class QtMaterialTheme : public QObject
{
    Q_OBJECT

public:
    explicit QtMaterialTheme(QObject *parent = 0);
    ~QtMaterialTheme();

    QColor getColor(const QString &key) const;

    void setColor(const QString &key, const QColor &color);
    void setColor(const QString &key, Material::Color color);

    static QIcon icon(QString category, QString icon);

protected:
    const QScopedPointer<QtMaterialThemePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTheme)
    Q_DECLARE_PRIVATE(QtMaterialTheme)
};

#endif // QTMATERIALTHEME_H
