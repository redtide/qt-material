#ifndef MATERIAL_TEXTFIELD_H
#define MATERIAL_TEXTFIELD_H

#include "dlimpexp.hpp"

#include <QColor>
#include <QtWidgets/QLineEdit>

class MaterialTextFieldPrivate;

class QT_MATERIAL_EXPORT MaterialTextField : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(bool    useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(bool    showLabel      WRITE setShowLabel      READ hasLabel)
    Q_PROPERTY(bool    showInputLine  WRITE setShowInputLine  READ hasInputLine)
    Q_PROPERTY(qreal   labelFontSize  WRITE setLabelFontSize  READ labelFontSize)
    Q_PROPERTY(QString label          WRITE setLabel          READ label)
    Q_PROPERTY(QColor  labelColor     WRITE setLabelColor     READ labelColor)
    Q_PROPERTY(QColor  textColor      WRITE setTextColor      READ textColor)
    Q_PROPERTY(QColor  inkColor       WRITE setInkColor       READ inkColor)
    Q_PROPERTY(QColor  inputLineColor WRITE setInputLineColor READ inputLineColor)

public:
    explicit MaterialTextField(QWidget* parent = nullptr);
    ~MaterialTextField();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setShowLabel(bool value);
    bool hasLabel() const;

    void setLabelFontSize(qreal size);
    qreal labelFontSize() const;

    void setLabel(const QString &label);
    QString label() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setLabelColor(const QColor &color);
    QColor labelColor() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setInputLineColor(const QColor &color);
    QColor inputLineColor() const;

    void setShowInputLine(bool value);
    bool hasInputLine() const;

protected:
    MaterialTextField(MaterialTextFieldPrivate &d, QWidget* parent = nullptr);

    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialTextFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialTextField)
    Q_DECLARE_PRIVATE(MaterialTextField)
};

#endif // MATERIAL_TEXTFIELD_H
