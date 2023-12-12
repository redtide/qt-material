#include "appbar_p.hpp"

#include <QtMaterialWidgets/appbar.hpp>
#include "defaults.hpp"
#include "palette-helper.hpp"

#include <QEvent>
#include <QHBoxLayout>
#include <QPainter>
#include <QPixmapCache>
#include <QStyleOption>
#include <QtWidgets/QGraphicsDropShadowEffect>

MaterialAppBarPrivate::MaterialAppBarPrivate(MaterialAppBar* q)
    : q_ptr(q)
{
}

MaterialAppBarPrivate::~MaterialAppBarPrivate()
{
}

void MaterialAppBarPrivate::init()
{
    Q_Q(MaterialAppBar);

    material::updatePalette(q);

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(material::defaults::global::effect::blurRadius);
    effect->setColor(material::defaults::global::effect::color);
    effect->setOffset(material::defaults::global::effect::offset);
    q->setGraphicsEffect(effect);

    QHBoxLayout* layout = new QHBoxLayout;
    q->setLayout(layout);
}

MaterialAppBar::MaterialAppBar(QWidget* parent)
    : QWidget(parent)
    , d_ptr(new MaterialAppBarPrivate(this))
{
    d_func()->init();
}

MaterialAppBar::~MaterialAppBar()
{
}

QSize MaterialAppBar::sizeHint() const
{
    return material::defaults::appbar::sizeHint;
}

bool MaterialAppBar::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return QWidget::event(event);
}

void MaterialAppBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(rect(), palette().color(QPalette::Button));
}
