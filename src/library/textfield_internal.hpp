#ifndef MATERIAL_TEXTFIELD_INTERNAL_H
#define MATERIAL_TEXTFIELD_INTERNAL_H

#include <QtMaterialWidgets/textfield.hpp>

#include <QStateMachine>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QPropertyAnimation;
QT_END_NAMESPACE

class MaterialTextFieldLabel;

class MaterialTextFieldStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
    MaterialTextFieldStateMachine(MaterialTextField* parent);
    ~MaterialTextFieldStateMachine();

    void setLabel(MaterialTextFieldLabel* label);

    inline void setProgress(qreal progress);
    inline qreal progress() const;

public Q_SLOTS:
    void setupProperties();

private:
    Q_DISABLE_COPY(MaterialTextFieldStateMachine)

    MaterialTextField*      const textField_;
    QState*                 const normalState_;
    QState*                 const focusedState_;
    MaterialTextFieldLabel* label_;
    QPropertyAnimation*     offsetAnimation_;
    QPropertyAnimation*     colorAnimation_;
    qreal                   progress_;
};

inline void MaterialTextFieldStateMachine::setProgress(qreal progress)
{
    progress_ = progress;
    textField_->update();
}

inline qreal MaterialTextFieldStateMachine::progress() const
{
    return progress_;
}

class MaterialTextFieldLabel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal   scale  READ scale  WRITE setScale)
    Q_PROPERTY(QPointF offset READ offset WRITE setOffset)

public:
    MaterialTextFieldLabel(MaterialTextField* parent);
    ~MaterialTextFieldLabel();

    inline void setScale(qreal scale);
    inline qreal scale() const;

    inline void setOffset(const QPointF& offset);
    inline QPointF offset() const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Q_DISABLE_COPY(MaterialTextFieldLabel)

    MaterialTextField* const textField_;
    qreal  scale_;
    qreal  offsetX_;
    qreal  offsetY_;
};

inline void MaterialTextFieldLabel::setScale(qreal scale)
{
    scale_ = scale;
    update();
}

inline qreal MaterialTextFieldLabel::scale() const
{
    return scale_;
}

inline void MaterialTextFieldLabel::setOffset(const QPointF& offset)
{
    offsetX_ = offset.x();
    offsetY_ = offset.y();
    update();
}

inline QPointF MaterialTextFieldLabel::offset() const
{
    return QPointF(offsetX_, offsetY_);
}

#endif // MATERIAL_TEXTFIELD_INTERNAL_H
