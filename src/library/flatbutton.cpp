#include "flatbutton_internal.hpp"
#include "flatbutton_p.hpp"
#include "defaults.hpp"

#include "QtMaterialWidgets/flatbutton.hpp"
#include <QtMaterialWidgets/ripple.hpp>
#include <QtMaterialWidgets/rippleoverlay.hpp>
#include "palette-helper.hpp"

#include <QEvent>
#include <QIcon>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

static constexpr int IconPadding { 12 };

MaterialFlatButtonPrivate::MaterialFlatButtonPrivate(MaterialFlatButton* q)
    : q_ptr(q)
{
}

MaterialFlatButtonPrivate::~MaterialFlatButtonPrivate()
{
}

void MaterialFlatButtonPrivate::init()
{
    Q_Q(MaterialFlatButton);

    rippleOverlay        = new MaterialRippleOverlay(q);
    stateMachine         = new MaterialFlatButtonStateMachine(q);
    role                 = Material::Default;
    rippleStyle          = Material::PositionedRipple;
    iconPlacement        = Material::LeftIcon;
    overlayStyle         = Material::GrayOverlay;
    bgMode               = Qt::TransparentMode;
    textAlignment        = Qt::AlignHCenter;
    fixedRippleRadius    = 64;
    cornerRadius         = 3;
    baseOpacity          = 0.13;
    fontSize             = material::defaults::global::font::pointSizeF;
    useFixedRippleRadius = false;
    isHaloVisible        = true;

    material::updatePalette(q);

    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);

    QFont font(material::defaults::global::font::family);
    font.setPointSizeF(fontSize);
    font.setWeight(material::defaults::global::font::weight);
    font.setCapitalization(material::defaults::global::font::capitalization);
    q->setFont(font);

    QPainterPath path;
    path.addRoundedRect(q->rect(), cornerRadius, cornerRadius);
    rippleOverlay->setClipPath(path);
    rippleOverlay->setClipping(true);

    stateMachine->setupProperties();
    stateMachine->startAnimations();
}

MaterialFlatButton::MaterialFlatButton(QWidget* parent, Material::ButtonPreset preset)
    : QPushButton(parent)
    , d_ptr(new MaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
}

MaterialFlatButton::MaterialFlatButton(const QString& text,
                                       QWidget* parent,
                                       Material::ButtonPreset preset)
    : QPushButton(text, parent)
    , d_ptr(new MaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
}

MaterialFlatButton::MaterialFlatButton(const QString& text,
                                       Material::Role role,
                                       QWidget* parent,
                                       Material::ButtonPreset preset)
    : QPushButton(text, parent)
    , d_ptr(new MaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
    setRole(role);
}

MaterialFlatButton::~MaterialFlatButton()
{
}

void MaterialFlatButton::applyPreset(Material::ButtonPreset preset)
{
    switch (preset)
    {
    case Material::FlatPreset:
        setOverlayStyle(Material::NoOverlay);
        break;
    case Material::CheckablePreset:
        setOverlayStyle(Material::NoOverlay);
        setCheckable(true);
        setHaloVisible(false);
        break;
    default:
        break;
    }
}

void MaterialFlatButton::setRole(Material::Role role)
{
    Q_D(MaterialFlatButton);

    d->role = role;
    d->stateMachine->setupProperties();
}

Material::Role MaterialFlatButton::role() const
{
    Q_D(const MaterialFlatButton);

    return d->role;
}

void MaterialFlatButton::setFontSize(qreal size)
{
    Q_D(MaterialFlatButton);

    d->fontSize = size;

    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal MaterialFlatButton::fontSize() const
{
    Q_D(const MaterialFlatButton);

    return d->fontSize;
}

void MaterialFlatButton::setHaloVisible(bool visible)
{
    Q_D(MaterialFlatButton);

    d->isHaloVisible = visible;
    update();
}

bool MaterialFlatButton::isHaloVisible() const
{
    Q_D(const MaterialFlatButton);

    return d->isHaloVisible;
}

void MaterialFlatButton::setOverlayStyle(Material::OverlayStyle style)
{
    Q_D(MaterialFlatButton);

    d->overlayStyle = style;
    update();
}

Material::OverlayStyle MaterialFlatButton::overlayStyle() const
{
    Q_D(const MaterialFlatButton);

    return d->overlayStyle;
}

void MaterialFlatButton::setRippleStyle(Material::RippleStyle style)
{
    Q_D(MaterialFlatButton);

    d->rippleStyle = style;
}

Material::RippleStyle MaterialFlatButton::rippleStyle() const
{
    Q_D(const MaterialFlatButton);

    return d->rippleStyle;
}

void MaterialFlatButton::setIconPlacement(Material::ButtonIconPlacement placement)
{
    Q_D(MaterialFlatButton);

    d->iconPlacement = placement;
    update();
}

Material::ButtonIconPlacement MaterialFlatButton::iconPlacement() const
{
    Q_D(const MaterialFlatButton);

    return d->iconPlacement;
}

void MaterialFlatButton::setCornerRadius(qreal radius)
{
    Q_D(MaterialFlatButton);

    d->cornerRadius = radius;
    updateClipPath();
    update();
}

qreal MaterialFlatButton::cornerRadius() const
{
    Q_D(const MaterialFlatButton);

    return d->cornerRadius;
}

void MaterialFlatButton::setBackgroundMode(Qt::BGMode mode)
{
    Q_D(MaterialFlatButton);

    d->bgMode = mode;
    d->stateMachine->setupProperties();
}

Qt::BGMode MaterialFlatButton::backgroundMode() const
{
    Q_D(const MaterialFlatButton);

    return d->bgMode;
}

void MaterialFlatButton::setBaseOpacity(qreal opacity)
{
    Q_D(MaterialFlatButton);

    d->baseOpacity = opacity;
    d->stateMachine->setupProperties();
}

qreal MaterialFlatButton::baseOpacity() const
{
    Q_D(const MaterialFlatButton);

    return d->baseOpacity;
}

void MaterialFlatButton::setCheckable(bool value)
{
    Q_D(MaterialFlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::setCheckable(value);
}

void MaterialFlatButton::setHasFixedRippleRadius(bool value)
{
    Q_D(MaterialFlatButton);

    d->useFixedRippleRadius = value;
}

bool MaterialFlatButton::hasFixedRippleRadius() const
{
    Q_D(const MaterialFlatButton);

    return d->useFixedRippleRadius;
}

void MaterialFlatButton::setFixedRippleRadius(qreal radius)
{
    Q_D(MaterialFlatButton);

    d->fixedRippleRadius = radius;
    setHasFixedRippleRadius(true);
}

void MaterialFlatButton::setTextAlignment(Qt::Alignment alignment)
{
    Q_D(MaterialFlatButton);

    d->textAlignment = alignment;
}

Qt::Alignment MaterialFlatButton::textAlignment() const
{
    Q_D(const MaterialFlatButton);

    return d->textAlignment;
}

QSize MaterialFlatButton::sizeHint() const
{
    ensurePolished();

    QSize label(fontMetrics().size(Qt::TextSingleLine, text()));
    int w = 20 + label.width();
    int h = label.height();

    if (!icon().isNull()) {
        w += iconSize().width() + IconPadding;
        h = qMax(h, iconSize().height());
    }
    return QSize(w, 20 + h);
}

MaterialFlatButton::MaterialFlatButton(MaterialFlatButtonPrivate& d,
                                       QWidget* parent,
                                       Material::ButtonPreset preset)
    : QPushButton(parent)
    , d_ptr(&d)
{
    d_func()->init();

    applyPreset(preset);
}

void MaterialFlatButton::checkStateSet()
{
    Q_D(MaterialFlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::checkStateSet();
}

bool MaterialFlatButton::event(QEvent* event)
{
    if (event->type() == QEvent::ThemeChange) {
        material::updatePalette(this);
        return true;
    }
    return QPushButton::event(event);
}

void MaterialFlatButton::mousePressEvent(QMouseEvent* event)
{
    Q_D(MaterialFlatButton);

    if (Material::NoRipple != d->rippleStyle)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (Material::CenteredRipple == d->rippleStyle) {
            pos = rect().center();
        } else {
            pos = event->pos();
        }

        if (d->useFixedRippleRadius) {
            radiusEndValue = d->fixedRippleRadius;
        } else {
            radiusEndValue = static_cast<qreal>(width())/2;
        }

        MaterialRipple* ripple = new MaterialRipple(pos);

        ripple->setRadiusEndValue(radiusEndValue);
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(palette().color(QPalette::ButtonText));
        ripple->radiusAnimation()->setDuration(600);
        ripple->opacityAnimation()->setDuration(1300);

        d->rippleOverlay->addRipple(ripple);
    }

    QPushButton::mousePressEvent(event);
}

void MaterialFlatButton::mouseReleaseEvent(QMouseEvent* event)
{
    Q_D(MaterialFlatButton);

    QPushButton::mouseReleaseEvent(event);

    d->stateMachine->updateCheckedStatus();
}

void MaterialFlatButton::resizeEvent(QResizeEvent* event)
{
    QPushButton::resizeEvent(event);

    updateClipPath();
}

void MaterialFlatButton::paintEvent(QPaintEvent*)
{
    Q_D(MaterialFlatButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const qreal cr = d->cornerRadius;

    if (cr > 0)
    {
        QPainterPath path;
        path.addRoundedRect(rect(), cr, cr);

        painter.setClipPath(path);
        painter.setClipping(true);
    }

    paintBackground(&painter);
    paintHalo(&painter);

    painter.setOpacity(1);
    painter.setClipping(false);

    paintForeground(&painter);
}

void MaterialFlatButton::paintBackground(QPainter* painter)
{
    Q_D(MaterialFlatButton);

    const qreal overlayOpacity = d->stateMachine->overlayOpacity();
    const qreal checkedProgress = d->stateMachine->checkedOverlayProgress();

    if (Qt::OpaqueMode == d->bgMode) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if (isEnabled())
            brush.setColor(palette().color(QPalette::Button));
        else
            brush.setColor(palette().color(QPalette::Disabled, QPalette::Button));

        painter->setOpacity(1);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect());
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(Qt::NoPen);

    if (!isEnabled()) {
        return;
    }

    if ((Material::NoOverlay != d->overlayStyle) && (overlayOpacity > 0)) {
        if (Material::TintedOverlay == d->overlayStyle)
            brush.setColor(Qt::white); // FIXME: overlayColor
        else
            brush.setColor(Qt::gray);

        painter->setOpacity(overlayOpacity);
        painter->setBrush(brush);
        painter->drawRect(rect());
    }

    if (isCheckable() && checkedProgress > 0) {
        const qreal q = Qt::TransparentMode == d->bgMode ? 0.45 : 0.7;
        brush.setColor(palette().color(QPalette::ButtonText));
        painter->setOpacity(q*checkedProgress);
        painter->setBrush(brush);
        QRect r(rect());
        r.setHeight(static_cast<qreal>(r.height())*checkedProgress);
        painter->drawRect(r);
    }
}

void MaterialFlatButton::paintHalo(QPainter* painter)
{
    Q_D(MaterialFlatButton);

    if (!d->isHaloVisible) {
        return;
    }

    const qreal opacity = d->stateMachine->haloOpacity();
    const qreal s = d->stateMachine->haloScaleFactor()*d->stateMachine->haloSize();
    const qreal radius = static_cast<qreal>(width())*s;

    if (isEnabled() && opacity > 0) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(palette().color(QPalette::ButtonText));
        painter->setOpacity(opacity);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        const QPointF center = rect().center();
        painter->drawEllipse(center, radius, radius);
    }
}

#define COLOR_INTERPOLATE(CH) (1 - progress) * source.CH() + progress * dest.CH()

void MaterialFlatButton::paintForeground(QPainter* painter)
{
    Q_D(MaterialFlatButton);

    if (isEnabled()) {
        painter->setPen(palette().color(QPalette::ButtonText));
        const qreal progress = d->stateMachine->checkedOverlayProgress();
        if (isCheckable() && progress > 0) {
            QColor source = palette().color(QPalette::ButtonText);
            QColor dest = Qt::TransparentMode == d->bgMode
                ? Qt::white
                : palette().color(QPalette::Button);
            if (qFuzzyCompare(1, progress)) {
                painter->setPen(dest);
            } else {
                painter->setPen(QColor(COLOR_INTERPOLATE(red),
                                       COLOR_INTERPOLATE(green),
                                       COLOR_INTERPOLATE(blue),
                                       COLOR_INTERPOLATE(alpha)));
            }
        }
    } else {
        painter->setPen(palette().color(QPalette::Disabled, QPalette::ButtonText));
    }

    if (icon().isNull())  {
        if (Qt::AlignLeft == d->textAlignment) {
            painter->drawText(rect().adjusted(12, 0, 0, 0),
                Qt::AlignLeft | Qt::AlignVCenter, text());
        } else {
            painter->drawText(rect(), Qt::AlignCenter, text());
        }
        return;
    }

    QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
    QSize base(size()-textSize);

    const int iw = iconSize().width() + IconPadding;
    QPoint pos(Qt::AlignLeft == d->textAlignment ? 12 : (base.width()-iw)/2, 0);

    QRect textGeometry(pos + QPoint(0, base.height()/2), textSize);
    QRect iconGeometry(pos + QPoint(0, (height()-iconSize().height())/2), iconSize());

    if (Material::LeftIcon == d->iconPlacement) {
        textGeometry.translate(iw, 0);
    } else {
        iconGeometry.translate(textSize.width() + IconPadding, 0);
    }

    painter->drawText(textGeometry, Qt::AlignCenter, text());

    QPixmap pixmap = icon().pixmap(iconSize());
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), painter->pen().color());
    painter->drawPixmap(iconGeometry, pixmap);
}

void MaterialFlatButton::updateClipPath()
{
    Q_D(MaterialFlatButton);

    const qreal radius = d->cornerRadius;

    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    d->rippleOverlay->setClipPath(path);
}
