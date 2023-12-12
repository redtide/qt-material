#include "checkable_internal.hpp"
#include "defaults.hpp"

#include <QtMaterialWidgets/checkable.hpp>

#include <QIcon>
#include <QPainter>
#include <QTransform>

namespace md = material::defaults::checkable;

MaterialCheckableIcon::MaterialCheckableIcon(const QIcon& icon, MaterialCheckable* parent)
    : QWidget(parent)
    , checkable_(parent)
    , icon_(icon)
    , iconSize_(md::iconSize)
    , opacity_(md::opacity)
{
    Q_ASSERT(parent);

    setAttribute(Qt::WA_TransparentForMouseEvents);
}

MaterialCheckableIcon::~MaterialCheckableIcon()
{
}

QSize MaterialCheckableIcon::sizeHint() const
{
    return QSize(iconSize_, iconSize_);
}

void MaterialCheckableIcon::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(opacity_);

    QPixmap pixmap = icon().pixmap(md::iconSize, md::iconSize);

    if (!pixmap.isNull())
    {
        const qreal p = static_cast<qreal>((height()) - iconSize_) / 2;
        const qreal z = iconSize_ / md::iconSize;

        QTransform t;
        if (checkable_->labelPosition() == MaterialCheckable::LabelPositionLeft) {
            t.translate(p + width() - 42, p);
        } else {
            t.translate(p, p);
        }
        t.scale(z, z);
        painter.setTransform(t);

        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), palette().color(QPalette::Button));
        painter.drawPixmap(0, 0, pixmap);
    }
}
