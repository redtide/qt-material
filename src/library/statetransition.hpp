#ifndef MATERIAL_STATETRANSITION_H
#define MATERIAL_STATETRANSITION_H

#include "statetransitionevent.hpp"

#include <QAbstractTransition>

class MaterialStateTransition : public QAbstractTransition
{
    Q_OBJECT

public:
    MaterialStateTransition(MaterialStateTransitionType type);

protected:
    virtual bool eventTest(QEvent *event);
    virtual void onTransition(QEvent *);

private:
    MaterialStateTransitionType type_;
};

#endif // MATERIAL_STATETRANSITION_H
