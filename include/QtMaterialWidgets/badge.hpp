#ifndef MATERIAL_BADGE_H
#define MATERIAL_BADGE_H

#include "overlaywidget.hpp"
#include "dlimpexp.hpp"

#include <QIcon>

class MaterialBadgePrivate;

class QT_MATERIAL_EXPORT MaterialBadge : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialBadge)
    Q_DECLARE_PRIVATE(MaterialBadge)

    Q_PROPERTY(QIcon   icon             READ icon             WRITE setIcon)
    Q_PROPERTY(QString text             READ text             WRITE setText)
    Q_PROPERTY(QPointF relativePosition READ relativePosition WRITE setRelativePosition)

public:
    explicit MaterialBadge(QWidget* parent = nullptr);
    explicit MaterialBadge(const QIcon& icon, QWidget* parent = nullptr);
    explicit MaterialBadge(const QString& text, QWidget* parent = nullptr);
    ~MaterialBadge();

    void setRelativePosition(const QPointF& pos);
    void setRelativePosition(qreal x, qreal y);
    QPointF relativePosition() const;

    void setRelativeXPosition(qreal x);
    qreal relativeXPosition() const;

    void setRelativeYPosition(qreal y);
    qreal relativeYPosition() const;

    void setIcon(const QIcon& icon);
    QIcon icon() const;

    void setText(const QString& text);
    QString text() const;

    QSize sizeHint() const override;

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    int getDiameter() const;

    const QScopedPointer<MaterialBadgePrivate> d_ptr;
};

#endif // MATERIAL_BADGE_H
