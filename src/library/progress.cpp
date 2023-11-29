#include "progress_internal.hpp"
#include "progress_p.hpp"

#include <QtMaterialWidgets/progress.hpp>
#include <QtMaterialWidgets/style.hpp>

#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

/*!
 *  \class MaterialProgressPrivate
 *  \internal
 */

MaterialProgressPrivate::MaterialProgressPrivate(MaterialProgress *q)
    : q_ptr(q)
{
}

MaterialProgressPrivate::~MaterialProgressPrivate()
{
}

void MaterialProgressPrivate::init()
{
    Q_Q(MaterialProgress);

    delegate       = new MaterialProgressDelegate(q);
    progressType   = Material::IndeterminateProgress;
    useThemeColors = true;

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("offset");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1000);

    animation->setLoopCount(-1);

    animation->start();
}

/*!
 *  \class MaterialProgress
 */

MaterialProgress::MaterialProgress(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new MaterialProgressPrivate(this))
{
    d_func()->init();
}

MaterialProgress::~MaterialProgress()
{
}

void MaterialProgress::setProgressType(Material::ProgressType type)
{
    Q_D(MaterialProgress);

    d->progressType = type;
    update();
}

Material::ProgressType MaterialProgress::progressType() const
{
    Q_D(const MaterialProgress);

    return d->progressType;
}

void MaterialProgress::setUseThemeColors(bool state)
{
    Q_D(MaterialProgress);

    if (d->useThemeColors == state) {
        return;
    }

    d->useThemeColors = state;
    update();
}

bool MaterialProgress::useThemeColors() const
{
    Q_D(const MaterialProgress);

    return d->useThemeColors;
}

void MaterialProgress::setProgressColor(const QColor &color)
{
    Q_D(MaterialProgress);

    d->progressColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialProgress::progressColor() const
{
    Q_D(const MaterialProgress);

    if (d->useThemeColors || !d->progressColor.isValid()) {
        return MaterialStyle::instance().themeColor("primary1");
    } else {
        return d->progressColor;
    }
}

void MaterialProgress::setBackgroundColor(const QColor &color)
{
    Q_D(MaterialProgress);

    d->backgroundColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialProgress::backgroundColor() const
{
    Q_D(const MaterialProgress);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return MaterialStyle::instance().themeColor("border");
    } else {
        return d->backgroundColor;
    }
}

/*!
 *  \reimp
 */
void MaterialProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(MaterialProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled() ? backgroundColor()
                               : MaterialStyle::instance().themeColor("disabled"));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(0, height()/2-3, width(), 6, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(0, 0, width(), height());

    if (isEnabled())
    {
        brush.setColor(progressColor());
        painter.setBrush(brush);

        if (Material::IndeterminateProgress == d->progressType) {
            painter.drawRect(d->delegate->offset()*width()*2-width(), 0, width(), height());
        } else {
            qreal p = static_cast<qreal>(width())*(value()-minimum())/(maximum()-minimum());
            painter.drawRect(0, 0, p, height());
        }
    }
}
