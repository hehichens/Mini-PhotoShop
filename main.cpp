#include "main_window.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QTimer>
#include <QProcess>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPixmap pixmap(":/images/start.png");

    QSplashScreen splash(pixmap); // Show a picture before app start.
    splash.show();
    QTimer::singleShot(2000, &splash, &QWidget::close); //  keep displayed for 2 seconds
    app.processEvents();
    main_window *w = new main_window;
    w->show();
    splash.finish(w);
    return app.exec();
}
