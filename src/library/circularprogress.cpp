#include "circularprogress_internal.hpp"
#include "circularprogress_p.hpp"

#include <QtMaterialWidgets/circularprogress.hpp>
#include "palette-helper.hpp"

#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

MaterialCircularProgressPrivate::MaterialCircularProgressPrivate(MaterialCircularProgress* q)
    : q_ptr(q)
{
}

MaterialCircularProgressPrivate::~MaterialCircularProgressPrivate()
{
}

void MaterialCircularProgressPrivate::init()
{
    Q_Q(MaterialCircularProgress);

    material::updatePalette(q);

    delegate       = new MaterialCircularProgressDelegate(q);
    progressType   = Material::IndeterminateProgress;
    penWidth       = 6.25;
    size           = 48;

    q->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
                                 QSizePolicy::MinimumExpanding));

    QParallelAnimationGroup* group = new QParallelAnimationGroup(q);
    group->setLoopCount(-1);

    QPropertyAnimation* animation;

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashLength");
    animation->setTargetObject(delegate);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setStartValue(0.1);
    animation->setKeyValueAt(0.15, 0.2);
    animation->setKeyValueAt(0.6, 20);
    animation->setKeyValueAt(0.7, 20);
    animation->setEndValue(20);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashOffset");
    animation->setTargetObject(delegate);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setStartValue(0);
    animation->setKeyValueAt(0.15, 0);
    animation->setKeyValueAt(0.6, -7);
    animation->setKeyValueAt(0.7, -7);
    animation->setEndValue(-25);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("angle");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(719);
    animation->setDuration(2050);

    group->addAnimation(animation);

    group->start();
}

MaterialCircularProgress::MaterialCircularProgress(QWidget* parent)
    : QProgressBar(parent)
    , d_ptr(new MaterialCircularProgressPrivate(this))
{
    d_func()->init();
}

MaterialCircularProgress::~MaterialCircularProgress()
{
}

void MaterialCircularProgress::setProgressType(Material::ProgressType type)
{
    Q_D(MaterialCircularProgress);

    d->progressType = type;
    update();
}

Material::ProgressType MaterialCircularProgress::progressType() const
{
    Q_D(const MaterialCircularProgress);

    return d->progressType;
}

void MaterialCircularProgress::setLineWidth(qreal width)
{
    Q_D(MaterialCircularProgress);

    d->penWidth = width;
    update();
    updateGeometry();
}

qreal MaterialCircularProgress::lineWidth() const
{
    Q_D(const MaterialCircularProgress);

    return d->penWidth;
}

void MaterialCircularProgress::setSize(int size)
{
    Q_D(MaterialCircularProgress);

    d->size = size;
    update();
    updateGeometry();
}

int MaterialCircularProgress::size() const
{
    Q_D(const MaterialCircularProgress);

    return d->size;
}

QSize MaterialCircularProgress::sizeHint() const
{
    Q_D(const MaterialCircularProgress);

    const qreal s = d->size + d->penWidth + 8;
    return QSize(s, s);
}

bool MaterialCircularProgress::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return QProgressBar::event(event);
}

void MaterialCircularProgress::paintEvent(QPaintEvent*)
{
    Q_D(MaterialCircularProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!isEnabled())
    {
        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidthF(d->penWidth);
        pen.setColor(palette().color(QPalette::WindowText));
        painter.setPen(pen);
        painter.drawLine(rect().center() - QPointF(20, 20),  rect().center() + QPointF(20, 20));
        painter.drawLine(rect().center() + QPointF(20, -20), rect().center() - QPointF(20, -20));
        return;
    }

    if (Material::IndeterminateProgress == d->progressType)
    {
        painter.translate(width() / 2, height() / 2);
        painter.rotate(d->delegate->angle());
    }

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(d->penWidth);
    pen.setColor(palette().color(QPalette::Button));

    if (Material::IndeterminateProgress == d->progressType)
    {
        QVector<qreal> pattern;
        pattern << d->delegate->dashLength() * d->size / 50 << 30 * d->size / 50;

        pen.setDashOffset(d->delegate->dashOffset() * d->size / 50);
        pen.setDashPattern(pattern);

        painter.setPen(pen);

        painter.drawEllipse(QPoint(0, 0), d->size / 2, d->size / 2);
    }
    else
    {
        painter.setPen(pen);

        const qreal x = (width()-d->size)  / 2;
        const qreal y = (height()-d->size) / 2;
        const qreal a = 360 * (value()-minimum()) / (maximum()-minimum());

        QPainterPath path;
        path.arcMoveTo(x, y, d->size, d->size, 0);
        path.arcTo(x, y, d->size, d->size, 0, a);

        painter.drawPath(path);
    }
}
