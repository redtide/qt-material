#ifndef MATERIAL_TABS_INTERNAL_H
#define MATERIAL_TABS_INTERNAL_H

#include <QtMaterialWidgets/flatbutton.hpp>
#include <QtMaterialWidgets/overlaywidget.hpp>

QT_BEGIN_NAMESPACE
class QPropertyAnimation;
QT_END_NAMESPACE

class MaterialTabs;

class MaterialTabsInkBar : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
    MaterialTabsInkBar(MaterialTabs *parent);
    ~MaterialTabsInkBar();

    inline void setTweenValue(qreal value);
    inline qreal tweenValue() const;

    void refreshGeometry();
    void animate();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialTabsInkBar)

    MaterialTabs       *const m_tabs;
    QPropertyAnimation *const m_animation;
    QRect                     m_geometry;
    QRect                     m_previousGeometry;
    qreal                     m_tween;
};

inline void MaterialTabsInkBar::setTweenValue(qreal value)
{
    m_tween = value;
    refreshGeometry();
}

inline qreal MaterialTabsInkBar::tweenValue() const
{
    return m_tween;
}

class MaterialTab : public MaterialFlatButton
{
    Q_OBJECT

public:
    explicit MaterialTab(MaterialTabs *parent);
    ~MaterialTab();

    inline void setActive(bool state);
    inline bool isActive() const;

    QSize sizeHint() const override;

protected Q_SLOTS:
    void activateTab();

protected:
    void paintForeground(QPainter *painter) override;

private:
    Q_DISABLE_COPY(MaterialTab)

    MaterialTabs *const m_tabs;
    bool                m_active;
};

inline void MaterialTab::setActive(bool state)
{
    m_active = state;
    update();
}

inline bool MaterialTab::isActive() const
{
    return m_active;
}

#endif // MATERIAL_TABS_INTERNAL_H
