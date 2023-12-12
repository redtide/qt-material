#ifndef MATERIAL_SNACKBAR_H
#define MATERIAL_SNACKBAR_H

#include "overlaywidget.hpp"
#include "dlimpexp.hpp"

class MaterialSnackbarPrivate;

class QT_MATERIAL_EXPORT MaterialSnackbar : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialSnackbar)
    Q_DECLARE_PRIVATE(MaterialSnackbar)

    Q_PROPERTY(qreal fontSize         READ fontSize         WRITE setFontSize)
    Q_PROPERTY(int   autoHideDuration READ autoHideDuration WRITE setAutoHideDuration)

public:
    explicit MaterialSnackbar(QWidget* parent = nullptr);
    ~MaterialSnackbar();

    void setAutoHideDuration(int duration);
    int autoHideDuration() const;

    void setBackgroundOpacity(qreal opacity);
    qreal backgroundOpacity() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setBoxWidth(int width);
    int boxWidth() const;

    void setClickToDismissMode(bool value);
    bool clickToDismissMode() const;

public Q_SLOTS:
    void addMessage(const QString& message);
    void addInstantMessage(const QString& message);

protected Q_SLOTS:
    void dequeue();

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    const QScopedPointer<MaterialSnackbarPrivate> d_ptr;
};

#endif // MATERIAL_SNACKBAR_H
