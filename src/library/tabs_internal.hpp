#ifndef MATERIAL_TABS_INTERNAL_H
#define MATERIAL_TABS_INTERNAL_H

#include <QtMaterialWidgets/flatbutton.hpp>
#include <QtMaterialWidgets/overlaywidget.hpp>

QT_BEGIN_NAMESPACE
class QPropertyAnimation;
QT_END_NAMESPACE

class MaterialTabs;

class MaterialTabsIndicatorBar : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
    MaterialTabsIndicatorBar(MaterialTabs* parent);
    ~MaterialTabsIndicatorBar();

    inline void setTweenValue(qreal value);
    inline qreal tweenValue() const;

    void refreshGeometry();
    void animate();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    Q_DISABLE_COPY(MaterialTabsIndicatorBar)

    MaterialTabs*       const tabs_;
    QPropertyAnimation* const animation_;
    QRect                     geometry_;
    QRect                     previousGeometry_;
    qreal                     tween_;
};

inline void MaterialTabsIndicatorBar::setTweenValue(qreal value)
{
    tween_ = value;
    refreshGeometry();
}

inline qreal MaterialTabsIndicatorBar::tweenValue() const
{
    return tween_;
}

class MaterialTab : public MaterialFlatButton
{
    Q_OBJECT

public:
    explicit MaterialTab(MaterialTabs* parent);
    ~MaterialTab();

    inline void setActive(bool state);
    inline bool isActive() const;

    QSize sizeHint() const override;

protected Q_SLOTS:
    void activateTab();

protected:
    void paintForeground(QPainter* painter) override;

private:
    Q_DISABLE_COPY(MaterialTab)

    MaterialTabs* const tabs_;
    bool                active_;
};

inline void MaterialTab::setActive(bool state)
{
    active_ = state;
    update();
}

inline bool MaterialTab::isActive() const
{
    return active_;
}

#endif // MATERIAL_TABS_INTERNAL_H
