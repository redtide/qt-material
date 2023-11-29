#ifndef MATERIAL_CHECKABLE_H
#define MATERIAL_CHECKABLE_H

#include "dlimpexp.hpp"

#include <QtWidgets/QAbstractButton>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QPaintEvent;
QT_END_NAMESPACE

class MaterialCheckablePrivate;

class QT_MATERIAL_EXPORT MaterialCheckable : public QAbstractButton
{
    Q_OBJECT
//    Q_PROPERTY(LabelPosition labelPosition  READ setLabelPosition  WRITE labelPosition)
//    Q_PROPERTY(bool          useThemeColors READ setUseThemeColors WRITE useThemeColors)
//    Q_PROPERTY(QColor        checkedColor   READ setCheckedColor   WRITE checkedColor)
//    Q_PROPERTY(QColor        uncheckedColor READ setUncheckedColor WRITE uncheckedColor)
//    Q_PROPERTY(QColor        textColor      READ setTextColor      WRITE textColor)
//    Q_PROPERTY(QColor        disabledColor  READ setDisabledColor  WRITE disabledColor)
//    Q_PROPERTY(QIcon         checkedIcon    READ setCheckedIcon    WRITE checkedIcon)
//    Q_PROPERTY(QIcon         uncheckedIcon  READ setUncheckedIcon  WRITE uncheckedIcon)

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

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setCheckedColor(const QColor &color);
    QColor checkedColor() const;

    void setUncheckedColor(const QColor &color);
    QColor uncheckedColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setCheckedIcon(const QIcon &icon);
    QIcon checkedIcon() const;

    void setUncheckedIcon(const QIcon &icon);
    QIcon uncheckedIcon() const;

    QSize sizeHint() const override;

protected:
    MaterialCheckable(MaterialCheckablePrivate &d, QWidget* parent = nullptr);

    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    virtual void setupProperties();

    const QScopedPointer<MaterialCheckablePrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(MaterialCheckable)
    Q_DISABLE_COPY(MaterialCheckable)
};

#endif // MATERIAL_CHECKABLE_H
