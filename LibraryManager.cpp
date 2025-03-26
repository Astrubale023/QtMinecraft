#include "LibraryManager.h"

LibraryManager::LibraryManager() {}

LibraryManager::~LibraryManager() {
    qDeleteAll(objects);  // Dealloca tutti gli oggetti nella lista
    objects.clear();
}

void LibraryManager::addObject(MinecraftObj* obj) {
    if (obj) {
        objects.append(obj);
    }
}

void LibraryManager::updateObject(MinecraftObj* oldObj, MinecraftObj* newObj) {
    int index = objects.indexOf(oldObj);
    if (index != -1 && newObj) {
        delete objects[index];  // Cancella il vecchio oggetto
        objects[index] = newObj;  // Sostituisco con quello nuovo
    }
}

void LibraryManager::deleteObject(MinecraftObj* obj) {
    if (objects.removeOne(obj)) {
        delete obj;  // Cancella l'oggetto dalla memoria
    }
}

const QList<MinecraftObj*>& LibraryManager::getObjects() const {
    return objects;
}

const QList<Material*> LibraryManager::getMaterials() const {
    QList<Material*> materialsList;

    for (MinecraftObj* obj : objects) { // Supponiamo che 'objects' contenga tutti gli oggetti
        if (Material* material = dynamic_cast<Material*>(obj)) {
            materialsList.append(material);
        }
    }

    return materialsList;
}

MinecraftObj* LibraryManager::getItem(MinecraftObj* obj) const {
    int index = objects.indexOf(obj);
    return (index != -1) ? objects[index] : nullptr;
}

QList<MinecraftObj*> LibraryManager::filterObjectsByName(const QString& filter) const {
    QList<MinecraftObj*> filteredObjects;
    for (MinecraftObj* obj : objects) {
        if (QString::fromStdString(obj->getNome()).contains(filter, Qt::CaseInsensitive)) {
            filteredObjects.append(obj);
        }
    }
    return filteredObjects;
}

void LibraryManager::saveToJson(const QString& filename) {
    JsonHandler::saveObjectsToFile(filename, objects);
}

void LibraryManager::loadFromJson(const QString& filename) {
    qDeleteAll(objects);  // Libera la memoria degli oggetti precedenti
    objects.clear();
    JsonHandler::loadObjectsFromFile(filename, objects);
}