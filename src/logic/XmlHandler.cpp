#include "XmlHandler.h"

//#include <QDomDocument>
//#include <QDomElement>
#include <QFile>
#include <QTextStream>
//#include <QDomNodeList>
#include <QString>
#include "Item.h"
#include "Material.h"
#include "Weapon.h"
#include "Block.h"
#include "LightBlock.h"
#include "OreBlock.h"
#include "XmlVisitor.h"

void XmlHandler::saveObjectsToFile(const QString& filename, const QList<MinecraftObj*>& objects) {
    QDomDocument doc;
    QDomElement root = doc.createElement("MinecraftObjects");
    doc.appendChild(root);
    XmlVisitor visitor;

    for (MinecraftObj* obj : objects) {
        obj->accept(visitor);  // Serializza l'oggetto
        root.appendChild(visitor.getXmlElement());  // Aggiunge l'elemento XML alla radice
    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << doc.toString(4);  // Indentazione per leggibilità
        file.close();
    } else {
        qWarning("Couldn't open file for writing");
    }
}

void XmlHandler::loadObjectsFromFile(const QString& filename, QList<MinecraftObj*>& objects) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file for reading");
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning("Failed to parse XML");
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList elements = root.childNodes();

    // Carica prima tutti i materiali
    QList<Material*> materials;
    for (int i = 0; i < elements.size(); ++i) {
        QDomElement elem = elements.at(i).toElement();
        if (!elem.isNull() && elem.tagName() == "Material") {
            QString materialName = elem.attribute("name");
            bool materialExists = false;

            for (Material* mat : materials) {
                if (mat && mat->getNome() == materialName.toStdString()) {
                    materialExists = true;
                    break;
                }
            }

            if (!materialExists) {
                QString img = elem.attribute("imageName");
                Rarity rarity = Material::intToRarity(elem.attribute("rarity").toInt());
                Material* newMaterial = new Material(materialName.toStdString(), img.toStdString(), true, rarity);
                materials.append(newMaterial);
            }
        }
    }

    // Carica gli altri oggetti (Weapon, Item, Block, etc.)
    for (int i = 0; i < elements.size(); ++i) {
        QDomElement elem = elements.at(i).toElement();
        QString type = elem.tagName();
        QString name = elem.attribute("name");
        QString img = elem.attribute("imageName");

        if (type == "Item") {
            bool stackable = (elem.attribute("stackable") == "true");
            Item* item = new Item(name.toStdString(), img.toStdString(), stackable);
            objects.append(item);
        } else if (type == "Material") {
            // Verifica se il materiale è già nella lista
            for (Material* mat : materials) {
                if (mat && mat->getNome() == name.toStdString()) {
                    objects.append(mat);
                    break;
                }
            }
        } else if (type == "Weapon") {
            int damage = elem.attribute("damage").toInt();
            bool stackable = (elem.attribute("stackable") == "true");
            QString materialName = elem.attribute("material_name");
            Material* material = nullptr;

            for (Material* mat : materials) {
                if (mat && mat->getNome() == materialName.toStdString()) {
                    material = mat;
                    break;
                }
            }

            if (material != nullptr) {
                Weapon* weapon = new Weapon(name.toStdString(), img.toStdString(), stackable, damage, material);
                objects.append(weapon);
            } else {
                Weapon* weapon = new Weapon(name.toStdString(), img.toStdString(), stackable, damage);
                objects.append(weapon);
            }
        } else if (type == "Block") {
            int hardness = elem.attribute("hardness").toInt();
            Block* block = new Block(name.toStdString(), img.toStdString(), hardness);
            objects.append(block);
        } else if (type == "OreBlock") {
            int hardness = elem.attribute("hardness").toInt();
            int minDrop = elem.attribute("minDrop").toInt();
            int maxDrop = elem.attribute("maxDrop").toInt();
            QString materialName = elem.attribute("material_name");
            Material* material = nullptr;

            for (Material* mat : materials) {
                if (mat && mat->getNome() == materialName.toStdString()) {
                    material = mat;
                    break;
                }
            }

            if (material != nullptr) {
                OreBlock* oreBlock = new OreBlock(name.toStdString(), img.toStdString(), hardness, minDrop, maxDrop, material);
                objects.append(oreBlock);
            } else {
                OreBlock* oreBlock = new OreBlock(name.toStdString(), img.toStdString(), hardness, minDrop, maxDrop);
                objects.append(oreBlock);
            }
        } else if (type == "LightBlock") {
            int hardness = elem.attribute("hardness").toInt();
            LightColor lightColor = LightBlock::intToColor(elem.attribute("lightColor").toInt());
            float brightness = elem.attribute("brightness").toDouble();

            LightBlock* lightBlock = new LightBlock(name.toStdString(), img.toStdString(), hardness, lightColor, brightness);
            objects.append(lightBlock);
        }
    }
}
