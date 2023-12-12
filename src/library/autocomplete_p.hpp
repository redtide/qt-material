#ifndef MATERIAL_AUTOCOMPLETE_P_H
#define MATERIAL_AUTOCOMPLETE_P_H

#include "textfield_p.hpp"

QT_BEGIN_NAMESPACE
class QWidget;
class QVBoxLayout;
QT_END_NAMESPACE

class MaterialAutoCompleteOverlay;
class MaterialAutoCompleteStateMachine;

class MaterialAutoCompletePrivate : public MaterialTextFieldPrivate
{
    Q_DISABLE_COPY(MaterialAutoCompletePrivate)
    Q_DECLARE_PUBLIC(MaterialAutoComplete)

public:
    MaterialAutoCompletePrivate(MaterialAutoComplete* q);
    virtual ~MaterialAutoCompletePrivate();

    void init();

    MaterialAutoCompleteStateMachine* stateMachine;
    QWidget*     menu;
    QWidget*     frame;
    QVBoxLayout* menuLayout;
    QStringList  dataSource;
    int          maxWidth;
};

#endif // MATERIAL_AUTOCOMPLETE_P_H
