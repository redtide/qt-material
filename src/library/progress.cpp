#include "progress_internal.hpp"
#include "progress_p.hpp"

#include <QtMaterialWidgets/progress.hpp>
#include "palette-helper.hpp"

#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

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

    material::updatePalette(q);

    delegate     = new MaterialProgressDelegate(q);
    progressType = Material::IndeterminateProgress;

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

MaterialProgress::MaterialProgress(QWidget *parent)
    : QProgressBar(parent)
    , d_ptr(new MaterialProgressPrivate(this))
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

bool MaterialProgress::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return QProgressBar::event(event);
}

void MaterialProgress::paintEvent(QPaintEvent*)
{
    Q_D(MaterialProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled()
        ? palette().color(QPalette::Window)
        : palette().color(QPalette::Disabled, QPalette::Window));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(0, height()/2-3, width(), 6, 3, 3);
    painter.setClipPath(path);
    painter.drawRect(0, 0, width(), height());

    if (isEnabled())
    {
        brush.setColor(palette().color(QPalette::Button));
        painter.setBrush(brush);

        if (Material::IndeterminateProgress == d->progressType) {
            painter.drawRect(d->delegate->offset() * width() * 2 - width(), 0, width(), height());
        } else {
            qreal p = static_cast<qreal>(width()) * (value()-minimum()) / (maximum() - minimum());
            painter.drawRect(0, 0, p, height());
        }
    }
}
