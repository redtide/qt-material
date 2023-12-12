#ifndef MATERIAL_TOGGLE_H
#define MATERIAL_TOGGLE_H

#include "dlimpexp.hpp"

#include <QtWidgets/QAbstractButton>

class MaterialSwitchPrivate;

class QT_MATERIAL_EXPORT MaterialSwitch : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)

public:
    explicit MaterialSwitch(QWidget* parent = nullptr);
    ~MaterialSwitch();

    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const;

    QSize sizeHint() const override;

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialSwitchPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialSwitch)
    Q_DECLARE_PRIVATE(MaterialSwitch)
};

#endif // MATERIAL_TOGGLE_H
