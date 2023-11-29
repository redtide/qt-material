#ifndef MATERIAL_TOGGLE_H
#define MATERIAL_TOGGLE_H

#include "dlimpexp.hpp"

#include <QtWidgets/QAbstractButton>

class MaterialSwitchPrivate;

class QT_MATERIAL_EXPORT MaterialSwitch : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(Qt::Orientation orientation    WRITE setOrientation    READ orientation)
    Q_PROPERTY(bool            useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(QColor          disabledColor  WRITE setDisabledColor  READ disabledColor)
    Q_PROPERTY(QColor          activeColor    WRITE setActiveColor    READ activeColor)
    Q_PROPERTY(QColor          inactiveColor  WRITE setInactiveColor  READ inactiveColor)
    Q_PROPERTY(QColor          trackColor     WRITE setTrackColor     READ trackColor)

public:
    explicit MaterialSwitch(QWidget* parent = nullptr);
    ~MaterialSwitch();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setActiveColor(const QColor &color);
    QColor activeColor() const;

    void setInactiveColor(const QColor &color);
    QColor inactiveColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

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
