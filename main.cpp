#include "main_window.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QProcess>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPixmap pixmap(":/images/hello.jpeg");

    QSplashScreen splash(pixmap); // Show a picture before app start.
    splash.show();
    app.processEvents();
    main_window *w = new main_window;
    w->show();
    splash.finish(w);
    return app.exec();
}
