#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QAction>
#include "ListView.h"

class LibraryManager;
class MinecraftObj;
// #include "editview.h"
// #include "detailview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    LibraryManager *libraryManager;
    QStackedWidget *stackedWidget;
    ListView *listView;
    // EditView *editView;
    // DetailView *detailView;

    QMenuBar *menuBar;
    QAction *saveJsonAction;
    QAction *loadJsonAction;

    void createMenuBar();  // Crea la barra del menu

public:
    explicit MainWindow(LibraryManager *libraryManager, QWidget *parent = nullptr);

private slots:
    void showListView();          // Torna alla vista della lista
    void showEditView(MinecraftObj* obj = nullptr); // Mostra la schermata di modifica/creazione
    void showDetailView(MinecraftObj* obj); // Mostra la schermata di dettaglio
    void saveJson();              // Salva in JSON
    void loadJson();              // Carica da JSON
};

#endif // MAINWINDOW_H
