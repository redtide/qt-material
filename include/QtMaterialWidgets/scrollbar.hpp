#ifndef MATERIAL_SCROLLBAR_H
#define MATERIAL_SCROLLBAR_H

#include "dlimpexp.hpp"

#include <QtWidgets/QScrollBar>

class MaterialScrollBarPrivate;

class QT_MATERIAL_EXPORT MaterialScrollBar : public QScrollBar
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialScrollBar)
    Q_DECLARE_PRIVATE(MaterialScrollBar)

    Q_PROPERTY(bool hideOnMouseOut READ hideOnMouseOut WRITE setHideOnMouseOut)

public:
    explicit MaterialScrollBar(QWidget* parent = nullptr);
    ~MaterialScrollBar();

    void setHideOnMouseOut(bool value);
    bool hideOnMouseOut() const;

    QSize sizeHint() const override;

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialScrollBarPrivate> d_ptr;
};

#endif // MATERIAL_SCROLLBAR_H
