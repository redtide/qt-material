#include "avatar_p.hpp"

#include <QtMaterialWidgets/avatar.hpp>
#include <QtMaterialWidgets/style.hpp>

#include <QPainter>
#include <QPainterPath>

/*!
 *  \class MaterialAvatarPrivate
 *  \internal
 */

/*!
 *  \internal
 */
MaterialAvatarPrivate::MaterialAvatarPrivate(MaterialAvatar *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
MaterialAvatarPrivate::~MaterialAvatarPrivate()
{
}

/*!
 *  \internal
 */
void MaterialAvatarPrivate::init()
{
    Q_Q(MaterialAvatar);

    size           = 40;
    type           = Material::LetterAvatar;
    useThemeColors = true;

    QFont font(q->font());
    font.setPointSizeF(16);
    q->setFont(font);

    QSizePolicy policy(QSizePolicy::MinimumExpanding,
                       QSizePolicy::MinimumExpanding);
    q->setSizePolicy(policy);
}

/*!
 *  \class MaterialAvatar
 */

MaterialAvatar::MaterialAvatar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new MaterialAvatarPrivate(this))
{
    d_func()->init();
}

MaterialAvatar::MaterialAvatar(const QIcon &icon, QWidget *parent)
    : QWidget(parent),
      d_ptr(new MaterialAvatarPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

MaterialAvatar::MaterialAvatar(const QChar &letter, QWidget *parent)
    : QWidget(parent),
      d_ptr(new MaterialAvatarPrivate(this))
{
    d_func()->init();

    setLetter(letter);
}

MaterialAvatar::MaterialAvatar(const QImage &image, QWidget *parent)
    : QWidget(parent),
      d_ptr(new MaterialAvatarPrivate(this))
{
    d_func()->init();

    setImage(image);
}

MaterialAvatar::~MaterialAvatar()
{
}

void MaterialAvatar::setUseThemeColors(bool value)
{
    Q_D(MaterialAvatar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool MaterialAvatar::useThemeColors() const
{
    Q_D(const MaterialAvatar);

    return d->useThemeColors;
}

void MaterialAvatar::setTextColor(const QColor &color)
{
    Q_D(MaterialAvatar);

    d->textColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialAvatar::textColor() const
{
    Q_D(const MaterialAvatar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return MaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void MaterialAvatar::setBackgroundColor(const QColor &color)
{
    Q_D(MaterialAvatar);

    d->backgroundColor = color;
    d->useThemeColors = false;

    update();
}

QColor MaterialAvatar::backgroundColor() const
{
    Q_D(const MaterialAvatar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return MaterialStyle::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

/*!
 *  \reimp
 */
QSize MaterialAvatar::sizeHint() const
{
    Q_D(const MaterialAvatar);

    return QSize(d->size+2, d->size+2);
}

void MaterialAvatar::setSize(int size)
{
    Q_D(MaterialAvatar);

    d->size = size;

    if (!d->image.isNull()) {
        d->pixmap = QPixmap::fromImage(d->image.scaled(d->size, d->size,
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation));
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

void MaterialAvatar::setLetter(const QChar &letter)
{
    Q_D(MaterialAvatar);

    d->letter = letter;
    d->type = Material::LetterAvatar;
    update();
}

QChar MaterialAvatar::letter() const
{
    Q_D(const MaterialAvatar);
    return d->letter;
}

void MaterialAvatar::setImage(const QImage &image)
{
    Q_D(MaterialAvatar);

    d->image = image;
    d->type = Material::ImageAvatar;

    d->pixmap = QPixmap::fromImage(image.scaled(d->size, d->size,
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation));
    update();
}

QImage MaterialAvatar::image() const
{
    Q_D(const MaterialAvatar);
    return d->image;
}

void MaterialAvatar::setIcon(const QIcon &icon)
{
    Q_D(MaterialAvatar);

    d->icon = icon;
    d->type = Material::IconAvatar;
    update();
}

QIcon MaterialAvatar::icon() const
{
    Q_D(const MaterialAvatar);
    return d->icon;
}

Material::AvatarType MaterialAvatar::type() const
{
    Q_D(const MaterialAvatar);

    return d->type;
}

/*!
 *  \reimp
 */
void MaterialAvatar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(MaterialAvatar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    const qreal hs = d->size/2;

    if (!isEnabled())
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(MaterialStyle::instance().themeColor("disabled"));
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width()-d->size)/2, (height()-d->size)/2,
                                   d->size, d->size));
        return;
    }

    if (Material::ImageAvatar != d->type)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(backgroundColor());
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width()-d->size)/2, (height()-d->size)/2,
                                   d->size, d->size));
    }

    switch (d->type)
    {
    case Material::ImageAvatar:
    {
        QPainterPath path;
        path.addEllipse(width()/2-hs, height()/2-hs, d->size, d->size);
        painter.setClipPath(path);

        painter.drawPixmap(QRect(width()/2-hs, height()/2-hs, d->size, d->size),
                           d->pixmap);
        break;
    }
    case Material::IconAvatar:
    {
        QRect iconGeometry((width()-hs)/2, (height()-hs)/2, hs, hs);
        QPixmap pixmap = d->icon.pixmap(hs, hs);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), textColor());
        painter.drawPixmap(iconGeometry, pixmap);
        break;
    }
    case Material::LetterAvatar:
    {
        painter.setPen(textColor());
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r, Qt::AlignCenter, QString(d->letter));
        break;
    }
    default:
        break;
    }
}
