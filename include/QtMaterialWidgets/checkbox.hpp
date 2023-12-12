#ifndef MATERIAL_CHECKBOX_H
#define MATERIAL_CHECKBOX_H

#include "dlimpexp.hpp"

#include <QtMaterialWidgets/checkable.hpp>

class MaterialCheckBoxPrivate;

class QT_MATERIAL_EXPORT MaterialCheckBox : public MaterialCheckable
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(MaterialCheckBox)
    Q_DISABLE_COPY(MaterialCheckBox)

public:
    explicit MaterialCheckBox(QWidget *parent = nullptr);
    ~MaterialCheckBox();
};

#endif // MATERIAL_CHECKBOX_H
