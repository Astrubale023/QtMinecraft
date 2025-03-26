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
    createCard(item.getNome(), QString::fromStdString("icons/"+item.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const Material& material) {
    createCard(material.getNome(), QString::fromStdString("icons/"+material.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const Weapon& weapon) {
    createCard(weapon.getNome(), QString::fromStdString("icons/"+weapon.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const Block& block) {
    createCard(block.getNome(), QString::fromStdString("icons/"+block.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const LightBlock& lightBlock) {
    createCard(lightBlock.getNome(), QString::fromStdString("icons/"+lightBlock.getImage()));  // Usa riferimento
}

void CardVisitor::visit(const OreBlock& oreBlock) {
    createCard(oreBlock.getNome(), QString::fromStdString("icons/"+oreBlock.getImage()));  // Usa riferimento
}

void CardVisitor::createCard(const std::string& name, const QString& imagePath) {
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
    QLabel *nameLabel = new QLabel(QString::fromStdString("\t") + QString::fromStdString(name));

    // Pulsanti
    viewBtn = new QPushButton("Visualizza");
    editBtn = new QPushButton("Modifica");
    deleteBtn = new QPushButton("Elimina");

    // Aggiungi i widget al layout
    layout->addWidget(imageLabel, 0, Qt::AlignCenter);
    layout->addWidget(nameLabel);
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
