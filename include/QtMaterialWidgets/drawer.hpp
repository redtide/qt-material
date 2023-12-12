#ifndef MATERIAL_DRAWER_H
#define MATERIAL_DRAWER_H

#include "overlaywidget.hpp"
#include "dlimpexp.hpp"

class MaterialDrawerPrivate;
class MaterialDrawerStateMachine;

class QT_MATERIAL_EXPORT MaterialDrawer : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialDrawer)
    Q_DECLARE_PRIVATE(MaterialDrawer)

public:
    explicit MaterialDrawer(QWidget* parent = nullptr);
    ~MaterialDrawer();

    void setDrawerWidth(int width);
    int drawerWidth() const;

    void setDrawerLayout(QLayout* layout);
    QLayout* drawerLayout() const;

    void setClickOutsideToClose(bool state);
    bool clickOutsideToClose() const;

    void setAutoRaise(bool state);
    bool autoRaise() const;

    void setOverlayMode(bool value);
    bool overlayMode() const;

public Q_SLOTS:
    void openDrawer();
    void closeDrawer();

protected:
    bool event(QEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    const QScopedPointer<MaterialDrawerPrivate> d_ptr;
};

#endif // MATERIAL_DRAWER_H
