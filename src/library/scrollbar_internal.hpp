#ifndef MATERIAL_SCROLLBAR_INTERNAL_H
#define MATERIAL_SCROLLBAR_INTERNAL_H

#include <QtMaterialWidgets/scrollbar.hpp>

#include <QStateMachine>

class MaterialScrollBarStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    MaterialScrollBarStateMachine(MaterialScrollBar *parent);
    ~MaterialScrollBarStateMachine();

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

private:
    Q_DISABLE_COPY(MaterialScrollBarStateMachine)

    MaterialScrollBar *const m_scrollBar;
    QState            *const focusState_;
    QState            *const m_blurState;
    qreal             opacity_;
};

inline void MaterialScrollBarStateMachine::setOpacity(qreal opacity)
{
    opacity_ = opacity;
    m_scrollBar->update();
}

inline qreal MaterialScrollBarStateMachine::opacity() const
{
    return opacity_;
}

#endif // MATERIAL_SCROLLBAR_INTERNAL_H
