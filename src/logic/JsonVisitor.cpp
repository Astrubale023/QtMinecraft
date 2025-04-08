#include "JsonVisitor.h"
#include "Item.h"
#include "Material.h"
#include "Weapon.h"
#include "Block.h"
#include "OreBlock.h"
#include "LightBlock.h"

QJsonObject JsonVisitor::getJsonObject() {
    return jsonobject;
}

void JsonVisitor::visit(const Item& item) {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "Item";
    tempJsonObject["name"] = QString::fromStdString(item.getNome());
    tempJsonObject["imageName"] = QString::fromStdString(item.getImage());
    tempJsonObject["stackable"] = item.isStackable();
    jsonobject = tempJsonObject;
}

void JsonVisitor::visit(const Weapon& weapon) {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "Weapon";
    tempJsonObject["name"] = QString::fromStdString(weapon.getNome());
    tempJsonObject["imageName"] = QString::fromStdString(weapon.getImage());
    tempJsonObject["stackable"] = weapon.isStackable();
    tempJsonObject["damage"] = weapon.getDamage();
    tempJsonObject["material_name"] = QString::fromStdString(weapon.getMaterial() ? weapon.getMaterial()->getNome() : "");

    jsonobject = tempJsonObject;
}

void JsonVisitor::visit(const Material& material) {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "Material";
    tempJsonObject["name"] = QString::fromStdString(material.getNome());
    tempJsonObject["imageName"] = QString::fromStdString(material.getImage());
    tempJsonObject["stackable"] = material.isStackable();
    tempJsonObject["rariry"] = QString::fromStdString(Material::rarityToString(material.getRarity()));
    
    jsonobject = tempJsonObject;
}

void JsonVisitor::visit(const Block& block) {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "Block";
    tempJsonObject["name"] = QString::fromStdString(block.getNome());
    tempJsonObject["imageName"] = QString::fromStdString(block.getImage());
    tempJsonObject["hardness"] = block.getHardness();
    
    jsonobject = tempJsonObject;
}

void JsonVisitor::visit(const OreBlock& oreBlock) {
    QJsonObject tempJsonObject;

    tempJsonObject["type"] = "OreBlock";
    tempJsonObject["name"] = QString::fromStdString(oreBlock.getNome());
    tempJsonObject["imageName"] = QString::fromStdString(oreBlock.getImage());
    tempJsonObject["hardness"] = oreBlock.getHardness();
    tempJsonObject["minDrop"] = oreBlock.getMinDrop();
    tempJsonObject["maxDrop"] = oreBlock.getMaxDrop();
    tempJsonObject["material_name"] = QString::fromStdString(oreBlock.getMaterial() ? oreBlock.getMaterial()->getNome() : "");

    jsonobject = tempJsonObject;
}

void JsonVisitor::visit(const LightBlock& lightBlock) {
    QJsonObject tempJsonObject;
    tempJsonObject["type"] = "LightBlock";
    tempJsonObject["name"] = QString::fromStdString(lightBlock.getNome());
    tempJsonObject["imageName"] = QString::fromStdString(lightBlock.getImage());
    tempJsonObject["hardness"] = lightBlock.getHardness();
    tempJsonObject["brightness"] = lightBlock.getBrightness();
    tempJsonObject["lightColor"] = QString::fromStdString(LightBlock::colorToString(lightBlock.getLightColor()));
    
    jsonobject = tempJsonObject;
}
