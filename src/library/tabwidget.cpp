#include <QtMaterialWidgets/tabwidget.hpp>
#include <QtMaterialWidgets/tabs.hpp>

#include <QStackedWidget>
#include <QVBoxLayout>

MaterialTabWidget::MaterialTabWidget(QWidget *parent)
    : QWidget(parent)
    , tabs(new MaterialTabs)
    , stack(new QStackedWidget)
{
    tabs->setObjectName(QStringLiteral("__qt__passive_tabbar"));
    tabs->setHaloVisible(false);

    connect(tabs, QOverload<int>::of(&MaterialTabs::currentChanged),
            this, &MaterialTabWidget::setCurrentIndex);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabs);
    layout->addWidget(stack);
}

void MaterialTabWidget::setHaloVisible(bool value)
{
    tabs->setHaloVisible(value);
}

bool MaterialTabWidget::isHaloVisible() const
{
    return tabs->isHaloVisible();
}

void MaterialTabWidget::setRippleStyle(Material::RippleStyle style)
{
    tabs->setRippleStyle(style);
}

Material::RippleStyle MaterialTabWidget::rippleStyle() const
{
    return tabs->rippleStyle();
}

void MaterialTabWidget::setInkColor(const QColor &color)
{
    tabs->setInkColor(color);
}

QColor MaterialTabWidget::inkColor() const
{
    return tabs->inkColor();
}

void MaterialTabWidget::setBackgroundColor(const QColor &color)
{
    tabs->setBackgroundColor(color);
}

QColor MaterialTabWidget::backgroundColor() const
{
    return tabs->backgroundColor();
}

void MaterialTabWidget::setTextColor(const QColor &color)
{
    tabs->setTextColor(color);
}

QColor MaterialTabWidget::textColor() const
{
    return tabs->textColor();
}

QSize MaterialTabWidget::sizeHint() const
{
    return QSize(300, 200);
}

void MaterialTabWidget::addTab(QWidget *page)
{
    insertTab(stack->count(), page);
}

void MaterialTabWidget::removeTab(int index)
{
    QWidget* widget = stack->widget(index);
    if (!widget)
        return;

    stack->removeWidget(widget);
    tabs->removeTab(index);
}

int MaterialTabWidget::count() const
{
    return stack->count();
}

void MaterialTabWidget::insertTab(int index, QWidget *page)
{
    page->setParent(stack);
    stack->insertWidget(index, page);

    QString title = page->windowTitle();
    if (title.isEmpty()) {
        title = tr("Tab %1").arg(tabs->count() + 1);
        page->setWindowTitle(title);
    }
    connect(page, &QWidget::windowTitleChanged,
            this, &MaterialTabWidget::tabWindowTitleChanged);
    tabs->insertTab(index, title);
}

void MaterialTabWidget::setTabTitle(QString const& text)
{
    QWidget* widget = stack->currentWidget();
    if (widget->windowTitle() == text)
        return;

    widget->setWindowTitle(text);
    Q_EMIT tabTitleChanged(text);
}

QString MaterialTabWidget::tabTitle() const
{
    if (const QWidget *currentWidget = stack->currentWidget())
        return currentWidget->windowTitle();
    return QString();
}

void MaterialTabWidget::setCurrentIndex(int index)
{
    if (index >= 0 && index < stack->count() && index != stack->currentIndex()) {
        stack->setCurrentIndex(index);
        tabs->setCurrentIndex(index);
    }
    Q_EMIT currentIndexChanged(index);
}

int MaterialTabWidget::currentIndex() const
{
    return stack->currentIndex();
}

QWidget* MaterialTabWidget::widget(int index)
{
    return stack->widget(index);
}

void MaterialTabWidget::tabWindowTitleChanged()
{
    QWidget *page = qobject_cast<QWidget *>(sender());
    const int index = stack->indexOf(page);
    tabs->setTabText(index, page->windowTitle());
}
