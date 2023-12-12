#ifndef MATERIAL_AUTOCOMPLETESTATEMACHINE_H
#define MATERIAL_AUTOCOMPLETESTATEMACHINE_H

#include <QtMaterialWidgets/autocomplete.hpp>

#include <QStateMachine>

class MaterialAutoCompleteStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialAutoCompleteStateMachine)

public:
    explicit MaterialAutoCompleteStateMachine(QWidget* menu);
    ~MaterialAutoCompleteStateMachine();

Q_SIGNALS:
    void shouldOpen();
    void shouldClose();
    void shouldFade();

private:
    QState*  const closedState_;
    QState*  const openState_;
    QState*  const closingState_;
};

#endif // MATERIAL_AUTOCOMPLETESTATEMACHINE_H
