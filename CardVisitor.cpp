#include "CardVisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include "Item.h"
#include "Weapon.h"
#include "Block.h"
#include "LightBlock.h"
#include "OreBlock.h"

void CardVisitor::visit(const Item& item) {
    createCard(item.getNome(), ":/icons/glider.png");  // Usa riferimento
}

void CardVisitor::visit(const Material& material) {
    createCard(material.getNome(), ":/icons/glider.png");  // Usa riferimento
}

void CardVisitor::visit(const Weapon& weapon) {
    createCard(weapon.getNome(), ":/icons/glide.png");  // Usa riferimento
}

void CardVisitor::visit(const Block& block) {
    createCard(block.getNome(), ":/icons/glider.png");  // Usa riferimento
}

void CardVisitor::visit(const LightBlock& lightBlock) {
    createCard(lightBlock.getNome(), ":/icons/glider.png");  // Usa riferimento
}

void CardVisitor::visit(const OreBlock& oreBlock) {
    createCard(oreBlock.getNome(), ":/icons/glider.png");  // Usa riferimento
}

void CardVisitor::createCard(const std::string& name, const QString& imagePath) {
    cardWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(cardWidget);

    // Immagine
    QLabel *imageLabel = new QLabel();
    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio));

    // Nome
    QLabel *nameLabel = new QLabel(QString::fromStdString(name));

    // Pulsanti
    viewBtn = new QPushButton("Visualizza");
    editBtn = new QPushButton("Modifica");
    deleteBtn = new QPushButton("Elimina");

    // Aggiungi i widget al layout
    layout->addWidget(imageLabel);
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
