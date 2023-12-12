#include "dialog_internal.hpp"
#include "dialog_p.hpp"
#include "statetransition.hpp"
#include "defaults.hpp"
#include "palette-helper.hpp"

#include <QtMaterialWidgets/dialog.hpp>

#include <QPainter>
#include <QPropertyAnimation>
#include <QState>
#include <QStateMachine>

#include <QtWidgets/QApplication>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QGraphicsDropShadowEffect>

MaterialDialogPrivate::MaterialDialogPrivate(MaterialDialog* q)
    : q_ptr(q)
{
}

MaterialDialogPrivate::~MaterialDialogPrivate()
{
}

void MaterialDialogPrivate::init()
{
    Q_Q(MaterialDialog);

    material::updatePalette(q);

    dialogWindow = new MaterialDialogWindow(q);
    proxyStack   = new QStackedLayout;
    stateMachine = new QStateMachine(q);
    proxy        = new MaterialDialogProxy(dialogWindow, proxyStack, q);

    QVBoxLayout* layout = new QVBoxLayout;
    q->setLayout(layout);

    QWidget* widget = new QWidget;
    widget->setLayout(proxyStack);
    widget->setMinimumWidth(material::defaults::dialog::minimumWidth);

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setColor(material::defaults::dialog::effect::color);
    effect->setBlurRadius(material::defaults::dialog::effect::blurRadius);
    effect->setOffset(material::defaults::dialog::effect::offset);
    widget->setGraphicsEffect(effect);

    layout->addWidget(widget);
    layout->setAlignment(widget, Qt::AlignCenter);

    proxyStack->addWidget(dialogWindow);
    proxyStack->addWidget(proxy);
    proxyStack->setCurrentIndex(1);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QState* hiddenState = new QState;
    QState* visibleState = new QState;

    stateMachine->addState(hiddenState);
    stateMachine->addState(visibleState);
    stateMachine->setInitialState(hiddenState);

    MaterialStateTransition* transition;

    transition = new MaterialStateTransition(DialogShowTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new MaterialStateTransition(DialogHideTransition);
    transition->setTargetState(hiddenState);
    visibleState->addTransition(transition);

    visibleState->assignProperty(proxy, "opacity", 1);
    visibleState->assignProperty(effect, "color", QColor(0, 0, 0, 200));
    visibleState->assignProperty(dialogWindow, "offset", 0);
    hiddenState->assignProperty(proxy, "opacity", 0);
    hiddenState->assignProperty(effect, "color", QColor(0, 0, 0, 0));
    hiddenState->assignProperty(dialogWindow, "offset", 200);

    QPropertyAnimation* animation;

    animation = new QPropertyAnimation(proxy, "opacity", q);
    animation->setDuration(280);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "color", q);
    animation->setDuration(280);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(dialogWindow, "offset", q);
    animation->setDuration(280);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    stateMachine->addDefaultAnimation(animation);

    QObject::connect(visibleState, SIGNAL(propertiesAssigned()),
                     proxy, SLOT(makeOpaque()));
    QObject::connect(hiddenState, SIGNAL(propertiesAssigned()),
                     proxy, SLOT(makeTransparent()));

    stateMachine->start();
    QCoreApplication::processEvents();
}

MaterialDialog::MaterialDialog(QWidget* parent)
    : MaterialOverlayWidget(parent)
    , d_ptr(new MaterialDialogPrivate(this))
{
    d_func()->init();
}

MaterialDialog::~MaterialDialog()
{
}

QLayout* MaterialDialog::windowLayout() const
{
    Q_D(const MaterialDialog);

    return d->dialogWindow->layout();
}

void MaterialDialog::setWindowLayout(QLayout* layout)
{
    Q_D(MaterialDialog);

    d->dialogWindow->setLayout(layout);
}

void MaterialDialog::showDialog()
{
    Q_D(MaterialDialog);

    d->stateMachine->postEvent(new MaterialStateTransitionEvent(DialogShowTransition));
    raise();
}

void MaterialDialog::hideDialog()
{
    Q_D(MaterialDialog);

    d->stateMachine->postEvent(new MaterialStateTransitionEvent(DialogHideTransition));
    setAttribute(Qt::WA_TransparentForMouseEvents);
    d->proxyStack->setCurrentIndex(1);
}

bool MaterialDialog::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return MaterialOverlayWidget::event(event);
}

void MaterialDialog::paintEvent(QPaintEvent*)
{
    Q_D(MaterialDialog);

    QPainter painter(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.setOpacity(d->proxy->opacity()/2.4);
    painter.drawRect(rect());
}
