#ifndef MATERIAL_FLATBUTTON_INTERNAL_H
#define MATERIAL_FLATBUTTON_INTERNAL_H

#include <QColor>
#include <QStateMachine>

QT_BEGIN_NAMESPACE
class QSequentialAnimationGroup;
QT_END_NAMESPACE

class MaterialFlatButton;

class MaterialFlatButtonStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal overlayOpacity WRITE setOverlayOpacity READ overlayOpacity)
    Q_PROPERTY(qreal checkedOverlayProgress WRITE setCheckedOverlayProgress READ checkedOverlayProgress)
    Q_PROPERTY(qreal haloOpacity WRITE setHaloOpacity READ haloOpacity)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
    Q_PROPERTY(qreal haloScaleFactor WRITE setHaloScaleFactor READ haloScaleFactor)

public:
    explicit MaterialFlatButtonStateMachine(MaterialFlatButton *parent);
    ~MaterialFlatButtonStateMachine();

    void setOverlayOpacity(qreal opacity);
    inline qreal overlayOpacity() const;

    void setCheckedOverlayProgress(qreal progress);
    inline qreal checkedOverlayProgress() const;

    void setHaloOpacity(qreal opacity);
    inline qreal haloOpacity() const;

    void setHaloSize(qreal size);
    inline qreal haloSize() const;

    void setHaloScaleFactor(qreal factor);
    inline qreal haloScaleFactor() const;

    void startAnimations();
    void setupProperties();
    void updateCheckedStatus();

Q_SIGNALS:
    void buttonPressed();
    void buttonChecked();
    void buttonUnchecked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialFlatButtonStateMachine)

    void addTransition(QObject *object, QEvent::Type eventType, QState *fromState, QState *toState);
    void addTransition(QAbstractTransition *transition, QState *fromState, QState *toState);

    MaterialFlatButton *const button_;
    QState               *const topLevelState_;
    QState               *const configState_;
    QState               *const checkableState_;
    QState               *const checkedState_;
    QState               *const uncheckedState_;
    QState               *const neutralState_;
    QState               *const neutralFocusedState_;
    QState               *const hoveredState_;
    QState               *const hoveredFocusedState_;
    QState               *const pressedState_;
    QSequentialAnimationGroup
                         *const haloAnimation_;
    qreal                       overlayOpacity_;
    qreal                       checkedOverlayProgress_;
    qreal                       haloOpacity_;
    qreal                       haloSize_;
    qreal                       haloScaleFactor_;
    bool                        wasChecked_;
};

inline qreal MaterialFlatButtonStateMachine::overlayOpacity() const
{
    return overlayOpacity_;
}

inline qreal MaterialFlatButtonStateMachine::checkedOverlayProgress() const
{
    return checkedOverlayProgress_;
}

inline qreal MaterialFlatButtonStateMachine::haloOpacity() const
{
    return haloOpacity_;
}

inline qreal MaterialFlatButtonStateMachine::haloSize() const
{
    return haloSize_;
}

inline qreal MaterialFlatButtonStateMachine::haloScaleFactor() const
{
    return haloScaleFactor_;
}

#endif // MATERIAL_FLATBUTTON_INTERNAL_H
