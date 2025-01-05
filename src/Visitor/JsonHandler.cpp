#include "JsonHandler.h"

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
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();

        // Se incontriamo un oggetto "material", lo aggiungiamo alla lista
        if (obj.contains("type") && obj["type"] == "material") {
            QString materialName = obj["name"].toString();
            bool materialExists = false;
            
            // Verifica se il materiale è già nella lista
            for (MinecraftObj* objInList : objects) {
                Material* mat = dynamic_cast<Material*>(objInList);
                if (mat && mat->getNome() == materialName.toStdString()) {
                    materialExists = true;
                    break;
                }
            }

            // Se il materiale non esiste già, lo creiamo e lo aggiungiamo alla lista
            if (!materialExists) {
                Rarity rarity = static_cast<Rarity>(obj["rarity"].toInt());
                Material* newMaterial = new Material(materialName.toStdString(), true, rarity);
                objects.append(newMaterial);  // Aggiungi il materiale alla lista
            }
        }
    }

    // Poi carica gli oggetti (Weapon, Item, Block, etc.)
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        QString type = obj["type"].toString();
        QString type = obj["name"].toString();

        if (type == "Item") {
            // Se è un Item, lo ricostruiamo
            bool stackable = obj["stackable"].toBool();
            Item* item = new Item(name.toStdString(), stackable);
            objects.append(item);
        }
        else if (type == "Weapon") {
            int damage = obj["damage"].toInt();
            bool stackable = obj["stackable"].toBool();
            // Se è una Weapon, recuperiamo il materiale dalla lista
            QString materialName = obj["material_name"].toString();
            Material* material = nullptr;

            // Cerca il materiale nella lista
            for (MinecraftObj* objInList : objects) {
                Material* mat = dynamic_cast<Material*>(objInList);
                if (mat && mat->getNome() == materialName.toStdString()) {
                    material = mat;
                    break;
                }
            }

            if (material != nullptr) {
                Weapon* weapon = new Weapon(name.toStdString(), stackable, damage, material);
                objects.append(weapon);
            } else {
                Weapon* weapon = new Weapon(name.toStdString(), stackable, damage);
                objects.append(weapon);
            }
        }
        else if (type == "Material") {
            // Se è un Material, lo ricostruiamo
            bool stackable = obj["stackable"].toBool();
            Rarity rarity = Material::stringToRarity(obj["rarity"].toString().toStdString());  // Converte l'intero in un valore Rarity
            Material* material = new Material(name.toStdString(), stackable, rarity);
            objects.append(material);
        }
        else if (type == "Block") {
            // Se è un Block, lo ricostruiamo
            int hardness = obj["hardness"].toInt();
            Block* block = new Block(name.toStdString(), hardness);
            objects.append(block);
        }
        else if (type == "OreBlock") {
            // Se è un OreBlock, lo ricostruiamo
            int hardness = obj["hardness"].toInt();
            int minDrop = obj["minDrop"].toInt();
            int maxDrop = obj["maxDrop"].toInt();
            QString materialName = obj["materialName"].toString();
            Material* material = nullptr;

            // Cerca il materiale nella lista
            for (MinecraftObj* objInList : objects) {
                Material* mat = dynamic_cast<Material*>(objInList);
                if (mat && mat->getNome() == materialName.toStdString()) {
                    material = mat;
                    break;
                }
            }

            if (material != nullptr || material->getNome() == "Default") {
                OreBlock* oreBlock = new OreBlock(name.toStdString(), hardness, minDrop, maxDrop, material);
                objects.append(oreBlock);
            } else {
                OreBlock* oreBlock = new OreBlock(name.toStdString(), hardness, minDrop, maxDrop);
                objects.append(oreBlock);
            }
        }
        else if (type == "LightBlock") {
            int hardness = obj["hardness"].toInt();
            LightColor lightColor = LightBlock::stringToColor(obj["lightColor"].toString().toStdString());
            float brightness = obj["brightness"].toDouble();

            LightBlock* lightBlock = new LightBlock(name.toStdString(), hardness, lightColor, brightness);
            objects.append(lightBlock);
        }
    }
}
