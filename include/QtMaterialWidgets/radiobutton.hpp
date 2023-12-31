#ifndef MATERIAL_RADIOBUTTON_H
#define MATERIAL_RADIOBUTTON_H

#include "checkable.hpp"
#include "dlimpexp.hpp"

class QT_MATERIAL_EXPORT MaterialRadioButtonPrivate;

class MaterialRadioButton : public MaterialCheckable
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(MaterialRadioButton)
    Q_DISABLE_COPY(MaterialRadioButton)

public:
    explicit MaterialRadioButton(QWidget* parent = nullptr);
    ~MaterialRadioButton();

protected:
    void setupProperties();
};

#endif // MATERIAL_RADIOBUTTON_H
