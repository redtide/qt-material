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

    Q_PROPERTY(bool                  isHaloVisible WRITE setHaloVisible READ isHaloVisible)
    Q_PROPERTY(Material::RippleStyle rippleStyle   WRITE setRippleStyle READ rippleStyle)

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

    void setHaloVisible(bool value);
    bool isHaloVisible() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

Q_SIGNALS:
    void currentChanged(int index);

protected:
    bool event(QEvent *event) override;

    void setTabActive(int index, bool active = true);
    void updateTabs();

    const QScopedPointer<MaterialTabsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialTabs)
    Q_DECLARE_PRIVATE(MaterialTabs)
};

#endif // MATERIAL_TABS_H
