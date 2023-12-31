#ifndef MATERIAL_DIALOG_H
#define MATERIAL_DIALOG_H

#include "overlaywidget.hpp"
#include "dlimpexp.hpp"

#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QLayout;
QT_END_NAMESPACE

class MaterialDialogPrivate;

class QT_MATERIAL_EXPORT MaterialDialog : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialDialog)
    Q_DECLARE_PRIVATE(MaterialDialog)

public:
    explicit MaterialDialog(QWidget* parent = nullptr);
    ~MaterialDialog();

    QLayout *windowLayout() const;
    void setWindowLayout(QLayout *layout);

public Q_SLOTS:
    void showDialog();
    void hideDialog();

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialDialogPrivate> d_ptr;
};

#endif // MATERIAL_DIALOG_H
