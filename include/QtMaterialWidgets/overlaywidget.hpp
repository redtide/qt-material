#ifndef MATERIAL_OVERLAYWIDGET_H
#define MATERIAL_OVERLAYWIDGET_H

#include "dlimpexp.hpp"

#include <QtWidgets/QWidget>

class QT_MATERIAL_EXPORT MaterialOverlayWidget : public QWidget
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialOverlayWidget)

public:
    explicit MaterialOverlayWidget(QWidget* parent = nullptr);
    ~MaterialOverlayWidget();

protected:
    bool event(QEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

    virtual QRect overlayGeometry() const;
};

#endif // MATERIAL_OVERLAYWIDGET_H
