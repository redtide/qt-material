#include "dialog_internal.hpp"

#include <QtMaterialWidgets/dialog.hpp>

#include <QEvent>
#include <QPainter>
#include <QPixmap>
#include <QtWidgets/QStackedLayout>

MaterialDialogProxy::MaterialDialogProxy(
        MaterialDialogWindow* source,
        QStackedLayout*       layout,
        MaterialDialog*       dialog,
        QWidget*              parent)
    : QWidget(parent)
    , source_(source)
    , layout_(layout)
    , dialog_(dialog)
    , opacity_(0)
    , mode_(Transparent)
{
}

MaterialDialogProxy::~MaterialDialogProxy()
{
}

void MaterialDialogProxy::setOpacity(qreal opacity)
{
    opacity_ = opacity;
    mode_    = SemiTransparent;
    update();
    dialog_->update();
}


void MaterialDialogProxy::makeOpaque()
{
    dialog_->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    layout_->setCurrentIndex(0);
    opacity_ = 1.0;
    mode_    = Opaque;
    update();
}

void MaterialDialogProxy::makeTransparent()
{
    opacity_ = 0.0;
    mode_    = Transparent;
    update();
}

QSize MaterialDialogProxy::sizeHint() const
{
    return source_->sizeHint();
}

bool MaterialDialogProxy::event(QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type)
        source_->setGeometry(geometry());

    return QWidget::event(event);
}

void MaterialDialogProxy::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    if (Transparent == mode_) {
        return;
    } else if (Opaque != mode_) {
        painter.setOpacity(opacity_);
    }
    QPixmap pm = source_->grab(source_->rect());
    painter.drawPixmap(0, 0, pm);
}

MaterialDialogWindow::MaterialDialogWindow(MaterialDialog *dialog,
                                           QWidget        *parent)
    : QWidget(parent)
    , dialog_(dialog)
{
}

MaterialDialogWindow::~MaterialDialogWindow()
{
}

void MaterialDialogWindow::setOffset(int offset)
{
    QMargins margins = dialog_->layout()->contentsMargins();
    margins.setBottom(offset);
    dialog_->layout()->setContentsMargins(margins);
}

int MaterialDialogWindow::offset() const
{
    return dialog_->layout()->contentsMargins().bottom();
}

void MaterialDialogWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawRect(rect());
}
