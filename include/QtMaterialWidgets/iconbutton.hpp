#ifndef MATERIAL_ICONBUTTON_H
#define MATERIAL_ICONBUTTON_H

#include "dlimpexp.hpp"

#include <QtWidgets/QAbstractButton>

class MaterialIconButtonPrivate;

class QT_MATERIAL_EXPORT MaterialIconButton : public QAbstractButton
{
    Q_OBJECT
//    Q_PROPERTY(bool   useThemeColors READ setUseThemeColors WRITE useThemeColors)
//    Q_PROPERTY(QColor color          READ setColor          WRITE color)
//    Q_PROPERTY(QColor disabledColor  READ setDisabledColor  WRITE disabledColor)

public:
    explicit MaterialIconButton(QWidget* parent = nullptr);
    explicit MaterialIconButton(const QIcon& icon, QWidget* parent = nullptr);
    ~MaterialIconButton();

    QSize sizeHint() const override;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

protected:
    MaterialIconButton(MaterialIconButtonPrivate &d, QWidget* parent = nullptr);

    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialIconButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialIconButton)
    Q_DECLARE_PRIVATE(MaterialIconButton)
};

#endif // MATERIAL_ICONBUTTON_H
