#ifndef MATERIAL_DIALOG_INTERNAL_H
#define MATERIAL_DIALOG_INTERNAL_H

#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QStackedLayout;
QT_END_NAMESPACE

class MaterialDialog;
class MaterialDialogWindow;

class MaterialDialogProxy : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

    enum TransparencyMode {
        Transparent,
        SemiTransparent,
        Opaque,
    };

public:
    MaterialDialogProxy(MaterialDialogWindow *source,
                          QStackedLayout *layout,
                          MaterialDialog *dialog,
                          QWidget* parent = nullptr);
    ~MaterialDialogProxy();


    void setOpacity(qreal opacity);
    inline qreal opacity() const;

protected Q_SLOTS:
    void makeOpaque();
    void makeTransparent();

protected:
    QSize sizeHint() const override;

    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialDialogProxy)

    MaterialDialogWindow *const m_source;
    QStackedLayout       *const m_layout;
    MaterialDialog       *const m_dialog;
    qreal                m_opacity;
    TransparencyMode     m_mode;
};

inline qreal MaterialDialogProxy::opacity() const
{
    return m_opacity;
}

class MaterialDialogWindow : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit MaterialDialogWindow(MaterialDialog *dialog, QWidget* parent = nullptr);
    ~MaterialDialogWindow();

    void setOffset(int offset);
    int offset() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialDialogWindow)

    MaterialDialog *const m_dialog;
};

#endif // MATERIAL_DIALOG_INTERNAL_H
