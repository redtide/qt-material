// FIXME: move style_p.hpp
#include <QtMaterialWidgets/private/style_p.hpp>

#include <QtMaterialWidgets/theme.hpp>
#include <QtMaterialWidgets/style.hpp>

#include <QFontDatabase>

/*!
 *  \class MaterialStylePrivate
 *  \internal
 */

MaterialStylePrivate::MaterialStylePrivate(MaterialStyle *q)
    : q_ptr(q)
{
}

MaterialStylePrivate::~MaterialStylePrivate()
{
}

void MaterialStylePrivate::init()
{
    Q_Q(MaterialStyle);

    QFontDatabase::addApplicationFont(":/fonts/roboto_regular");
    QFontDatabase::addApplicationFont(":/fonts/roboto_medium");
    QFontDatabase::addApplicationFont(":/fonts/roboto_bold");

    q->setTheme(new MaterialTheme);
}

/*!
 *  \class MaterialStyle
 *  \internal
 */

void MaterialStyle::setTheme(MaterialTheme *theme)
{
    Q_D(MaterialStyle);

    d->theme = theme;
    theme->setParent(this);
}

QColor MaterialStyle::themeColor(const QString &key) const
{
    Q_D(const MaterialStyle);

    Q_ASSERT(d->theme);

    return d->theme->getColor(key);
}

MaterialStyle::MaterialStyle()
    : QCommonStyle(),
      d_ptr(new MaterialStylePrivate(this))
{
    d_func()->init();
}
