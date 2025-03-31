#include "CardVisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFrame>
#include "Item.h"
#include "Weapon.h"
#include "Block.h"
#include "LightBlock.h"
#include "OreBlock.h"

void CardVisitor::visit(const Item& item) {
    createCard(QString::fromStdString(item.getNome() + " | Item"), QString::fromStdString("icons/"+item.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const Material& material) {
    createCard(QString::fromStdString(material.getNome() + " | Material"), QString::fromStdString("icons/"+material.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const Weapon& weapon) {
    createCard(QString::fromStdString(weapon.getNome() + " | Weapon"), QString::fromStdString("icons/"+weapon.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const Block& block) {
    createCard(QString::fromStdString(block.getNome() + " | Block"), QString::fromStdString("icons/"+block.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const LightBlock& lightBlock) {
    createCard(QString::fromStdString(lightBlock.getNome() + " | LightBlock"), QString::fromStdString("icons/"+lightBlock.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const OreBlock& oreBlock) {
    createCard(QString::fromStdString(oreBlock.getNome() + " | OreBlock"), QString::fromStdString("icons/"+oreBlock.getImage()));  // Usa riferimento
}

void CardVisitor::createCard(const QString& name, const QString& imagePath) {
    cardWidget = new QWidget();
    cardWidget->setObjectName("card");  // identificativo
    QVBoxLayout *layout = new QVBoxLayout(cardWidget);

    // Aggiungi solo il bordo alla card principale
    cardWidget->setStyleSheet("#card { border: 2px solid black; border-radius: 10px; padding: 5px; }");

    // Immagine
    QLabel *imageLabel = new QLabel();
    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap.scaled(128, 128, Qt::KeepAspectRatio));

    // Nome
    QLabel *nameLabel = new QLabel(name);

    // Pulsanti
    viewBtn = new QPushButton("Visualizza");
    editBtn = new QPushButton("Modifica");
    deleteBtn = new QPushButton("Elimina");

    // Aggiungi i widget al layout
    layout->addWidget(imageLabel, 0, Qt::AlignCenter);
    layout->addWidget(nameLabel, 0, Qt::AlignCenter);
    layout->addWidget(viewBtn);
    layout->addWidget(editBtn);
    layout->addWidget(deleteBtn);
}

QWidget* CardVisitor::getCardWidget() {
    return cardWidget;
}

QPushButton* CardVisitor::getViewButton() const {
    return viewBtn;
}

QPushButton* CardVisitor::getEditButton() const {
    return editBtn;
}

QPushButton* CardVisitor::getDeleteButton() const {
    return deleteBtn;
}
