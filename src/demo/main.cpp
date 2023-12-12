#include "MainWindow.hpp"

#include <QtMaterialWidgets/resources.hpp>
#if 0
#include <QtMaterialWidgets/style.hpp>
#endif
#include <QtWidgets/QApplication>
#include <QScreen>

static void centerOnScreen(QWidget* widget)
{
    if (const QScreen* screen = QApplication::screenAt(QCursor::pos())) {
        QRect rct = screen->geometry();
        widget->move((rct.width() - widget->width()) / 2,
                     (rct.height() - widget->height()) / 2);
    }
}

int main(int argc, char *argv[])
{
#if 0
    QApplication::setStyle(new MaterialStyle);
#endif
    QApplication app(argc, argv);
#if QT_VERSION < 0x060000
    QString displayName = QStringLiteral("Material Widgets for Qt5");
#else
    QString displayName = QStringLiteral("Material Widgets for Qt6");
#endif
    app.setApplicationDisplayName(displayName);
    app.setOrganizationDomain(QStringLiteral("io.github.Qtilities"));
    app.setOrganizationName(QStringLiteral("Qtilities"));

    material::resources::init();

    MainWindow window;
    centerOnScreen(&window);
    window.show();

    return app.exec();
}
