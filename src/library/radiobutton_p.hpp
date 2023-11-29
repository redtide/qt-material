#ifndef MATERIAL_RADIOBUTTON_P_H
#define MATERIAL_RADIOBUTTON_P_H

#include "checkable_p.hpp"

#include <QtMaterialWidgets/radiobutton.hpp>

class MaterialRadioButtonPrivate : public MaterialCheckablePrivate
{
    Q_DISABLE_COPY(MaterialRadioButtonPrivate)
    Q_DECLARE_PUBLIC(MaterialRadioButton)

public:
    MaterialRadioButtonPrivate(MaterialRadioButton *q);
    ~MaterialRadioButtonPrivate();

    void init();
};

#endif // MATERIAL_RADIOBUTTON_P_H
