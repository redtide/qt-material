#ifndef MATERIAL_CHECKABLE_INTERNAL_H
#define MATERIAL_CHECKABLE_INTERNAL_H

#include <QColor>
#include <QIcon>
#include <QtWidgets/QWidget>

class MaterialCheckable;

class MaterialCheckableIcon : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(qreal iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    MaterialCheckableIcon(const QIcon &icon, MaterialCheckable *parent);
    ~MaterialCheckableIcon();

    QSize sizeHint() const override;

    inline void setIcon(const QIcon &icon);
    inline QIcon icon() const;

    inline void setColor(const QColor &color);
    inline QColor color() const;

    inline void setIconSize(qreal size);
    inline qreal iconSize() const;

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialCheckableIcon)

    MaterialCheckable *const m_checkable;
    QColor                     m_color;
    QIcon                      m_icon;
    qreal                      m_iconSize;
    qreal                      m_opacity;
};

inline void MaterialCheckableIcon::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

inline QIcon MaterialCheckableIcon::icon() const
{
    return m_icon;
}

inline void MaterialCheckableIcon::setColor(const QColor &color)
{
    m_color = color;
    update();
}

inline QColor MaterialCheckableIcon::color() const
{
    return m_color;
}

inline void MaterialCheckableIcon::setIconSize(qreal size)
{
    m_iconSize = size;
    update();
}

inline qreal MaterialCheckableIcon::iconSize() const
{
    return m_iconSize;
}

inline void MaterialCheckableIcon::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

inline qreal MaterialCheckableIcon::opacity() const
{
    return m_opacity;
}

#endif // MATERIAL_CHECKABLE_INTERNAL_H
