#ifndef MATERIAL_TEXTFIELD_H
#define MATERIAL_TEXTFIELD_H

#include "dlimpexp.hpp"

#include <QtWidgets/QLineEdit>

class MaterialTextFieldPrivate;

class QT_MATERIAL_EXPORT MaterialTextField : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(bool    showLabel     READ hasLabel      WRITE setShowLabel)
    Q_PROPERTY(bool    showInputLine READ hasInputLine  WRITE setShowInputLine)
    Q_PROPERTY(qreal   labelFontSize READ labelFontSize WRITE setLabelFontSize)
    Q_PROPERTY(QString label         READ label         WRITE setLabel)

public:
    explicit MaterialTextField(QWidget* parent = nullptr);
    ~MaterialTextField();

    void setShowLabel(bool value);
    bool hasLabel() const;

    void setLabelFontSize(qreal size);
    qreal labelFontSize() const;

    void setLabel(const QString& label);
    QString label() const;

    void setShowInputLine(bool value);
    bool hasInputLine() const;

protected:
    MaterialTextField(MaterialTextFieldPrivate& d, QWidget* parent = nullptr);

    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    const QScopedPointer<MaterialTextFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialTextField)
    Q_DECLARE_PRIVATE(MaterialTextField)
};

#endif // MATERIAL_TEXTFIELD_H
