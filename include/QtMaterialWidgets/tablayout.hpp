#ifndef MATERIAL_TABLAYOUT_H
#define MATERIAL_TABLAYOUT_H

#include <QtMaterialWidgets/defs.hpp>
#include "dlimpexp.hpp"

#include <QWidget>

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE

class MaterialTabs;

class QT_MATERIAL_EXPORT MaterialTabLayout : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int                   currentIndex  READ currentIndex  WRITE setCurrentIndex)
    Q_PROPERTY(QString               tabTitle      READ tabTitle      WRITE setTabTitle STORED false)
    Q_PROPERTY(bool                  isHaloVisible READ isHaloVisible WRITE setHaloVisible)
    Q_PROPERTY(Material::RippleStyle rippleStyle   READ rippleStyle   WRITE setRippleStyle)

public:
    explicit MaterialTabLayout(QWidget* parent = nullptr);

    void setHaloVisible(bool value);
    bool isHaloVisible() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    int count() const;

    int currentIndex() const;

    QWidget* widget(int index);

    QString tabTitle() const;

    QSize sizeHint() const override;

public Q_SLOTS:
    void addTab(QWidget* page);
    void insertTab(int index, QWidget* page);
    void removeTab(int index);
    void setTabTitle(QString const& text);
    void setCurrentIndex(int index);

private Q_SLOTS:
    void tabWindowTitleChanged();

Q_SIGNALS:
    void currentIndexChanged(int index);
    void tabTitleChanged(const QString& title);

private:
    MaterialTabs*   tabs;
    QStackedWidget* stack;
};

#endif // MATERIAL_TABLAYOUT_H
