#include "drawer_internal.hpp"
#include "drawer_p.hpp"
#include "palette-helper.hpp"

#include <QtMaterialWidgets/drawer.hpp>

#include <QDebug>
#include <QEvent>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QPainter>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>

MaterialDrawerPrivate::MaterialDrawerPrivate(MaterialDrawer* q)
    : q_ptr(q)
{
}

MaterialDrawerPrivate::~MaterialDrawerPrivate()
{
}

void MaterialDrawerPrivate::init()
{
    Q_Q(MaterialDrawer);

    material::updatePalette(q);

    widget       = new MaterialDrawerWidget;
    stateMachine = new MaterialDrawerStateMachine(widget, q);
    window       = new QWidget;
    width        = 250;
    clickToClose = false;
    autoRaise    = true;
    closed       = true;
    overlay      = false;

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(window);

    widget->setLayout(layout);
    widget->setFixedWidth(width+16);

    widget->setParent(q);

    stateMachine->start();
    QCoreApplication::processEvents();
}

MaterialDrawer::MaterialDrawer(QWidget* parent)
    : MaterialOverlayWidget(parent)
    , d_ptr(new MaterialDrawerPrivate(this))
{
    d_func()->init();
}

MaterialDrawer::~MaterialDrawer()
{
}

void MaterialDrawer::setDrawerWidth(int width)
{
    Q_D(MaterialDrawer);

    d->width = width;
    d->stateMachine->updatePropertyAssignments();
    d->widget->setFixedWidth(width+16);
}

int MaterialDrawer::drawerWidth() const
{
    Q_D(const MaterialDrawer);

    return d->width;
}

void MaterialDrawer::setDrawerLayout(QLayout* layout)
{
    Q_D(MaterialDrawer);

    d->window->setLayout(layout);
}

QLayout* MaterialDrawer::drawerLayout() const
{
    Q_D(const MaterialDrawer);

    return d->window->layout();
}

void MaterialDrawer::setClickOutsideToClose(bool state)
{
    Q_D(MaterialDrawer);

    d->clickToClose = state;
}

bool MaterialDrawer::clickOutsideToClose() const
{
    Q_D(const MaterialDrawer);

    return d->clickToClose;
}

void MaterialDrawer::setAutoRaise(bool state)
{
    Q_D(MaterialDrawer);

    d->autoRaise = state;
}

bool MaterialDrawer::autoRaise() const
{
    Q_D(const MaterialDrawer);

    return d->autoRaise;
}

void MaterialDrawer::setOverlayMode(bool value)
{
    Q_D(MaterialDrawer);

    d->overlay = value;
    update();
}

bool MaterialDrawer::overlayMode() const
{
    Q_D(const MaterialDrawer);

    return d->overlay;
}

void MaterialDrawer::openDrawer()
{
    Q_D(MaterialDrawer);

    Q_EMIT d->stateMachine->signalOpen();

    if (d->autoRaise) {
        raise();
    }
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_NoSystemBackground, false);
}

void MaterialDrawer::closeDrawer()
{
    Q_D(MaterialDrawer);

    Q_EMIT d->stateMachine->signalClose();

    if (d->overlay) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
    }
}

bool MaterialDrawer::event(QEvent* event)
{
    Q_D(MaterialDrawer);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        if (!d->overlay)
            setMask(QRegion(d->widget->rect()));
        break;
    default:
        break;
    }
    return MaterialOverlayWidget::event(event);
}

bool MaterialDrawer::eventFilter(QObject* obj, QEvent* event)
{
    Q_D(MaterialDrawer);

    switch (event->type())
    {
    case QEvent::MouseButtonPress: {
        QMouseEvent* mouseEvent;
        if ((mouseEvent = static_cast<QMouseEvent* >(event))) {
            const bool canClose = d->clickToClose || d->overlay;
            if (!d->widget->geometry().contains(mouseEvent->pos()) && canClose)
                closeDrawer();
        }
        break;
    }
    case QEvent::Move:
    case QEvent::Resize: {
        QLayout* lw = d->widget->layout();
        if (lw && 16 != lw->contentsMargins().right())
            lw->setContentsMargins(0, 0, 16, 0);
        break;
    }
    case QEvent::ThemeChange: {
        material::updatePalette(this);
        return true;
    }
    default:
        break;
    }
    return MaterialOverlayWidget::eventFilter(obj, event);
}

void MaterialDrawer::paintEvent(QPaintEvent*)
{
    Q_D(MaterialDrawer);

    if (!d->overlay || d->stateMachine->isInClosedState())
        return;

    QPainter painter(this);
    painter.setOpacity(d->stateMachine->opacity());
    painter.fillRect(rect(), Qt::SolidPattern);
}
