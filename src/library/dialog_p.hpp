#ifndef MATERIAL_DIALOG_P_H
#define MATERIAL_DIALOG_P_H

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QStateMachine;
class QStackedLayout;
QT_END_NAMESPACE

class MaterialDialog;
class MaterialDialogWindow;
class MaterialDialogProxy;

class MaterialDialogPrivate
{
    Q_DISABLE_COPY(MaterialDialogPrivate)
    Q_DECLARE_PUBLIC(MaterialDialog)

public:
    MaterialDialogPrivate(MaterialDialog *q);
    ~MaterialDialogPrivate();

    void init();

    MaterialDialog       *const q_ptr;
    MaterialDialogWindow *dialogWindow;
    QStackedLayout       *proxyStack;
    QStateMachine        *stateMachine;
    MaterialDialogProxy  *proxy;
};

#endif // MATERIAL_DIALOG_P_H
