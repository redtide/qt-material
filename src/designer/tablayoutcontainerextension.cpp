#include "tablayoutcontainerextension.hpp"
#include <QtMaterialWidgets/tablayout.hpp>

QMWTabLayoutContainerExtension::QMWTabLayoutContainerExtension(MaterialTabLayout* widget, QObject* parent)
    : QObject(parent)
    , tablayout_(widget)
{
}
void QMWTabLayoutContainerExtension::addWidget(QWidget* widget)
{
    tablayout_->addTab(widget);
}
int QMWTabLayoutContainerExtension::count() const
{
    return tablayout_->count();
}
int QMWTabLayoutContainerExtension::currentIndex() const
{
    return tablayout_->currentIndex();
}
void QMWTabLayoutContainerExtension::insertWidget(int index, QWidget* widget)
{
    tablayout_->insertTab(index, widget);
}
void QMWTabLayoutContainerExtension::remove(int index)
{
    tablayout_->removeTab(index);
}
void QMWTabLayoutContainerExtension::setCurrentIndex(int index)
{
    tablayout_->setCurrentIndex(index);
}
QWidget* QMWTabLayoutContainerExtension::widget(int index) const
{
    return tablayout_->widget(index);
}
#if QT_VERSION >= 0x060000
bool QMWTabLayoutContainerExtension::canAddWidget() const
{
    return true;
}
bool QMWTabLayoutContainerExtension::canRemove(int) const
{
    return true;
}
#endif
