#ifndef MATERIAL_RAISEDBUTTON_H
#define MATERIAL_RAISEDBUTTON_H

#include "flatbutton.hpp"
#include "dlimpexp.hpp"

class MaterialRaisedButtonPrivate;

class QT_MATERIAL_EXPORT MaterialRaisedButton : public MaterialFlatButton
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialRaisedButton)
    Q_DECLARE_PRIVATE(MaterialRaisedButton)

public:
    explicit MaterialRaisedButton(QWidget* parent = nullptr);
    explicit MaterialRaisedButton(const QString& text, QWidget* parent = nullptr);
    ~MaterialRaisedButton();

protected:
    MaterialRaisedButton(MaterialRaisedButtonPrivate& d, QWidget* parent = nullptr);

    bool event(QEvent* event) override;
};

#endif // MATERIAL_RAISEDBUTTON_H
