#ifndef MATERIAL_CHECKABLE_INTERNAL_H
#define MATERIAL_CHECKABLE_INTERNAL_H

#include <QColor>
#include <QIcon>
#include <QtWidgets/QWidget>

class MaterialCheckable;

class MaterialCheckableIcon : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color    READ color    WRITE setColor)
    Q_PROPERTY(qreal  iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(qreal  opacity  READ opacity  WRITE setOpacity)

public:
    MaterialCheckableIcon(const QIcon& icon, MaterialCheckable* parent);
    ~MaterialCheckableIcon();

    QSize sizeHint() const override;

    inline void setIcon(const QIcon& icon);
    inline QIcon icon() const;

    inline void setIconSize(qreal size);
    inline qreal iconSize() const;

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

    inline void setColor(const QColor& color);
    inline QColor color() const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Q_DISABLE_COPY(MaterialCheckableIcon)

    MaterialCheckable* const checkable_;
    QColor color_;
    QIcon  icon_;
    qreal  iconSize_;
    qreal  opacity_;
};

inline void MaterialCheckableIcon::setIcon(const QIcon& icon)
{
    icon_ = icon;
    update();
}

inline QIcon MaterialCheckableIcon::icon() const
{
    return icon_;
}

inline void MaterialCheckableIcon::setIconSize(qreal size)
{
    iconSize_ = size;
    update();
}

inline qreal MaterialCheckableIcon::iconSize() const
{
    return iconSize_;
}

inline void MaterialCheckableIcon::setOpacity(qreal opacity)
{
    opacity_ = opacity;
    update();
}

inline qreal MaterialCheckableIcon::opacity() const
{
    return opacity_;
}

inline void MaterialCheckableIcon::setColor(const QColor& color)
{
    color_ = color;
    update();
}

inline QColor MaterialCheckableIcon::color() const
{
    return color_;
}

#endif // MATERIAL_CHECKABLE_INTERNAL_H
