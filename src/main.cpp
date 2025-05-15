#include <QApplication>
#include "ui/MainWindow.h"
#include "logic/LibraryManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LibraryManager libraryManager;
    MainWindow mainWindow(&libraryManager);
    mainWindow.show();

    return app.exec();
}
