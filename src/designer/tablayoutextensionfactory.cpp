#include <QtMaterialWidgets/tablayout.hpp>

#include "tablayoutextensionfactory.hpp"
#include "tablayoutcontainerextension.hpp"

QMWTabLayoutExtensionFactory::QMWTabLayoutExtensionFactory(QExtensionManager* parent)
    : QExtensionFactory(parent)
{}

QObject* QMWTabLayoutExtensionFactory::createExtension(QObject*       object,
                                                       const QString& iid,
                                                       QObject*       parent) const
{
    MaterialTabLayout* widget = qobject_cast<MaterialTabLayout*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension)))
        return new QMWTabLayoutContainerExtension(widget, parent);

    return nullptr;
}
