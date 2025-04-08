#include "CardVisitor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFrame>
#include <QStyle>
#include <QIcon>
#include "../logic/Item.h"
#include "../logic/Weapon.h"
#include "../logic/Block.h"
#include "../logic/LightBlock.h"
#include "../logic/OreBlock.h"

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
    viewBtn = new QPushButton();
    viewBtn->setIcon(QIcon::fromTheme("view-preview", QIcon("icons/occhio_di_sauron.png")));
    editBtn = new QPushButton();
    editBtn->setIcon(QIcon::fromTheme("document-edit", QIcon("icons/matitonzola.png")));
    deleteBtn = new QPushButton();
    deleteBtn->setIcon(QIcon::fromTheme("edit-delete"));

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(viewBtn);
    btnLayout->addWidget(editBtn);
    btnLayout->addWidget(deleteBtn);

    // Aggiungi i widget al layout
    layout->addWidget(imageLabel, 0, Qt::AlignCenter);
    layout->addWidget(nameLabel, 0, Qt::AlignCenter);
    layout->addLayout(btnLayout, Qt::AlignRight);
    // layout->addWidget(viewBtn);
    // layout->addWidget(editBtn);
    // layout->addWidget(deleteBtn);
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
