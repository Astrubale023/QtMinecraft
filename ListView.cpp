#include "ListView.h"
#include <QHBoxLayout>
#include <QDialog>
#include <QDebug>
#include <QStyle>
#include "LibraryManager.h"
#include "MinecraftObj.h"
#include "CardVisitor.h"
#include "TypeSelectionDialog.h"
#include "ObjectFactory.h"

ListView::ListView(LibraryManager *libraryManager, QWidget *parent)
    : QWidget(parent), libraryManager(libraryManager), columnCount(3) { // Inizialmente 3 colonne

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Barra di ricerca e pulsanti in alto
    QHBoxLayout *topLayout = new QHBoxLayout();
    searchBar = new QLineEdit(this);
    refreshButton = new QPushButton("Aggiorna", this);
    //refreshButton->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    addButton = new QPushButton(this);
    addButton->setIcon(QIcon::fromTheme("list-add"));

    topLayout->addWidget(searchBar);
    topLayout->addWidget(refreshButton);
    topLayout->addWidget(addButton);
    mainLayout->addLayout(topLayout);

    // Area scrollabile per le card
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    scrollWidget = new QWidget();
    cardLayout = new QGridLayout(); // Usa un QGridLayout per disporre le card a griglia
    cardLayout->setSpacing(10);
    scrollWidget->setLayout(cardLayout);

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    // Collegamenti segnali-slot
    connect(searchBar, &QLineEdit::textChanged, this, &ListView::onSearchTextChanged);
    connect(refreshButton, &QPushButton::clicked, this, &ListView::onRefreshClicked);
    connect(addButton, &QPushButton::clicked, this, &ListView::onAddItemClicked);

    // Caricamento iniziale della lista
    populateList();
}

void ListView::populateList(const QString& filter) {
    // Pulizia layout
    QLayoutItem *child;
    while ((child = cardLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Recupera la lista filtrata
    QList<MinecraftObj*> objects = filter.isEmpty() ? 
        libraryManager->getObjects() : 
        libraryManager->filterObjectsByName(filter);

    int row = 0, col = 0;
    for (MinecraftObj* obj : objects) {
        CardVisitor visitor;
        obj->accept(visitor);
        QWidget *card = visitor.getCardWidget();

        // Connessione pulsanti della card ai segnali di ListView
        connect(visitor.getViewButton(), &QPushButton::clicked, [this, obj]() {
            emit viewItem(obj);
        });

        connect(visitor.getEditButton(), &QPushButton::clicked, [this, obj]() {
            emit editItem(obj);
        });

        connect(visitor.getDeleteButton(), &QPushButton::clicked, [this, obj]() {
            onDeleteConfirmed(obj);
        });

        // Aggiungi la card alla griglia
        cardLayout->addWidget(card, row, col);
        col++;
        if (col >= columnCount) {
            col = 0;
            row++;
        }
    }

    adjustGridLayout();
}

void ListView::onSearchTextChanged() {
    populateList(searchBar->text());
}

void ListView::onDeleteConfirmed(MinecraftObj* item) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Conferma Eliminazione",
                                  "Sei sicuro di voler eliminare questo oggetto?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        libraryManager->deleteObject(item);
        populateList(searchBar->text()); // Ricarica la lista
    }
}

void ListView::onRefreshClicked() {
    searchBar->clear();
    populateList();
}

void ListView::onAddItemClicked() {
    TypeSelectionDialog typeDialog;
    if (typeDialog.exec() == QDialog::Accepted) {  // L'utente ha scelto un tipo
        QString selectedType = typeDialog.getSelectedType();

        // Creiamo l'oggetto temporaneo
        MinecraftObj* tempObj = ObjectFactory::createTemporaryObject(selectedType);

        if (tempObj) {
            // Informiamo la MainWindow di cambiare pagina e mostrare il form
            emit addItem(tempObj);
        }
    }
}

void ListView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    adjustGridLayout(); // Adatta la griglia quando cambia la dimensione della finestra
}

void ListView::adjustGridLayout() {
    int width = scrollArea->viewport()->width();
    int cardWidth = 250; // Larghezza approssimativa di una card
    int newColumnCount = std::max(1, width / cardWidth); // Calcola il numero di colonne

    if (newColumnCount != columnCount) {
        columnCount = newColumnCount;
        populateList(searchBar->text()); // Ricarica la lista con il nuovo numero di colonne
    }
}
