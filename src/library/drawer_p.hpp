#ifndef DRAWER_P_H
#define DRAWER_P_H

#include <QObject>

class MaterialDrawer;
class MaterialDrawerWidget;
class MaterialDrawerStateMachine;

class MaterialDrawerPrivate
{
    Q_DISABLE_COPY(MaterialDrawerPrivate)
    Q_DECLARE_PUBLIC(MaterialDrawer)

public:
    MaterialDrawerPrivate(MaterialDrawer *q);
    ~MaterialDrawerPrivate();

    void init();
    void setClosed(bool value = true);

    MaterialDrawer             *const q_ptr;
    MaterialDrawerWidget       *widget;
    MaterialDrawerStateMachine *stateMachine;
    QWidget                    *window;
    int                        width;
    bool                       clickToClose;
    bool                       autoRaise;
    bool                       closed;
    bool                       overlay;
};

#endif // DRAWER_P_H
