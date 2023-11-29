#include "scrollbar_internal.hpp"
#include "scrollbar_p.hpp"

#include <QtMaterialWidgets/scrollbar.hpp>
#include <QtMaterialWidgets/style.hpp>

#include <QDebug>
#include <QPainter>
#include <QPainterPath>

/*!
 *  \class MaterialScrollBarPrivate
 *  \internal
 */

MaterialScrollBarPrivate::MaterialScrollBarPrivate(MaterialScrollBar *q)
    : q_ptr(q)
{
}

MaterialScrollBarPrivate::~MaterialScrollBarPrivate()
{
}

void MaterialScrollBarPrivate::init()
{
    Q_Q(MaterialScrollBar);

    stateMachine   = new MaterialScrollBarStateMachine(q);
    hideOnMouseOut = true;
    useThemeColors = true;

    q->setMouseTracking(true);
    q->setStyle(&MaterialStyle::instance());
    q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
                     "QScrollBar::add-line:vertical { height: 0; margin: 0; }"
                     "QScrollBar::sub-line:vertical { height: 0; margin: 0; }");

    stateMachine->start();
}

/*!
 *  \class MaterialScrollBar
 */

MaterialScrollBar::MaterialScrollBar(QWidget *parent)
    : QScrollBar(parent),
      d_ptr(new MaterialScrollBarPrivate(this))
{
    d_func()->init();
}

MaterialScrollBar::~MaterialScrollBar()
{
}

/*!
 *  \reimp
 */
QSize MaterialScrollBar::sizeHint() const
{
    if (Qt::Horizontal == orientation()) {
        return QSize(1, 10);
    } else {
        return QSize(10, 1);
    }
}

void MaterialScrollBar::setUseThemeColors(bool value)
{
    Q_D(MaterialScrollBar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool MaterialScrollBar::useThemeColors() const
{
    Q_D(const MaterialScrollBar);

    return d->useThemeColors;
}

void MaterialScrollBar::setCanvasColor(const QColor &color)
{
    Q_D(MaterialScrollBar);

    d->canvasColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialScrollBar::canvasColor() const
{
    Q_D(const MaterialScrollBar);

    if (d->useThemeColors || !d->canvasColor.isValid()) {
        return parentWidget()->palette().color(backgroundRole());
    } else {
        return d->canvasColor;
    }
}

void MaterialScrollBar::setBackgroundColor(const QColor &color)
{
    Q_D(MaterialScrollBar);

    d->backgroundColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialScrollBar::backgroundColor() const
{
    Q_D(const MaterialScrollBar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return MaterialStyle::instance().themeColor("border");
    } else {
        return d->backgroundColor;
    }
}

void MaterialScrollBar::setSliderColor(const QColor &color)
{
    Q_D(MaterialScrollBar);

    d->sliderColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialScrollBar::sliderColor() const
{
    Q_D(const MaterialScrollBar);

    if (d->useThemeColors || !d->sliderColor.isValid()) {
        return MaterialStyle::instance().themeColor("primary1");
    } else {
        return d->sliderColor;
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

/*!
 *  \reimp
 */
void MaterialScrollBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(MaterialScrollBar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), canvasColor());

    int x, y, w, h;
    rect().getRect(&x, &y, &w, &h);

    QMargins margins(2, 2, 2, 2);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (d->hideOnMouseOut) {
        painter.setOpacity(d->stateMachine->opacity());
    }

    QRect trimmed(rect().marginsRemoved(margins));

    QPainterPath path;
    path.addRoundedRect(trimmed, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(trimmed);

    const qreal q = (Qt::Horizontal == orientation() ? w : h) /
            static_cast<qreal>(maximum()-minimum()+pageStep()-1);

    QRect handle = Qt::Horizontal == orientation()
            ? QRect(sliderPosition()*q, y, pageStep()*q, h)
            : QRect(x, sliderPosition()*q, w, pageStep()*q);

    brush.setColor(sliderColor());
    painter.setBrush(brush);

    painter.drawRoundedRect(handle, 9, 9);
}
