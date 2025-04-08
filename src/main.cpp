#include <QApplication>
#include "MainWindow.h"
#include "LibraryManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LibraryManager libraryManager;  // 🔹 Creiamo una sola istanza
    MainWindow mainWindow(&libraryManager);  // 🔹 Passiamo il puntatore
    mainWindow.show();

    return app.exec();
}
