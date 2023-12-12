#include "avatar_p.hpp"

#include <QtMaterialWidgets/avatar.hpp>
#include "palette-helper.hpp"

#include <QEvent>
#include <QPainter>
#include <QPainterPath>

MaterialAvatarPrivate::MaterialAvatarPrivate(MaterialAvatar* q)
    : q_ptr(q)
{
}

MaterialAvatarPrivate::~MaterialAvatarPrivate()
{
}

void MaterialAvatarPrivate::init()
{
    Q_Q(MaterialAvatar);

    material::updatePalette(q);

    size = 40;
    type = MaterialAvatar::AvatarLetter;

    QFont font(q->font());
    font.setPointSizeF(16);
    q->setFont(font);

    QSizePolicy policy(QSizePolicy::MinimumExpanding,
                       QSizePolicy::MinimumExpanding);
    q->setSizePolicy(policy);
}

MaterialAvatar::MaterialAvatar(QWidget* parent)
    : QWidget(parent)
    , d_ptr(new MaterialAvatarPrivate(this))
{
    d_func()->init();
}

MaterialAvatar::MaterialAvatar(const QIcon& icon, QWidget* parent)
    : QWidget(parent)
    , d_ptr(new MaterialAvatarPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

MaterialAvatar::MaterialAvatar(const QChar& letter, QWidget* parent)
    : QWidget(parent)
    , d_ptr(new MaterialAvatarPrivate(this))
{
    d_func()->init();

    setLetter(letter);
}

MaterialAvatar::MaterialAvatar(const QPixmap& pixmap, QWidget* parent)
    : QWidget(parent)
    , d_ptr(new MaterialAvatarPrivate(this))
{
    d_func()->init();

    setPixmap(pixmap);
}

MaterialAvatar::~MaterialAvatar()
{
}

QSize MaterialAvatar::sizeHint() const
{
    Q_D(const MaterialAvatar);

    return QSize(d->size + 2, d->size + 2);
}

void MaterialAvatar::setSize(int size)
{
    Q_D(MaterialAvatar);

    d->size = size;

    if (!d->pixmap.isNull()) {
        d->pixmap.scaled(d->size, d->size,
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);
    }
    QFont f(font());
    f.setPointSizeF(size*16/40);
    setFont(f);

    update();
}

int MaterialAvatar::size() const
{
    Q_D(const MaterialAvatar);

    return d->size;
}

void MaterialAvatar::setLetter(const QChar& letter)
{
    Q_D(MaterialAvatar);

    d->letter = letter;
    d->type = AvatarType::AvatarLetter;
    update();
}

QChar MaterialAvatar::letter() const
{
    Q_D(const MaterialAvatar);
    return d->letter;
}

void MaterialAvatar::setPixmap(const QPixmap& pixmap)
{
    Q_D(MaterialAvatar);

    d->pixmap = pixmap;
    d->type = AvatarType::AvatarPixmap;

    d->pixmap.scaled(d->size, d->size,
                     Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation);
    update();
}

QPixmap MaterialAvatar::pixmap() const
{
    Q_D(const MaterialAvatar);
    return d->pixmap;
}

void MaterialAvatar::setIcon(const QIcon& icon)
{
    Q_D(MaterialAvatar);

    d->icon = icon;
    d->type = AvatarType::AvatarIcon;
    update();
}

QIcon MaterialAvatar::icon() const
{
    Q_D(const MaterialAvatar);
    return d->icon;
}

MaterialAvatar::AvatarType MaterialAvatar::type() const
{
    Q_D(const MaterialAvatar);

    return d->type;
}

bool MaterialAvatar::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return QWidget::event(event);
}

void MaterialAvatar::paintEvent(QPaintEvent*)
{
    Q_D(MaterialAvatar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    const qreal hs = d->size / 2;

    if (!isEnabled())
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(palette().color(QPalette::Disabled, QPalette::Button));

        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width()-d->size)  / 2,
                                   (height()-d->size) / 2,
                                   d->size, d->size));
        return;
    }

    if (AvatarType::AvatarPixmap != d->type)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(palette().color(QPalette::Normal, QPalette::Button));

        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width()-d->size)  / 2,
                                   (height()-d->size) / 2,
                                   d->size, d->size));
    }
    switch (d->type)
    {
    case AvatarType::AvatarPixmap:
    {
        QPainterPath path;
        path.addEllipse(width()/2-hs, height()/2-hs, d->size, d->size);
        painter.setClipPath(path);
        painter.drawPixmap(QRect(width()/2-hs, height()/2-hs, d->size, d->size), d->pixmap);
        break;
    }
    case AvatarType::AvatarIcon:
    {
        QRect iconGeometry((width()-hs)/2, (height()-hs)/2, hs, hs);
        QPixmap pixmap = d->icon.pixmap(hs, hs);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), palette().color(QPalette::Normal, QPalette::ButtonText));
        painter.drawPixmap(iconGeometry, pixmap);
        break;
    }
    case AvatarType::AvatarLetter:
    {
        painter.setPen(palette().color(QPalette::Normal, QPalette::ButtonText));
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r, Qt::AlignCenter, QString(d->letter));
        break;
    }
    default:
        break;
    }
}
