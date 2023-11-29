#ifndef MATERIAL_SNACKBAR_H
#define MATERIAL_SNACKBAR_H

#include "overlaywidget.hpp"
#include "dlimpexp.hpp"

class MaterialSnackbarPrivate;

class QT_MATERIAL_EXPORT MaterialSnackbar : public MaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit MaterialSnackbar(QWidget* parent = nullptr);
    ~MaterialSnackbar();

    void setAutoHideDuration(int duration);
    int autoHideDuration() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setBackgroundOpacity(qreal opacity);
    qreal backgroundOpacity() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setBoxWidth(int width);
    int boxWidth() const;

    void setClickToDismissMode(bool value);
    bool clickToDismissMode() const;

public Q_SLOTS:
    void addMessage(const QString &message);
    void addInstantMessage(const QString &message);

protected Q_SLOTS:
    void dequeue();

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialSnackbarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialSnackbar)
    Q_DECLARE_PRIVATE(MaterialSnackbar)
};

#endif // MATERIAL_SNACKBAR_H
