#ifndef MATERIAL_BADGE_H
#define MATERIAL_BADGE_H

#include "overlaywidget.hpp"
#include "dlimpexp.hpp"

#include <QIcon>

class MaterialBadgePrivate;

class QT_MATERIAL_EXPORT MaterialBadge : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor  textColor        WRITE setTextColor        READ textColor)
    Q_PROPERTY(QColor  backgroundColor  WRITE setBackgroundColor  READ backgroundColor)
    Q_PROPERTY(QPointF relativePosition WRITE setRelativePosition READ relativePosition)
    Q_PROPERTY(QIcon   icon             WRITE setIcon             READ icon)
    Q_PROPERTY(QString text             WRITE setText             READ text)

public:
    explicit MaterialBadge(QWidget* parent = nullptr);
    explicit MaterialBadge(const QIcon &icon, QWidget* parent = nullptr);
    explicit MaterialBadge(const QString &text, QWidget* parent = nullptr);
    ~MaterialBadge();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setRelativePosition(const QPointF &pos);
    void setRelativePosition(qreal x, qreal y);
    QPointF relativePosition() const;

    void setRelativeXPosition(qreal x);
    qreal relativeXPosition() const;

    void setRelativeYPosition(qreal y);
    qreal relativeYPosition() const;

    QSize sizeHint() const override;

    void setIcon(const QIcon &icon);
    QIcon icon() const;

    void setText(const QString &text);
    QString text() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    int getDiameter() const;

    const QScopedPointer<MaterialBadgePrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialBadge)
    Q_DECLARE_PRIVATE(MaterialBadge)
};

#endif // MATERIAL_BADGE_H
