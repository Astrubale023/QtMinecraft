#ifndef CARDVISITOR_H
#define CARDVISITOR_H

#include "../logic/MinecraftObjVisitor.h"
#include <QString>
#include <QWidget>
#include <QPushButton>

class CardVisitor : public MinecraftObjVisitor {
public:
    void visit(const Item& item) override;
    void visit(const Material& material) override;
    void visit(const Weapon& weapon) override;
    void visit(const Block& block) override;
    void visit(const OreBlock& block) override;
    void visit(const LightBlock& block) override;

    QWidget* getCardWidget();

    QPushButton* getViewButton() const;
    QPushButton* getEditButton() const;
    QPushButton* getDeleteButton() const;

private:
    QWidget *cardWidget;

    QPushButton *viewBtn;
    QPushButton *editBtn;
    QPushButton *deleteBtn;

    void createCard(const QString& name, const QString& imagePath);
};

#endif // CARDVISITOR_H
