#ifndef MATERIAL_AUTOCOMPLETESTATEMACHINE_H
#define MATERIAL_AUTOCOMPLETESTATEMACHINE_H

#include <QtMaterialWidgets/autocomplete.hpp>

#include <QStateMachine>

class MaterialAutoCompleteStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    explicit MaterialAutoCompleteStateMachine(QWidget *menu);
    ~MaterialAutoCompleteStateMachine();

Q_SIGNALS:
    void shouldOpen();
    void shouldClose();
    void shouldFade();

private:
    Q_DISABLE_COPY(MaterialAutoCompleteStateMachine)

    QWidget *const m_menu;
    QState  *const m_closedState;
    QState  *const m_openState;
    QState  *const m_closingState;
};

#endif // MATERIAL_AUTOCOMPLETESTATEMACHINE_H
