#ifndef MATERIAL_CHECKBOX_P_H
#define MATERIAL_CHECKBOX_P_H

#include "checkable_p.hpp"

#include <QtMaterialWidgets/checkbox.hpp>

class MaterialCheckBoxPrivate : public MaterialCheckablePrivate
{
    Q_DECLARE_PUBLIC(MaterialCheckBox)

public:
    MaterialCheckBoxPrivate(MaterialCheckBox *q);
    ~MaterialCheckBoxPrivate();

    void init();
};

#endif // MATERIAL_CHECKBOX_P_H
