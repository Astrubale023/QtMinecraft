#include "JsonHandler.h"

void JsonHandler::saveObjectsToFile(const QString& filename, const QList<MinecraftObj*>& objects) {
    QJsonArray jsonArray;
    JsonVisitor visitor;

    for (MinecraftObj* obj : objects) {
        obj->accept(visitor);  // Serializza l'oggetto
        jsonArray.append(visitor.getJson());  // Aggiunge l'oggetto serializzato
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
        QString name = obj["name"].toString();

        if (obj.contains("material_name")) {
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
                int damage = obj["damage"].toInt();
                Weapon* weapon = new Weapon(name.toStdString(), material, damage);
                objects.append(weapon);
            }
        } else if (obj.contains("stackable")) {
            // Se è un Item, lo ricostruiamo
            bool stackable = obj["stackable"].toBool();
            Item* item = new Item(name.toStdString(), stackable);
            objects.append(item);
        }
        // Aggiungi altre logiche per Block e altri oggetti
    }
}
