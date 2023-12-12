#ifndef MATERIAL_ICONBUTTON_H
#define MATERIAL_ICONBUTTON_H

#include "dlimpexp.hpp"

#include <QtWidgets/QAbstractButton>

class MaterialIconButtonPrivate;

class QT_MATERIAL_EXPORT MaterialIconButton : public QAbstractButton
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialIconButton)
    Q_DECLARE_PRIVATE(MaterialIconButton)

public:
    explicit MaterialIconButton(QWidget* parent = nullptr);
    explicit MaterialIconButton(const QIcon& icon, QWidget* parent = nullptr);
    ~MaterialIconButton();

    QSize sizeHint() const override;

protected:
    MaterialIconButton(MaterialIconButtonPrivate &d, QWidget* parent = nullptr);

    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialIconButtonPrivate> d_ptr;
};

#endif // MATERIAL_ICONBUTTON_H
