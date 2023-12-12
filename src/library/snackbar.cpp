#include "snackbar_internal.hpp"
#include "snackbar_p.hpp"
#include "statetransition.hpp"
#include "defaults.hpp"

#include <QtMaterialWidgets/snackbar.hpp>
#include "palette-helper.hpp"

#include <QDebug>
#include <QPainter>
#include <QtWidgets/QApplication>

MaterialSnackbarPrivate::MaterialSnackbarPrivate(MaterialSnackbar* q)
    : q_ptr(q)
{
}

MaterialSnackbarPrivate::~MaterialSnackbarPrivate()
{
}

void MaterialSnackbarPrivate::init()
{
    Q_Q(MaterialSnackbar);

    material::updatePalette(q);

    stateMachine     = new MaterialSnackbarStateMachine(q);
    bgOpacity        = 0.9;
    autoHideDuration = material::defaults::snackbar::autoHideDuration;
    boxWidth         = 300;
    clickDismiss     = false;

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QFont font(material::defaults::global::font::family);
    font.setPointSizeF(material::defaults::global::font::pointSizeF);
    font.setWeight(material::defaults::global::font::weight);
    font.setCapitalization(material::defaults::global::font::capitalization);
    q->setFont(font);

    stateMachine->start();
    QCoreApplication::processEvents();
}

MaterialSnackbar::MaterialSnackbar(QWidget* parent)
    : MaterialOverlayWidget(parent)
    , d_ptr(new MaterialSnackbarPrivate(this))
{
    d_func()->init();
}

MaterialSnackbar::~MaterialSnackbar()
{
}

void MaterialSnackbar::setAutoHideDuration(int duration)
{
    Q_D(MaterialSnackbar);

    d->autoHideDuration = duration;
}

int MaterialSnackbar::autoHideDuration() const
{
    Q_D(const MaterialSnackbar);

    return d->autoHideDuration;
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

void MaterialSnackbar::addMessage(const QString& message)
{
    Q_D(MaterialSnackbar);

    d->messages.push_back(message);
    d->stateMachine->postEvent(new MaterialStateTransitionEvent(SnackbarShowTransition));
    raise();
}

void MaterialSnackbar::addInstantMessage(const QString &message)
{
    Q_D(MaterialSnackbar);

    if (d->messages.isEmpty())
        d->messages.push_back(message);

    d->messages.insert(1, message);

    d->stateMachine->progress();
}

void MaterialSnackbar::dequeue()
{
    Q_D(MaterialSnackbar);

    if (d->messages.isEmpty())
        return;

    d->messages.removeFirst();

    if (!d->messages.isEmpty())
        d->stateMachine->postEvent(new MaterialStateTransitionEvent(SnackbarNextTransition));

    d->stateMachine->postEvent(new MaterialStateTransitionEvent(SnackbarWaitTransition));
}

bool MaterialSnackbar::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return MaterialOverlayWidget::event(event);
}

void MaterialSnackbar::paintEvent(QPaintEvent*)
{
    Q_D(MaterialSnackbar);

    if (d->messages.isEmpty())
        return;

    QString message = d->messages.first();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(palette().color(QPalette::Button));
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
    painter.setPen(palette().color(QPalette::ButtonText));
    painter.drawText(br, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);
}
