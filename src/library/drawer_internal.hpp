#ifndef DRAWER_INTERNAL_H
#define DRAWER_INTERNAL_H

#include <QtMaterialWidgets/overlaywidget.hpp>

#include <QStateMachine>

class MaterialDrawer;
class MaterialDrawerWidget;

class MaterialDrawerStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit MaterialDrawerStateMachine(MaterialDrawerWidget *drawer,
                                          MaterialDrawer *parent);
    ~MaterialDrawerStateMachine();

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    bool isInClosedState() const;

    void updatePropertyAssignments();

Q_SIGNALS:
    void signalOpen();
    void signalClose();

private:
    Q_DISABLE_COPY(MaterialDrawerStateMachine)

    MaterialDrawerWidget *const drawer_;
    MaterialDrawer       *const main_;
    QState                 *const openingState_;
    QState                 *const openedState_;
    QState                 *const closingState_;
    QState                 *const closedState_;
    qreal                         opacity_;
};

inline qreal MaterialDrawerStateMachine::opacity() const
{
    return opacity_;
}

class MaterialDrawerWidget : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit MaterialDrawerWidget(QWidget* parent = nullptr);
    ~MaterialDrawerWidget();

    void setOffset(int offset);
    inline int offset() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    QRect overlayGeometry() const override;

private:
    int  offset_;
};

inline int MaterialDrawerWidget::offset() const
{
    return offset_;
}

#endif // DRAWER_INTERNAL_H
