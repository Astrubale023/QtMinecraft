#include "JsonHandler.h"

#include <QDebug>

#include "Item.h"
#include "Material.h"
#include "Weapon.h"
#include "Block.h"
#include "LightBlock.h"
#include "OreBlock.h"
#include "JsonVisitor.h"

void JsonHandler::saveObjectsToFile(const QString& filename, const QList<MinecraftObj*>& objects) {
    QJsonArray jsonArray;
    JsonVisitor visitor;

    for (MinecraftObj* obj : objects) {
        obj->accept(visitor);  // Serializza l'oggetto
        jsonArray.append(visitor.getJsonObject());  // Aggiunge l'oggetto serializzato
    }

    QJsonDocument doc(jsonArray);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    } else {
        qWarning("Couldn't open file for writing");
    }
}

void JsonHandler::loadObjectsFromFile(const QString& filename, QList<MinecraftObj*>& objects) {
    QFile file(filename);
    
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file for reading");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = doc.array();

    // Carica prima tutti i materiali e aggiungili alla QList principale
    QList<Material*> materials;
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();

        // Se incontriamo un oggetto "material", lo aggiungiamo alla lista
        if (obj.contains("type") && obj["type"] == "Material") {
            QString materialName = obj["name"].toString();
            bool materialExists = false;
            
            // Verifica se il materiale è già nella lista
            for (Material* mat : materials) {
                if (mat && mat->getNome() == materialName.toStdString()) {
                    materialExists = true;
                    break;
                }
            }

            // Se il materiale non esiste già, lo creiamo e lo aggiungiamo alla lista
            if (!materialExists) {
                QString img = obj["imageName"].toString();
                Rarity rarity = Material::intToRarity(obj["rarity"].toInt());
                Material* newMaterial = new Material(materialName.toStdString(), img.toStdString(), true, rarity);
                materials.append(newMaterial);  // Aggiungi il materiale alla lista
            }
        }
    }

    // Poi carica gli oggetti (Weapon, Item, Block, etc.)
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        QString type = obj["type"].toString();
        QString name = obj["name"].toString();
        QString img = obj["imageName"].toString();

        if (type == "Item") {
            // Se è un Item, lo ricostruiamo
            bool stackable = obj["stackable"].toBool();
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
            int damage = obj["damage"].toInt();
            bool stackable = obj["stackable"].toBool();
            // Se è una Weapon, recuperiamo il materiale dalla lista
            QString materialName = obj["material_name"].toString();
            Material* material = nullptr;

            // Cerca il materiale nella lista
            for (Material* mat : materials) {
                if (mat && mat->getNome() == materialName.toStdString()) {
                    material = mat;
                    break;
                }
            }

            if (material != nullptr) {
                Weapon* weapon = new Weapon(name.toStdString(), img.toStdString(), stackable, damage, material);
                objects.append(weapon);
            } else {    // non ha trovato il materiale e allora me lo mette lui a deafult
                Weapon* weapon = new Weapon(name.toStdString(), img.toStdString(), stackable, damage);
                objects.append(weapon);
            }
        } else if (type == "Block") {
            // Se è un Block, lo ricostruiamo
            int hardness = obj["hardness"].toInt();
            Block* block = new Block(name.toStdString(), img.toStdString(), hardness);
            objects.append(block);
        } else if (type == "OreBlock") {
            // Se è un OreBlock, lo ricostruiamo
            int hardness = obj["hardness"].toInt();
            int minDrop = obj["minDrop"].toInt();
            int maxDrop = obj["maxDrop"].toInt();
            QString materialName = obj["materialName"].toString();
            Material* material = nullptr;

            // Cerca il materiale nella lista
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
            int hardness = obj["hardness"].toInt();
            LightColor lightColor = LightBlock::intToColor(obj["lightColor"].toInt());
            float brightness = obj["brightness"].toDouble();

            LightBlock* lightBlock = new LightBlock(name.toStdString(), img.toStdString(), hardness, lightColor, brightness);
            objects.append(lightBlock);
        }
    }
}
