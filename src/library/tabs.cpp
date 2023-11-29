#include "tabs_internal.hpp"
#include "tabs_p.hpp"

#include <QtMaterialWidgets/style.hpp>
#include <QtMaterialWidgets/tabs.hpp>

#include <QtWidgets/QHBoxLayout>

/*!
 *  \MaterialTabsPrivate
 *  \internal
 */

MaterialTabsPrivate::MaterialTabsPrivate(MaterialTabs *q)
    : q_ptr(q)
{
}

MaterialTabsPrivate::~MaterialTabsPrivate()
{
}

void MaterialTabsPrivate::init()
{
    Q_Q(MaterialTabs);

    inkBar         = new MaterialTabsInkBar(q);
    tabLayout      = new QHBoxLayout;
    rippleStyle    = Material::CenteredRipple;
    currentIndex   = -1;
    showHalo       = true;
    useThemeColors = true;

    q->setLayout(tabLayout);
    q->setStyle(&MaterialStyle::instance());

    tabLayout->setSpacing(0);
    tabLayout->setMargin(0);
}

/*!
 *  \MaterialTabs
 */

MaterialTabs::MaterialTabs(QWidget *parent)
    : QWidget(parent),
      d_ptr(new MaterialTabsPrivate(this))
{
    d_func()->init();
}

MaterialTabs::~MaterialTabs()
{
}

void MaterialTabs::setUseThemeColors(bool value)
{
    Q_D(MaterialTabs);

    d->useThemeColors = value;
}

bool MaterialTabs::useThemeColors() const
{
    Q_D(const MaterialTabs);

    return d->useThemeColors;
}

void MaterialTabs::setHaloVisible(bool value)
{
    Q_D(MaterialTabs);

    d->showHalo = value;
    updateTabs();
}

bool MaterialTabs::isHaloVisible() const
{
    Q_D(const MaterialTabs);

    return d->showHalo;
}

void MaterialTabs::setRippleStyle(Material::RippleStyle style)
{
    Q_D(MaterialTabs);

    d->rippleStyle = style;
    updateTabs();
}

Material::RippleStyle MaterialTabs::rippleStyle() const
{
    Q_D(const MaterialTabs);

    return d->rippleStyle;
}

void MaterialTabs::setInkColor(const QColor &color)
{
    Q_D(MaterialTabs);

    d->inkColor = color;
    d->useThemeColors = false;
    d->inkBar->update();

    update();
}

QColor MaterialTabs::inkColor() const
{
    Q_D(const MaterialTabs);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return MaterialStyle::instance().themeColor("accent1");
    } else {
        return d->inkColor;
    }
}

void MaterialTabs::setBackgroundColor(const QColor &color)
{
    Q_D(MaterialTabs);

    d->backgroundColor = color;
    d->useThemeColors = false;
    updateTabs();

    update();
}

QColor MaterialTabs::backgroundColor() const
{
    Q_D(const MaterialTabs);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return MaterialStyle::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

void MaterialTabs::setTextColor(const QColor &color)
{
    Q_D(MaterialTabs);

    d->textColor = color;
    d->useThemeColors = false;

    updateTabs();
    update();
}

QColor MaterialTabs::textColor() const
{
    Q_D(const MaterialTabs);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return MaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void MaterialTabs::addTab(const QString &text, const QIcon &icon)
{
    insertTab(count(), text, icon);
}

void MaterialTabs::insertTab(int index, const QString &text, const QIcon &icon)
{
    Q_D(MaterialTabs);

    MaterialTab* tab = new MaterialTab(this);
    tab->setText(text);
    tab->setHaloVisible(isHaloVisible());
    tab->setRippleStyle(rippleStyle());

    if (!icon.isNull()) {
        tab->setIcon(icon);
        tab->setIconSize(QSize(22, 22));
    }

    d->tabLayout->insertWidget(index, tab);

    if (-1 == d->currentIndex) {
        d->currentIndex = 0;
        d->inkBar->refreshGeometry();
        d->inkBar->raise();
        tab->setActive(true);
    };
}

void MaterialTabs::removeTab(int index)
{
    Q_D(MaterialTabs);

    if (index > -1) {
        MaterialTab* tab = static_cast<MaterialTab*>(d->tabLayout->itemAt(index)->widget());
        if (tab) {
            d->tabLayout->removeWidget(tab);
            delete tab;
        }
        setCurrentIndex(index - 1);
    }
}

void MaterialTabs::setTabText(int index, const QString& text)
{
    Q_D(MaterialTabs);

    if (index > -1) {
        MaterialTab* tab = static_cast<MaterialTab*>(d->tabLayout->itemAt(index)->widget());
        if (tab)
            tab->setText(text);
    }
}

void MaterialTabs::setCurrentTab(MaterialTab* tab)
{
    Q_D(MaterialTabs);

    setCurrentIndex(d->tabLayout->indexOf(tab));
}

void MaterialTabs::setCurrentIndex(int index)
{
    Q_D(MaterialTabs);

    setTabActive(d->currentIndex, false);
    d->currentIndex = index;
    setTabActive(index, true);
    d->inkBar->animate();

    Q_EMIT currentChanged(index);
}

int MaterialTabs::currentIndex() const
{
    Q_D(const MaterialTabs);

    return d->currentIndex;
}

QWidget* MaterialTabs::widget(int index) const
{
    Q_D(const MaterialTabs);

    QLayoutItem* item = d->tabLayout->itemAt(index);
    if (item)
        return item->widget();

    return nullptr;
}

int MaterialTabs::count() const
{
    Q_D(const MaterialTabs);
    return d->tabLayout->count();
}

void MaterialTabs::setTabActive(int index, bool active)
{
    Q_D(MaterialTabs);

    if (index > -1) {
        MaterialTab* tab = static_cast<MaterialTab*>(d->tabLayout->itemAt(index)->widget());
        if (tab)
            tab->setActive(active);
    }
}

void MaterialTabs::updateTabs()
{
    Q_D(MaterialTabs);

    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if (MaterialTab* tab = static_cast<MaterialTab *>(item->widget())) {
            tab->setRippleStyle(d->rippleStyle);
            tab->setHaloVisible(d->showHalo);
            tab->setBackgroundColor(backgroundColor());
            tab->setForegroundColor(textColor());
        }
    }
}
