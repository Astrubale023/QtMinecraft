#ifndef CARDVISITOR_H
#define CARDVISITOR_H

#include "MinecraftObjVisitor.h"
#include <QString>
#include <QWidget>
#include <QPushButton>

class CardVisitor : public MinecraftObjVisitor {
public:
    void visit(const Item& item) override;   // Modificato per prendere riferimenti
    void visit(const Material& material) override;  // Modificato per prendere riferimenti
    void visit(const Weapon& weapon) override;  // Modificato per prendere riferimenti
    void visit(const Block& block) override;  // Modificato per prendere riferimenti
    void visit(const OreBlock& block) override;  // Modificato per prendere riferimenti
    void visit(const LightBlock& block) override;  // Modificato per prendere riferimenti

    QWidget* getCardWidget(); // Ritorna il widget della card generata

    // Getter per i bottoni
    QPushButton* getViewButton() const;
    QPushButton* getEditButton() const;
    QPushButton* getDeleteButton() const;

private:
    QWidget *cardWidget; // Widget che rappresenta la card

    QPushButton *viewBtn;
    QPushButton *editBtn;
    QPushButton *deleteBtn;

    void createCard(const std::string& name, const QString& imagePath);
};

#endif // CARDVISITOR_H
