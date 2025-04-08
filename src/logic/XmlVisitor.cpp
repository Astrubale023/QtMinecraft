#include "XmlVisitor.h"
#include "Item.h"
#include "Material.h"
#include "Weapon.h"
#include "Block.h"
#include "OreBlock.h"
#include "LightBlock.h"

QDomElement XmlVisitor::getXmlElement() {
    return xmlElement;
}

void XmlVisitor::visit(const Item& item) {
    QDomDocument doc;
    QDomElement itemElement = doc.createElement("Item");
    itemElement.setAttribute("name", QString::fromStdString(item.getNome()));
    itemElement.setAttribute("imageName", QString::fromStdString(item.getImage()));
    itemElement.setAttribute("stackable", item.isStackable() ? "true" : "false");

    xmlElement = itemElement;
}

void XmlVisitor::visit(const Weapon& weapon) {
    QDomDocument doc;
    QDomElement weaponElement = doc.createElement("Weapon");
    weaponElement.setAttribute("name", QString::fromStdString(weapon.getNome()));
    weaponElement.setAttribute("imageName", QString::fromStdString(weapon.getImage()));
    weaponElement.setAttribute("stackable", weapon.isStackable() ? "true" : "false");
    weaponElement.setAttribute("damage", weapon.getDamage());
    weaponElement.setAttribute("material_name", QString::fromStdString(weapon.getMaterial() ? weapon.getMaterial()->getNome() : ""));

    xmlElement = weaponElement;
}

void XmlVisitor::visit(const Material& material) {
    QDomDocument doc;
    QDomElement materialElement = doc.createElement("Material");
    materialElement.setAttribute("name", QString::fromStdString(material.getNome()));
    materialElement.setAttribute("imageName", QString::fromStdString(material.getImage()));
    materialElement.setAttribute("stackable", material.isStackable() ? "true" : "false");
    materialElement.setAttribute("rarity", QString::fromStdString(Material::rarityToString(material.getRarity())));

    xmlElement = materialElement;
}

void XmlVisitor::visit(const Block& block) {
    QDomDocument doc;
    QDomElement blockElement = doc.createElement("Block");
    blockElement.setAttribute("name", QString::fromStdString(block.getNome()));
    blockElement.setAttribute("imageName", QString::fromStdString(block.getImage()));
    blockElement.setAttribute("hardness", block.getHardness());

    xmlElement = blockElement;
}

void XmlVisitor::visit(const OreBlock& oreBlock) {
    QDomDocument doc;
    QDomElement oreBlockElement = doc.createElement("OreBlock");
    oreBlockElement.setAttribute("name", QString::fromStdString(oreBlock.getNome()));
    oreBlockElement.setAttribute("imageName", QString::fromStdString(oreBlock.getImage()));
    oreBlockElement.setAttribute("hardness", oreBlock.getHardness());
    oreBlockElement.setAttribute("minDrop", oreBlock.getMinDrop());
    oreBlockElement.setAttribute("maxDrop", oreBlock.getMaxDrop());
    oreBlockElement.setAttribute("material_name", QString::fromStdString(oreBlock.getMaterial() ? oreBlock.getMaterial()->getNome() : ""));
    
    xmlElement = oreBlockElement;
}

void XmlVisitor::visit(const LightBlock& lightBlock) {
    QDomDocument doc;
    QDomElement lightBlockElement = doc.createElement("LightBlock");
    lightBlockElement.setAttribute("name", QString::fromStdString(lightBlock.getNome()));
    lightBlockElement.setAttribute("imageName", QString::fromStdString(lightBlock.getImage()));
    lightBlockElement.setAttribute("hardness", lightBlock.getHardness());
    lightBlockElement.setAttribute("brightness", lightBlock.getBrightness());
    lightBlockElement.setAttribute("lightColor", QString::fromStdString(LightBlock::colorToString(lightBlock.getLightColor())));

    xmlElement = lightBlockElement;
}
