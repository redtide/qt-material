#include "tabs_internal.hpp"

#include <QtMaterialWidgets/tabs.hpp>

#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLayoutItem>

MaterialTabsIndicatorBar::MaterialTabsIndicatorBar(MaterialTabs* parent)
    : MaterialOverlayWidget(parent)
    , tabs_(parent)
    , animation_(new QPropertyAnimation(parent))
    , tween_(0)
{
    Q_ASSERT(parent);

    animation_->setPropertyName("tweenValue");
    animation_->setEasingCurve(QEasingCurve::OutCirc);
    animation_->setTargetObject(this);
    animation_->setDuration(700);

    tabs_->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

MaterialTabsIndicatorBar::~MaterialTabsIndicatorBar()
{
}

void MaterialTabsIndicatorBar::refreshGeometry()
{
    QLayoutItem* item = tabs_->layout()->itemAt(tabs_->currentIndex());

    if (item)
    {
        const QRect r(item->geometry());
        const qreal s = 1 - tween_;

        if (QAbstractAnimation::Running != animation_->state()) {
            geometry_ = QRect(r.left(), r.bottom() - 1, r.width(), 4);
        } else {
            const qreal left  = previousGeometry_.left()  * s + r.left()  * tween_;
            const qreal width = previousGeometry_.width() * s + r.width() * tween_;
            geometry_ = QRect(left, r.bottom() - 1, width, 4);
        }
        tabs_->update();
    }
}

void MaterialTabsIndicatorBar::animate()
{
    raise();

    previousGeometry_ = geometry_;

    animation_->stop();
    animation_->setStartValue(0);
    animation_->setEndValue(1);
    animation_->start();
}

bool MaterialTabsIndicatorBar::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
    {
        refreshGeometry();
        break;
    }
    default:
        break;
    }
    return MaterialOverlayWidget::eventFilter(obj, event);
}

void MaterialTabsIndicatorBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setOpacity(1);
    painter.fillRect(geometry_, palette().color(QPalette::Button));
}

MaterialTab::MaterialTab(MaterialTabs* parent)
    : MaterialFlatButton(parent)
    , tabs_(parent)
    , active_(false)
{
    Q_ASSERT(parent);

    setMinimumHeight(50);

    QFont f(font());
    f.setStyleName("Normal");
    setFont(f);

    setCornerRadius(0);
    setRole(Material::Primary);
    setBackgroundMode(Qt::OpaqueMode);
    setBaseOpacity(0.25);

    connect(this, SIGNAL(clicked(bool)), this, SLOT(activateTab()));
}

MaterialTab::~MaterialTab()
{
}

QSize MaterialTab::sizeHint() const
{
    if (icon().isNull())
        return MaterialFlatButton::sizeHint();

    return QSize(40, iconSize().height() + 46);
}

void MaterialTab::activateTab()
{
    tabs_->setCurrentTab(this);
}

void MaterialTab::paintForeground(QPainter* painter)
{
    painter->setPen(palette().color(QPalette::ButtonText));

    if (!icon().isNull())
        painter->translate(0, 12);

    QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
    QSize base(size() - textSize);

    QRect textGeometry(QPoint(base.width(), base.height()) / 2, textSize);

    painter->drawText(textGeometry, Qt::AlignCenter, text());

    if (!icon().isNull())
    {
        const QSize &size = iconSize();
        QRect iconRect(QPoint((width()-size.width())/2, 0), size);

        QPixmap pixmap = icon().pixmap(iconSize());
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), painter->pen().color());
        painter->drawPixmap(iconRect, pixmap);
    }

    if (!active_)
    {
        if (!icon().isNull())
            painter->translate(0, -12);

        QBrush overlay;
        overlay.setStyle(Qt::SolidPattern);
        overlay.setColor(palette().color(QPalette::Button));
        painter->setOpacity(0.36);
        painter->fillRect(rect(), overlay);
    }
}
