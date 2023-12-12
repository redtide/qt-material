#ifndef MATERIAL_CHECKABLE_H
#define MATERIAL_CHECKABLE_H

#include "dlimpexp.hpp"

#include <QtWidgets/QAbstractButton>
#include <QColor>
#include <QIcon>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QPaintEvent;
QT_END_NAMESPACE

class MaterialCheckablePrivate;

class QT_MATERIAL_EXPORT MaterialCheckable : public QAbstractButton
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(MaterialCheckable)
    Q_DISABLE_COPY(MaterialCheckable)

    Q_PROPERTY(LabelPosition labelPosition READ labelPosition WRITE setLabelPosition)
    Q_PROPERTY(QIcon         checkedIcon   READ checkedIcon   WRITE setCheckedIcon)
    Q_PROPERTY(QIcon         uncheckedIcon READ uncheckedIcon WRITE setUncheckedIcon)

public:
    enum LabelPosition {
        LabelPositionLeft,
        LabelPositionRight,
    };
    Q_ENUM(LabelPosition)

    explicit MaterialCheckable(QWidget* parent = nullptr);
    ~MaterialCheckable();

    void setLabelPosition(LabelPosition placement);
    LabelPosition labelPosition() const;

    void setCheckedIcon(const QIcon& icon);
    QIcon checkedIcon() const;

    void setUncheckedIcon(const QIcon& icon);
    QIcon uncheckedIcon() const;

    QSize sizeHint() const override;

protected:
    MaterialCheckable(MaterialCheckablePrivate& d, QWidget* parent = nullptr);

    bool event(QEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    virtual void setupProperties();

    const QScopedPointer<MaterialCheckablePrivate> d_ptr;
};

#endif // MATERIAL_CHECKABLE_H
