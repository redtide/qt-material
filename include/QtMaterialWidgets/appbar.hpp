#ifndef MATERIAL_APPBAR_H
#define MATERIAL_APPBAR_H

#include "dlimpexp.hpp"

#include <QScopedPointer>
#include <QtGlobal>
#include <QtWidgets/QWidget>

class MaterialAppBarPrivate;

class QT_MATERIAL_EXPORT MaterialAppBar : public QWidget
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialAppBar)
    Q_DECLARE_PRIVATE(MaterialAppBar)

public:
    explicit MaterialAppBar(QWidget* parent = nullptr);
    virtual ~MaterialAppBar();

    QSize sizeHint() const override;

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    const QScopedPointer<MaterialAppBarPrivate> d_ptr;
};

#endif // MATERIAL_APPBAR_H
