#include "MainWindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QDebug>

MainWindow::MainWindow(LibraryManager *libraryManager, QWidget *parent)
    : QMainWindow(parent), libraryManager(libraryManager), currentFormView(nullptr) {

    stackedWidget = new QStackedWidget(this);

    // Creazione della ListView
    listView = new ListView(libraryManager, this);
    stackedWidget->addWidget(listView);

    setCentralWidget(stackedWidget);
    createMenuBar();

    // Collegamenti segnali-slot
    connect(listView, &ListView::viewItem, this, [this](MinecraftObj* obj) {
        showFormView(obj, FormVisitor::FormMode::DETAIL);
    });

    connect(listView, &ListView::editItem, this, [this](MinecraftObj* obj) {
        showFormView(obj, FormVisitor::FormMode::EDIT);
    });

    connect(listView, &ListView::addItem, this, [this](MinecraftObj* obj) {
        showFormView(obj, FormVisitor::FormMode::ADD);
    });

    setWindowTitle("Gestione Oggetti Minecraft");
    resize(800, 600);
}

void MainWindow::createMenuBar() {
    //menuBar = new QMenuBar(this);   // menuBar è il nome di un metodo anche e pensa che io voglia assegnare un qualcosa al metodo, lol
    QMenuBar* mainMenuBar = new QMenuBar(this);
    QMenu *fileMenu = mainMenuBar->addMenu("File");

    QAction *saveJsonAction = new QAction("Salva JSON", this);
    QAction *loadJsonAction = new QAction("Carica JSON", this);

    fileMenu->addAction(saveJsonAction);
    fileMenu->addAction(loadJsonAction);

    connect(saveJsonAction, &QAction::triggered, this, &MainWindow::saveJson);
    connect(loadJsonAction, &QAction::triggered, this, &MainWindow::loadJson);

    setMenuBar(mainMenuBar);
}

void MainWindow::showListView() {
    stackedWidget->setCurrentWidget(listView);
    listView->onRefreshClicked();
}

void MainWindow::showFormView(MinecraftObj* obj, FormVisitor::FormMode mode) {
    if (currentFormView) {
        stackedWidget->removeWidget(currentFormView);
        delete currentFormView;
        currentFormView = nullptr;
    }

    // Creiamo un nuovo FormVisitor passando il LibraryManager
    FormVisitor *formVisitor = new FormVisitor(mode, libraryManager);

    if (obj) {
        qDebug() << "Costruzione del form";
        formVisitor->buildForm(obj); // CORRETTO: Usa buildForm() invece di obj->accept()
    }

    qDebug() << "Post if della costruzione form";

    // Prendi il widget del form e aggiungilo alla stackedWidget
    currentFormView = formVisitor->getFormWidget();
    stackedWidget->addWidget(currentFormView);
    stackedWidget->setCurrentWidget(currentFormView);

    // Collegare i segnali per gestire il salvataggio e il ritorno alla lista
    connect(formVisitor, &FormVisitor::objectSaved, this, [this]() {
        showListView();
    });

    connect(formVisitor, &FormVisitor::objectAdded, this, [this]() {
        showListView();
    });

    connect(formVisitor, &FormVisitor::cancelled, this, [this]() {
        showListView();
    });
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
        listView->onRefreshClicked();
    }
}
