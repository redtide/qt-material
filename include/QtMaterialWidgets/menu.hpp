#ifndef MATERIAL_MENU_H
#define MATERIAL_MENU_H

#include "dlimpexp.hpp"

#include <QtWidgets/QWidget>

class QT_MATERIAL_EXPORT MaterialMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialMenu(QWidget *parent = nullptr);
    ~MaterialMenu();
};

#endif // MATERIAL_MENU_H
