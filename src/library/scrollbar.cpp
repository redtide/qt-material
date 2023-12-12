#include "scrollbar_internal.hpp"
#include "scrollbar_p.hpp"

#include <QtMaterialWidgets/scrollbar.hpp>
#include "palette-helper.hpp"

#include <QDebug>
#include <QPainter>
#include <QPainterPath>

MaterialScrollBarPrivate::MaterialScrollBarPrivate(MaterialScrollBar* q)
    : q_ptr(q)
{
}

MaterialScrollBarPrivate::~MaterialScrollBarPrivate()
{
}

void MaterialScrollBarPrivate::init()
{
    Q_Q(MaterialScrollBar);

    material::updatePalette(q);

    stateMachine   = new MaterialScrollBarStateMachine(q);
    hideOnMouseOut = true;
    useThemeColors = true;

    q->setMouseTracking(true);

    q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
                     "QScrollBar::add-line:vertical { height: 0; margin: 0; }"
                     "QScrollBar::sub-line:vertical { height: 0; margin: 0; }");

    stateMachine->start();
}

MaterialScrollBar::MaterialScrollBar(QWidget* parent)
    : QScrollBar(parent),
      d_ptr(new MaterialScrollBarPrivate(this))
{
    d_func()->init();
}

MaterialScrollBar::~MaterialScrollBar()
{
}

QSize MaterialScrollBar::sizeHint() const
{
    if (Qt::Horizontal == orientation()) {
        return QSize(1, 10);
    } else {
        return QSize(10, 1);
    }
}

void MaterialScrollBar::setHideOnMouseOut(bool value)
{
    Q_D(MaterialScrollBar);

    d->hideOnMouseOut = value;
    update();
}

bool MaterialScrollBar::hideOnMouseOut() const
{
    Q_D(const MaterialScrollBar);

    return d->hideOnMouseOut;
}

bool MaterialScrollBar::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return QScrollBar::event(event);
}

void MaterialScrollBar::paintEvent(QPaintEvent*)
{
    Q_D(MaterialScrollBar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), palette().color(QPalette::Window));

    int x, y, w, h;
    rect().getRect(&x, &y, &w, &h);

    QMargins margins(2, 2, 2, 2);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(palette().color(QPalette::Button));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (d->hideOnMouseOut)
        painter.setOpacity(d->stateMachine->opacity());

    QRect trimmed(rect().marginsRemoved(margins));

    QPainterPath path;
    path.addRoundedRect(trimmed, 3, 3);
    painter.setClipPath(path);
    painter.drawRect(trimmed);

    const qreal q = (Qt::Horizontal == orientation() ? w : h) /
            static_cast<qreal>(maximum() - minimum() + pageStep() - 1);

    QRect handle = Qt::Horizontal == orientation()
            ? QRect(sliderPosition() * q, y, pageStep() * q, h)
            : QRect(x, sliderPosition() * q, w, pageStep() * q);

    brush.setColor(palette().color(QPalette::Button));
    painter.setBrush(brush);

    painter.drawRoundedRect(handle, 9, 9);
}
