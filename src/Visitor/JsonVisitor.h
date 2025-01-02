#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include "MinecraftObjVisitor.h"
#include <QJsonObject>

class JsonVisitor : public MinecraftObjVisitor {
private:
    QJsonObject jsonobject;

public:
    void visit(const Item& item) override {
        QJsonObject tempJsonObject;
        tempJsonObject["type"] = "Item";
        tempJsonObject["name"] = QString::fromStdString(item.getNome());
        tempJsonObject["stackable"] = item.isStackable();
    }
    void visit(const Weapon& weapon) override {
        QJsonObject tempJsonObject;
        tempJsonObject["type"] = "Weapon";
        tempJsonObject["name"] = QString::fromStdString(weapon.getNome());
        tempJsonObject["stackable"] = weapon.isStackable();
        // Bisogna salvare ancora il materiale
    }
    void visit(const Material& material) override {
        QJsonObject tempJsonObject;
        tempJsonObject["type"] = "Material";
        tempJsonObject["name"] = QString::fromStdString(material.getNome());
        tempJsonObject["stackable"] = material.isStackable();
        tempJsonObject["Rariry"] = Material.rarityToString(material.getRarita());
    }

    void visit(const Block& block) override {
        QJsonObject tempJsonObject;
        tempJsonObject["type"] = "Block";
        tempJsonObject["name"] = QString::fromStdString(block.getNome());
        tempJsonObject["hardness"] = block.getHardness();
    }
    void visit(const OreBlock& oreBlock) override {
        QJsonObject tempJsonObject;
        tempJsonObject["type"] = "OreBlock";
        tempJsonObject["name"] = QString::fromStdString(oreBlock.getNome());
        tempJsonObject["hardness"] = oreBlock.getHardness();
    }
    void visit(const LightBlock& lightBlock) override {
        QJsonObject tempJsonObject;
        tempJsonObject["type"] = "LightBlock";
        tempJsonObject["name"] = QString::fromStdString(lightBlock.getNome());
        tempJsonObject["hardness"] = lightBlock.getHardness();
        tempJsonObject["brightness"] = lightBlock.getBrightness();
        tempJsonObject["lightColor"] = LightBlock.colorToString(lightBlock.getLightColor());
    }
}

#endif // JSONVISITOR_H