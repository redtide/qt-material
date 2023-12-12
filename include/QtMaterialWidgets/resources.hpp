#pragma once

#include <QtGlobal>
#include <QIcon>

static inline void initResource()
{
    Q_INIT_RESOURCE(qtmaterialwidgets);
}
namespace material {
namespace resources {
static inline void init()
{
    initResource();
}
static QIcon icon(const QString& categoryName, const QString& iconName)
{
    return QIcon(":/icons/" + categoryName + "/svg/production/ic_" + iconName + "_24px.svg");
}
} // namespace resource
} // namespace material
