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

    MaterialSnackbar *const m_snackbar;
    QTimer           m_timer;
    qreal            m_offset;
};

inline qreal MaterialSnackbarStateMachine::offset() const
{
    return m_offset;
}

#endif // MATERIAL_SNACKBAR_INTERNAL_H
