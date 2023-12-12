#include "fab_p.hpp"
#include "palette-helper.hpp"

#include <QtMaterialWidgets/fab.hpp>
#include <QtMaterialWidgets/rippleoverlay.hpp>

#include <QEvent>
#include <QPainter>
#include <QState>
#include <QtWidgets/QGraphicsDropShadowEffect>

MaterialFloatingActionButtonPrivate::MaterialFloatingActionButtonPrivate(MaterialFloatingActionButton* q)
    : MaterialRaisedButtonPrivate(q)
{
}

MaterialFloatingActionButtonPrivate::~MaterialFloatingActionButtonPrivate()
{
}

void MaterialFloatingActionButtonPrivate::init()
{
    Q_Q(MaterialFloatingActionButton);

    material::updatePalette(q);

    corner = Qt::BottomRightCorner;
    isMini = false;
    offsX  = 34;
    offsY  = 36;

    q->setRole(Material::Primary);
    q->setFixedSize(DefaultDiameter, DefaultDiameter);
    q->setGeometry(fabGeometry());

    setupProperties();

    if (q->parentWidget())
        q->parentWidget()->installEventFilter(q);

    q->setFixedRippleRadius(50);
}

QRect MaterialFloatingActionButtonPrivate::fabGeometry() const
{
    Q_Q(const MaterialFloatingActionButton);

    QWidget* parent = q->parentWidget();
    if (!parent)
        return QRect();

    const int s = isMini ? MiniDiameter : DefaultDiameter;

    switch (corner)
    {
    case Qt::TopLeftCorner:
        return QRect(offsX, offsY, s, s);
    case Qt::TopRightCorner:
        return QRect(parent->width()-(offsX+s), offsY, s, s);
    case Qt::BottomLeftCorner:
        return QRect(offsX, parent->height()-(offsY+s), s, s);
    case Qt::BottomRightCorner:
    default:
        break;
    }
    return QRect(parent->width()-(offsX+s), parent->height()-(offsY+s), s, s);
}

void MaterialFloatingActionButtonPrivate::setupProperties()
{
    if (isMini) {
        effect->setColor(QColor(0, 0, 0, 80));
        normalState->assignProperty(effect, "offset", QPointF(0, 3));
        normalState->assignProperty(effect, "blurRadius", 13);
        pressedState->assignProperty(effect, "offset", QPointF(0, 7));
        pressedState->assignProperty(effect, "blurRadius", 20);
        return;
    }
    effect->setColor(QColor(0, 0, 0, 105));
    normalState->assignProperty(effect, "offset", QPointF(0, 6));
    normalState->assignProperty(effect, "blurRadius", 16);
    pressedState->assignProperty(effect, "offset", QPointF(0, 11));
    pressedState->assignProperty(effect, "blurRadius", 28);
}

MaterialFloatingActionButton::MaterialFloatingActionButton(QWidget* parent)
    : MaterialRaisedButton(*new MaterialFloatingActionButtonPrivate(this), parent)
{
    d_func()->init();
}

MaterialFloatingActionButton::MaterialFloatingActionButton(const QIcon& icon, QWidget* parent)
    : MaterialRaisedButton(*new MaterialFloatingActionButtonPrivate(this), parent)
{
    d_func()->init();

    setIcon(icon);
}

MaterialFloatingActionButton::~MaterialFloatingActionButton()
{
}

QSize MaterialFloatingActionButton::sizeHint() const
{
    Q_D(const MaterialFloatingActionButton);

    if (d->isMini)
        return QSize(MaterialFloatingActionButtonPrivate::MiniDiameter,
                     MaterialFloatingActionButtonPrivate::MiniDiameter);

    return QSize(MaterialFloatingActionButtonPrivate::DefaultDiameter,
                 MaterialFloatingActionButtonPrivate::DefaultDiameter);
}

void MaterialFloatingActionButton::setMini(bool state)
{
    Q_D(MaterialFloatingActionButton);

    if (state == d->isMini)
        return;

    d->isMini = state;

    setFixedSize(d->diameter(), d->diameter());
    setFixedRippleRadius(state ? 30 : 50);

    d->setupProperties();
    updateClipPath();
    setGeometry(d->fabGeometry());
    update();
}

bool MaterialFloatingActionButton::isMini() const
{
    Q_D(const MaterialFloatingActionButton);

    return d->isMini;
}

void MaterialFloatingActionButton::setCorner(Qt::Corner corner)
{
    Q_D(MaterialFloatingActionButton);

    if (corner == d->corner)
        return;

    d->corner = corner;
    setGeometry(d->fabGeometry());
    update();
}

Qt::Corner MaterialFloatingActionButton::corner() const
{
    Q_D(const MaterialFloatingActionButton);

    return d->corner;
}

void MaterialFloatingActionButton::setOffset(int x, int y)
{
    Q_D(MaterialFloatingActionButton);

    d->offsX = x;
    d->offsY = y;
    setGeometry(d->fabGeometry());
    update();
}

QSize MaterialFloatingActionButton::offset() const
{
    Q_D(const MaterialFloatingActionButton);

    return QSize(d->offsX, d->offsY);
}

void MaterialFloatingActionButton::setXOffset(int x)
{
    Q_D(MaterialFloatingActionButton);

    d->offsX = x;
    setGeometry(d->fabGeometry());
    update();
}

int MaterialFloatingActionButton::xOffset() const
{
    Q_D(const MaterialFloatingActionButton);

    return d->offsX;
}

void MaterialFloatingActionButton::setYOffset(int y)
{
    Q_D(MaterialFloatingActionButton);

    d->offsY = y;
    setGeometry(d->fabGeometry());
    update();
}

int MaterialFloatingActionButton::yOffset() const
{
    Q_D(const MaterialFloatingActionButton);

    return d->offsY;
}

bool MaterialFloatingActionButton::event(QEvent* event)
{
    Q_D(MaterialFloatingActionButton);

    if (!parent())
        return MaterialRaisedButton::event(event);

    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        parent()->installEventFilter(this);
        setGeometry(d->fabGeometry());
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        parent()->removeEventFilter(this);
        break;
    }
    case QEvent::ThemeChange: {
        material::updatePalette(this);
        return true;
    }
    default:
        break;
    }
    return MaterialRaisedButton::event(event);
}

bool MaterialFloatingActionButton::eventFilter(QObject* obj, QEvent* event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type) {
        Q_D(MaterialFloatingActionButton);
        setGeometry(d->fabGeometry());
    }
    return MaterialRaisedButton::eventFilter(obj, event);
}

void MaterialFloatingActionButton::paintEvent(QPaintEvent*)
{
    Q_D(MaterialFloatingActionButton);

    QRect square = QRect(0, 0, d->diameter(), d->diameter());
    square.moveCenter(rect().center());

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    if (isEnabled())
        brush.setColor(palette().color(QPalette::Button));
    else
        brush.setColor(palette().color(QPalette::Disabled, QPalette::Button));

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(square);

    QRect iconGeometry(0, 0, d->iconSize(), d->iconSize());
    iconGeometry.moveCenter(square.center());

    QPixmap pixmap = icon().pixmap(QSize(d->iconSize(), d->iconSize()));
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(),
        isEnabled()
            ? palette().color(QPalette::ButtonText)
            : palette().color(QPalette::Disabled, QPalette::ButtonText));
    painter.drawPixmap(iconGeometry, pixmap);
}

void MaterialFloatingActionButton::updateClipPath()
{
    Q_D(MaterialFloatingActionButton);

    QPainterPath path;
    path.addEllipse(0, 0, d->diameter(), d->diameter());
    d->rippleOverlay->setClipPath(path);
}
