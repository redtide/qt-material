#ifndef MATERIAL_SNACKBAR_INTERNAL_H
#define MATERIAL_SNACKBAR_INTERNAL_H

#include <QStateMachine>
#include <QTimer>

class MaterialSnackbar;

class MaterialSnackbarStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    MaterialSnackbarStateMachine(MaterialSnackbar *parent);
    ~MaterialSnackbarStateMachine();

    void setOffset(qreal offset);
    inline qreal offset() const;

public Q_SLOTS:
    void progress();

protected Q_SLOTS:
    void snackbarShown();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialSnackbarStateMachine)

    MaterialSnackbar *const snackbar_;
    QTimer           m_timer;
    qreal            offset_;
};

inline qreal MaterialSnackbarStateMachine::offset() const
{
    return offset_;
}

#endif // MATERIAL_SNACKBAR_INTERNAL_H
