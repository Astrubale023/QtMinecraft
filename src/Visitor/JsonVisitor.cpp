#include "JsonVisitor.h"

QJsonObject JsonVisitor::getJsonObject() {
    return jsonobject;
}

void JsonVisitor::visit(const Item& item) override {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "Item";
    tempJsonObject["name"] = QString::fromStdString(item.getNome());
    tempJsonObject["stackable"] = item.isStackable();
    jsonobject = tempJsonObject;
}
void JsonVisitor::visit(const Weapon& weapon) override {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "Weapon";
    tempJsonObject["name"] = QString::fromStdString(weapon.getNome());
    tempJsonObject["stackable"] = weapon.isStackable();
    tempJsonObject["stackable"] = weapon.getDamage();
    // salvare il materiale
    tempJsonObject["material_name"] = weapon.getMaterialName();

    jsonobject = tempJsonObject;
}
void JsonVisitor::visit(const Material& material) override {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "Material";
    tempJsonObject["name"] = QString::fromStdString(material.getNome());
    tempJsonObject["stackable"] = material.isStackable();
    tempJsonObject["rariry"] = Material.rarityToString(material.getRarita());
    
    jsonobject = tempJsonObject;
}

void JsonVisitor::visit(const Block& block) override {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "Block";
    tempJsonObject["name"] = QString::fromStdString(block.getNome());
    tempJsonObject["hardness"] = block.getHardness();
    
    jsonobject = tempJsonObject;
}
void JsonVisitor::visit(const OreBlock& oreBlock) override {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "OreBlock";
    tempJsonObject["name"] = QString::fromStdString(oreBlock.getNome());
    tempJsonObject["hardness"] = oreBlock.getHardness();
    tempJsonObject["minDrop"] = oreBlock.getMinDrop();
    tempJsonObject["maxDrop"] = oreBlock.getMaxDrop();

    tempJsonObject["materialName"] = oreBlock.getMaterial().getNome();  // sul read bisognerà accedere a una Qmap
    
    jsonobject = tempJsonObject;
}
void JsonVisitor::visit(const LightBlock& lightBlock) override {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "LightBlock";
    tempJsonObject["name"] = QString::fromStdString(lightBlock.getNome());
    tempJsonObject["hardness"] = lightBlock.getHardness();
    tempJsonObject["brightness"] = lightBlock.getBrightness();
    tempJsonObject["lightColor"] = LightBlock.colorToString(lightBlock.getLightColor());
    
    jsonobject = tempJsonObject;
}