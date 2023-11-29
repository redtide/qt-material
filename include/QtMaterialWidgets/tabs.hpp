#ifndef MATERIAL_TABS_H
#define MATERIAL_TABS_H

#include "defs.hpp"
#include "dlimpexp.hpp"

#include <QIcon>
#include <QtWidgets/QWidget>

class MaterialTabsPrivate;
class MaterialTab;

class QT_MATERIAL_EXPORT MaterialTabs : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool                  haloVisible     WRITE setHaloVisible     READ isHaloVisible)
    Q_PROPERTY(Material::RippleStyle rippleStyle     WRITE setRippleStyle     READ rippleStyle)
    Q_PROPERTY(QColor                inkColor        WRITE setInkColor        READ inkColor)
    Q_PROPERTY(QColor                backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor                textColor       WRITE setTextColor       READ textColor)

public:
    explicit MaterialTabs(QWidget* parent = nullptr);
    ~MaterialTabs();

    void addTab(const QString& text, const QIcon& icon = QIcon());
    void insertTab(int index, const QString& text, const QIcon& icon = QIcon());
    void removeTab(int index);

    void setCurrentTab(MaterialTab* tab);
    void setTabText(int index, const QString& text);

    void setCurrentIndex(int index);
    int currentIndex() const;

    QWidget* widget(int index) const;

    int count() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setHaloVisible(bool value);
    bool isHaloVisible() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

Q_SIGNALS:
    void currentChanged(int index);

protected:
    void setTabActive(int index, bool active = true);
    void updateTabs();

    const QScopedPointer<MaterialTabsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialTabs)
    Q_DECLARE_PRIVATE(MaterialTabs)
};

#endif // MATERIAL_TABS_H
