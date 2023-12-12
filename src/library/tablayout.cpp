#include <QtMaterialWidgets/tablayout.hpp>
#include <QtMaterialWidgets/tabs.hpp>

#include <QStackedWidget>
#include <QVBoxLayout>

MaterialTabLayout::MaterialTabLayout(QWidget* parent)
    : QWidget(parent)
    , tabs(new MaterialTabs)
    , stack(new QStackedWidget)
{
    tabs->setObjectName(QStringLiteral("__qt__passive_tabs"));
    tabs->setHaloVisible(false);

    connect(tabs, QOverload<int>::of(&MaterialTabs::currentChanged),
            this, &MaterialTabLayout::setCurrentIndex);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tabs);
    layout->addWidget(stack);
}

QSize MaterialTabLayout::sizeHint() const
{
    return QSize(128, 128);
}

void MaterialTabLayout::setHaloVisible(bool value)
{
    tabs->setHaloVisible(value);
}

bool MaterialTabLayout::isHaloVisible() const
{
    return tabs->isHaloVisible();
}

void MaterialTabLayout::setRippleStyle(Material::RippleStyle style)
{
    tabs->setRippleStyle(style);
}

Material::RippleStyle MaterialTabLayout::rippleStyle() const
{
    return tabs->rippleStyle();
}

void MaterialTabLayout::addTab(QWidget* page)
{
    insertTab(stack->count(), page);
}

void MaterialTabLayout::removeTab(int index)
{
    QWidget* widget = stack->widget(index);
    if (!widget)
        return;

    stack->removeWidget(widget);
    tabs->removeTab(index);
}

int MaterialTabLayout::count() const
{
    return stack->count();
}

void MaterialTabLayout::insertTab(int index, QWidget* page)
{
    if (!page)
        return;

    page->setParent(stack);
    stack->insertWidget(index, page);

    QString title = page->windowTitle();
    if (title.isEmpty()) {
        title = tr("Tab %1").arg(tabs->count() + 1);
        page->setWindowTitle(title);
    }
    connect(page, &QWidget::windowTitleChanged,
            this, &MaterialTabLayout::tabWindowTitleChanged);

    tabs->insertTab(index, title);
}

void MaterialTabLayout::setTabTitle(QString const& text)
{
    QWidget* currentWidget = stack->currentWidget();
    if (currentWidget->windowTitle() == text)
        return;

    currentWidget->setWindowTitle(text);
    Q_EMIT tabTitleChanged(text);
}

QString MaterialTabLayout::tabTitle() const
{
    if (const QWidget* widget = stack->currentWidget())
        return widget->windowTitle();

    return QString();
}

void MaterialTabLayout::setCurrentIndex(int index)
{
    if (index >= 0 && index < stack->count() && index != stack->currentIndex()) {
        stack->setCurrentIndex(index);
        tabs->setCurrentIndex(index);
    }
    Q_EMIT currentIndexChanged(index);
}

int MaterialTabLayout::currentIndex() const
{
    return stack->currentIndex();
}

QWidget* MaterialTabLayout::widget(int index)
{
    return stack->widget(index);
}

void MaterialTabLayout::tabWindowTitleChanged()
{
    QWidget*  page  = qobject_cast<QWidget*>(sender());
    const int index = stack->indexOf(page);

    tabs->setTabText(index, page->windowTitle());
}
