#include <QtMaterialWidgets/overlaywidget.hpp>

#include <QEvent>

/*!
 *  \class MaterialOverlayWidget
 *  \internal
 */

MaterialOverlayWidget::MaterialOverlayWidget(QWidget *parent)
    : QWidget(parent)
{
    if (parent) {
        parent->installEventFilter(this);
    }
}

MaterialOverlayWidget::~MaterialOverlayWidget()
{
}

/*!
 *  \reimp
 */
bool MaterialOverlayWidget::event(QEvent *event)
{
    if (!parent()) {
        return QWidget::event(event);
    }
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        parent()->installEventFilter(this);
        setGeometry(overlayGeometry());
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

/*!
 *  \reimp
 */
bool MaterialOverlayWidget::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        setGeometry(overlayGeometry());
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

QRect MaterialOverlayWidget::overlayGeometry() const
{
    QWidget *widget = parentWidget();
    if (!widget) {
        return QRect();
    }
    return widget->rect();
}
