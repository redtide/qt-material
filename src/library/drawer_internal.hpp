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

    MaterialDrawerWidget *const m_drawer;
    MaterialDrawer       *const m_main;
    QState                 *const m_openingState;
    QState                 *const m_openedState;
    QState                 *const m_closingState;
    QState                 *const m_closedState;
    qreal                         m_opacity;
};

inline qreal MaterialDrawerStateMachine::opacity() const
{
    return m_opacity;
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
    int  m_offset;
};

inline int MaterialDrawerWidget::offset() const
{
    return m_offset;
}

#endif // DRAWER_INTERNAL_H
