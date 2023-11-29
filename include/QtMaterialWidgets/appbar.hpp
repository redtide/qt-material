#ifndef MATERIAL_APPBAR_H
#define MATERIAL_APPBAR_H

#include "dlimpexp.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

class MaterialAppBarPrivate;

class QT_MATERIAL_EXPORT MaterialAppBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)

public:
    explicit MaterialAppBar(QWidget *parent = nullptr);
    virtual ~MaterialAppBar();

    QSize sizeHint() const override;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    inline QHBoxLayout *appBarLayout() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialAppBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialAppBar)
    Q_DECLARE_PRIVATE(MaterialAppBar)
};

inline QHBoxLayout *MaterialAppBar::appBarLayout() const
{
    return static_cast<QHBoxLayout *>(layout());
}

#endif // MATERIAL_APPBAR_H
