#include "ListView.h"
#include <QHBoxLayout>
#include <QDialog>
#include <QDebug>
#include <QStyle>
#include "../logic/LibraryManager.h"
#include "../logic/MinecraftObj.h"
#include "CardVisitor.h"
#include "TypeSelectionDialog.h"
#include "../logic/ObjectFactory.h"

ListView::ListView(LibraryManager *libraryManager, QWidget *parent)
    : QWidget(parent), libraryManager(libraryManager), columnCount(3) {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();
    searchBar = new QLineEdit(this);
    refreshButton = new QPushButton("Aggiorna", this);
    addButton = new QPushButton(this);
    addButton->setIcon(QIcon::fromTheme("list-add"));

    topLayout->addWidget(searchBar);
    topLayout->addWidget(refreshButton);
    topLayout->addWidget(addButton);
    mainLayout->addLayout(topLayout);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    scrollWidget = new QWidget();
    cardLayout = new QGridLayout();
    cardLayout->setSpacing(10);
    scrollWidget->setLayout(cardLayout);

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    connect(searchBar, &QLineEdit::textChanged, this, &ListView::onSearchTextChanged);
    connect(refreshButton, &QPushButton::clicked, this, &ListView::onRefreshClicked);
    connect(addButton, &QPushButton::clicked, this, &ListView::onAddItemClicked);

    populateList();
}

void ListView::populateList(const QString& filter) {
    QLayoutItem *child;
    while ((child = cardLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QList<MinecraftObj*> objects = filter.isEmpty() ? 
        libraryManager->getObjects() : 
        libraryManager->filterObjectsByName(filter);

    int row = 0, col = 0;
    for (MinecraftObj* obj : objects) {
        CardVisitor visitor;
        obj->accept(visitor);
        QWidget *card = visitor.getCardWidget();

        connect(visitor.getViewButton(), &QPushButton::clicked, [this, obj]() {
            emit viewItem(obj);
        });

        connect(visitor.getEditButton(), &QPushButton::clicked, [this, obj]() {
            emit editItem(obj);
        });

        connect(visitor.getDeleteButton(), &QPushButton::clicked, [this, obj]() {
            onDeleteConfirmed(obj);
        });

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
        populateList(searchBar->text());
    }
}

void ListView::onRefreshClicked() {
    searchBar->clear();
    populateList();
}

void ListView::onAddItemClicked() {
    TypeSelectionDialog typeDialog;
    if (typeDialog.exec() == QDialog::Accepted) {
        QString selectedType = typeDialog.getSelectedType();

        MinecraftObj* tempObj = ObjectFactory::createTemporaryObject(selectedType);

        if (tempObj) {
            emit addItem(tempObj);
        }
    }
}

void ListView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    adjustGridLayout();
}

void ListView::adjustGridLayout() {
    int width = scrollArea->viewport()->width();
    int cardWidth = 250;
    int newColumnCount = std::max(1, width / cardWidth);

    if (newColumnCount != columnCount) {
        columnCount = newColumnCount;
        populateList(searchBar->text());
    }
}
