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
    resize(1000, 800);
}

void MainWindow::createMenuBar() {
    QMenuBar* mainMenuBar = new QMenuBar(this);
    QMenu *fileMenu = mainMenuBar->addMenu("File");

    QAction *saveAction = new QAction("Salva", this);
    QAction *loadAction = new QAction("Carica", this);

    fileMenu->addAction(saveAction);
    fileMenu->addAction(loadAction);

    // Aggiunta delle shortcut
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    loadAction->setShortcut(QKeySequence("Ctrl+O"));

    connect(saveAction, &QAction::triggered, this, [this]() {
        // Chiede all'utente se vuole salvare in JSON o XML
        QString fileName = QFileDialog::getSaveFileName(this, "Salva come", "", "JSON e XML (*.json *.xml)");
        if (!fileName.isEmpty()) {
            if (fileName.endsWith(".json"))
                saveFile(Format::JSON, fileName);
            else if (fileName.endsWith(".xml"))
                saveFile(Format::XML, fileName);
        }
    });

    connect(loadAction, &QAction::triggered, this, [this]() {
        // Chiede all'utente se vuole caricare JSON o XML
        QString fileName = QFileDialog::getOpenFileName(this, "Carica file", "", "JSON e XML (*.json *.xml)");
        if (!fileName.isEmpty()) {
            if (fileName.endsWith(".json"))
                loadFile(Format::JSON, fileName);
            else if (fileName.endsWith(".xml"))
                loadFile(Format::XML, fileName);
        }
    });

    setMenuBar(mainMenuBar);
}

void MainWindow::showListView() {
    stackedWidget->setCurrentWidget(listView);
    listView->onRefreshClicked();
}

void MainWindow::showFormView(MinecraftObj* obj, const FormVisitor::FormMode& mode) {
    if (currentFormView) {
        stackedWidget->removeWidget(currentFormView);
        delete currentFormView;
        currentFormView = nullptr;
    }

    // Creiamo un nuovo FormVisitor passando il LibraryManager
    FormVisitor *formVisitor = new FormVisitor(mode, libraryManager);

    if (obj) {
        formVisitor->buildForm(obj); // CORRETTO: Usa buildForm() invece di obj->accept()
    }

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

void MainWindow::saveFile(const Format& format, const QString& fileName) const {
    if (!fileName.isEmpty()) {
        if (format == Format::JSON)
            libraryManager->saveToJson(fileName);
        else
            libraryManager->saveToXML(fileName);
    }
}

void MainWindow::loadFile(const Format& format, const QString& fileName) {    
    if (!fileName.isEmpty()) {
        if (format == Format::JSON)
            libraryManager->loadFromJson(fileName);
        else
            libraryManager->loadFromXML(fileName);
        
        listView->onRefreshClicked();
    }
}