#include "MainWindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include "LibraryManager.h"
#include "MinecraftObj.h"

MainWindow::MainWindow(LibraryManager *libraryManager, QWidget *parent)
    : QMainWindow(parent), libraryManager(libraryManager) {

    stackedWidget = new QStackedWidget(this);

    // Creazione della ListView
    listView = new ListView(libraryManager, this);
    stackedWidget->addWidget(listView);

    /*
    // Creazione della EditView (inizialmente nascosta)
    editView = new EditView(libraryManager, this);
    stackedWidget->addWidget(editView);

    // Creazione della DetailView (inizialmente nascosta)
    detailView = new DetailView(this);
    stackedWidget->addWidget(detailView);
    */

    setCentralWidget(stackedWidget);
    createMenuBar(); // Crea il menu in alto

    // Collegamenti segnali-slot
    connect(listView, &ListView::viewItem, this, &MainWindow::showDetailView);
    connect(listView, &ListView::editItem, this, &MainWindow::showEditView);
    connect(listView, &ListView::addItem, this, [this]() { showEditView(nullptr); });

    // connect(editView, &EditView::backToList, this, &MainWindow::showListView);
    // connect(detailView, &DetailView::backToList, this, &MainWindow::showListView);

    setWindowTitle("Gestione Oggetti Minecraft");
    resize(800, 600); // Dimensioni iniziali
}

void MainWindow::createMenuBar() {
    menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("File");

    saveJsonAction = new QAction("Salva JSON", this);
    loadJsonAction = new QAction("Carica JSON", this);

    fileMenu->addAction(saveJsonAction);
    fileMenu->addAction(loadJsonAction);

    connect(saveJsonAction, &QAction::triggered, this, &MainWindow::saveJson);
    connect(loadJsonAction, &QAction::triggered, this, &MainWindow::loadJson);

    setMenuBar(menuBar);
}

void MainWindow::showListView() {
    stackedWidget->setCurrentWidget(listView);
    listView->onRefreshClicked(); // Aggiorna la lista
}


void MainWindow::showEditView(MinecraftObj* obj) {
    // editView->setObject(obj);
    // stackedWidget->setCurrentWidget(editView);
}

void MainWindow::showDetailView(MinecraftObj* obj) {
    // detailView->setObject(obj);
    // stackedWidget->setCurrentWidget(detailView);
}


void MainWindow::saveJson() {
    QString filename = QFileDialog::getSaveFileName(this, "Salva JSON", "", "JSON Files (*.json)");
    if (!filename.isEmpty()) {
        libraryManager->saveToJson(filename);
    }
}

void MainWindow::loadJson() {
    QString filename = QFileDialog::getOpenFileName(this, "Carica JSON", "", "JSON Files (*.json)");
    if (!filename.isEmpty()) {
        libraryManager->loadFromJson(filename);
        listView->onRefreshClicked(); // Ricarica la lista
    }
}
