#include "snackbar_internal.hpp"
#include "snackbar_p.hpp"
#include "statetransition.hpp"

#include <QtMaterialWidgets/snackbar.hpp>
#include <QtMaterialWidgets/style.hpp>

#include <QDebug>
#include <QPainter>
#include <QtWidgets/QApplication>

/*!
 *  \class MaterialSnackbarPrivate
 *  \internal
 */

MaterialSnackbarPrivate::MaterialSnackbarPrivate(MaterialSnackbar *q)
    : q_ptr(q)
{
}

MaterialSnackbarPrivate::~MaterialSnackbarPrivate()
{
}

void MaterialSnackbarPrivate::init()
{
    Q_Q(MaterialSnackbar);

    stateMachine   = new MaterialSnackbarStateMachine(q);
    bgOpacity      = 0.9;
    duration       = 3000;
    boxWidth       = 300;
    clickDismiss   = false;
    useThemeColors = true;

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QFont font("Roboto", 10, QFont::Medium);
    font.setCapitalization(QFont::AllUppercase);
    q->setFont(font);

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class MaterialSnackbar
 */

MaterialSnackbar::MaterialSnackbar(QWidget *parent)
    : MaterialOverlayWidget(parent),
      d_ptr(new MaterialSnackbarPrivate(this))
{
    d_func()->init();
}

MaterialSnackbar::~MaterialSnackbar()
{
}

void MaterialSnackbar::setAutoHideDuration(int duration)
{
    Q_D(MaterialSnackbar);

    d->duration = duration;
}

int MaterialSnackbar::autoHideDuration() const
{
    Q_D(const MaterialSnackbar);

    return d->duration;
}

void MaterialSnackbar::setUseThemeColors(bool value)
{
    Q_D(MaterialSnackbar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool MaterialSnackbar::useThemeColors() const
{
    Q_D(const MaterialSnackbar);

    return d->useThemeColors;
}

void MaterialSnackbar::setBackgroundColor(const QColor &color)
{
    Q_D(MaterialSnackbar);

    d->backgroundColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialSnackbar::backgroundColor() const
{
    Q_D(const MaterialSnackbar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return MaterialStyle::instance().themeColor("text");
    } else {
        return d->backgroundColor;
    }
}

void MaterialSnackbar::setBackgroundOpacity(qreal opacity)
{
    Q_D(MaterialSnackbar);

    d->bgOpacity = opacity;
    update();
}

qreal MaterialSnackbar::backgroundOpacity() const
{
    Q_D(const MaterialSnackbar);

    return d->bgOpacity;
}

void MaterialSnackbar::setTextColor(const QColor &color)
{
    Q_D(MaterialSnackbar);

    d->textColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialSnackbar::textColor() const
{
    Q_D(const MaterialSnackbar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return MaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void MaterialSnackbar::setFontSize(qreal size)
{
    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal MaterialSnackbar::fontSize() const
{
    return font().pointSizeF();
}

void MaterialSnackbar::setBoxWidth(int width)
{
    Q_D(MaterialSnackbar);

    d->boxWidth = width;
    update();
}

int MaterialSnackbar::boxWidth() const
{
    Q_D(const MaterialSnackbar);

    return d->boxWidth;
}

void MaterialSnackbar::setClickToDismissMode(bool value)
{
    Q_D(MaterialSnackbar);

    d->clickDismiss = value;
}

bool MaterialSnackbar::clickToDismissMode() const
{
    Q_D(const MaterialSnackbar);

    return d->clickDismiss;
}

void MaterialSnackbar::addMessage(const QString &message)
{
    Q_D(MaterialSnackbar);

    d->messages.push_back(message);
    d->stateMachine->postEvent(new MaterialStateTransitionEvent(SnackbarShowTransition));
    raise();
}

void MaterialSnackbar::addInstantMessage(const QString &message)
{
    Q_D(MaterialSnackbar);

    if (d->messages.isEmpty()) {
        d->messages.push_back(message);
    } else {
        d->messages.insert(1, message);
    }

    d->stateMachine->progress();
}

void MaterialSnackbar::dequeue()
{
    Q_D(MaterialSnackbar);

    if (d->messages.isEmpty()) {
        return;
    }

    d->messages.removeFirst();

    if (!d->messages.isEmpty()) {
        d->stateMachine->postEvent(new MaterialStateTransitionEvent(SnackbarNextTransition));
    } else {
        d->stateMachine->postEvent(new MaterialStateTransitionEvent(SnackbarWaitTransition));
    }
}

void MaterialSnackbar::paintEvent(QPaintEvent*)
{
    Q_D(MaterialSnackbar);

    if (d->messages.isEmpty()) {
        return;
    }

    QString message = d->messages.first();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setBrush(brush);
    painter.setOpacity(d->bgOpacity);

    QRect r(0, 0, d->boxWidth, 40);

    painter.setPen(Qt::white);
    QRect br = painter.boundingRect(r, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);

    painter.setPen(Qt::NoPen);
    r = br.united(r).adjusted(-10, -10, 10, 20);

    const qreal s = 1-d->stateMachine->offset();

    painter.translate((width()-(r.width()-20))/2,
                      height()+10-s*(r.height()));

    br.moveCenter(r.center());
    painter.drawRoundedRect(r.adjusted(0, 0, 0, 3), 3, 3);
    painter.setPen(textColor());
    painter.drawText(br, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);
}
