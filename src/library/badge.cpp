#include "badge_p.hpp"

#include <QtMaterialWidgets/badge.hpp>
#include "palette-helper.hpp"

#include <QEvent>
#include <QPainter>

MaterialBadgePrivate::MaterialBadgePrivate(MaterialBadge* q)
    : q_ptr(q)
{
}

MaterialBadgePrivate::~MaterialBadgePrivate()
{
}

void MaterialBadgePrivate::init()
{
    Q_Q(MaterialBadge);

    namespace md = material;
    namespace dark = md::palette_system::dark;
    namespace light = md::palette_system::light;

    md::updatePalette(q);

    QPalette palette = q->palette();

    if (md::isDark()) {
        palette.setColor(QPalette::Button, md::fromRgba(light::error));
        palette.setColor(QPalette::ButtonText, md::fromRgba(light::on_error));
    } else {
        palette.setColor(QPalette::Button, md::fromRgba(light::error));
        palette.setColor(QPalette::ButtonText, md::fromRgba(light::on_error));
    }
    q->setPalette(palette);

    x       = 0;
    y       = 0;
    padding = 10;

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QFont font(q->font());
    font.setPointSizeF(10.f);
    font.setWeight(QFont::Bold);
    q->setFont(font);
    q->setText("1");
}

MaterialBadge::MaterialBadge(QWidget* parent)
    : MaterialOverlayWidget(parent)
    , d_ptr(new MaterialBadgePrivate(this))
{
    d_func()->init();
}

MaterialBadge::MaterialBadge(const QIcon& icon, QWidget* parent)
    : MaterialOverlayWidget(parent)
    , d_ptr(new MaterialBadgePrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

MaterialBadge::MaterialBadge(const QString& text, QWidget* parent)
    : MaterialOverlayWidget(parent)
    , d_ptr(new MaterialBadgePrivate(this))
{
    d_func()->init();

    setText(text);
}

MaterialBadge::~MaterialBadge()
{
}

void MaterialBadge::setRelativePosition(const QPointF &pos)
{
    setRelativePosition(pos.x(), pos.y());
}

void MaterialBadge::setRelativePosition(qreal x, qreal y)
{
    Q_D(MaterialBadge);

    d->x = x;
    d->y = y;
    update();
}

QPointF MaterialBadge::relativePosition() const
{
    Q_D(const MaterialBadge);

    return QPointF(d->x, d->y);
}

void MaterialBadge::setRelativeXPosition(qreal x)
{
    Q_D(MaterialBadge);

    d->x = x;
    update();
}

qreal MaterialBadge::relativeXPosition() const
{
    Q_D(const MaterialBadge);

    return d->x;
}

void MaterialBadge::setRelativeYPosition(qreal y)
{
    Q_D(MaterialBadge);

    d->y = y;
    update();
}

qreal MaterialBadge::relativeYPosition() const
{
    Q_D(const MaterialBadge);

    return d->y;
}

QSize MaterialBadge::sizeHint() const
{
    const int s = getDiameter();
    return QSize(s + 4, s + 4);
}

void MaterialBadge::setIcon(const QIcon &icon)
{
    Q_D(MaterialBadge);

    d->icon = icon;
    update();
}

QIcon MaterialBadge::icon() const
{
    Q_D(const MaterialBadge);

    return d->icon;
}

void MaterialBadge::setText(const QString &text)
{
    Q_D(MaterialBadge);

    d->text = text;

    if (!d->icon.isNull())
        d->icon = QIcon();

    d->size = fontMetrics().size(Qt::TextShowMnemonic, text);

    update();
}

QString MaterialBadge::text() const
{
    Q_D(const MaterialBadge);

    return d->text;
}

bool MaterialBadge::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return MaterialOverlayWidget::event(event);
}

void MaterialBadge::paintEvent(QPaintEvent*)
{
    Q_D(MaterialBadge);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(d->x, d->y);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled() ? palette().color(QPalette::Button)
                               : palette().color(QPalette::Disabled, QPalette::Button));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    const int s = getDiameter();

    QRectF r(0, 0, s, s);
    r.translate(QPointF((width()-s), (height()-s))/2);

    if (d->icon.isNull())
    {
        painter.drawEllipse(r);
        painter.setPen(palette().color(QPalette::ButtonText));
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r.translated(0, -0.5), Qt::AlignCenter, d->text);
    }
    else
    {
        painter.drawEllipse(r);
        QRectF q(0, 0, 16, 16);
        q.moveCenter(r.center());
        QPixmap pixmap = icon().pixmap(16, 16);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), palette().color(QPalette::ButtonText));

        painter.drawPixmap(q.toRect(), pixmap);
    }
}

int MaterialBadge::getDiameter() const
{
    Q_D(const MaterialBadge);

    if (d->icon.isNull())
        return qMax(d->size.width(), d->size.height()) + d->padding;

    return 24;
}
