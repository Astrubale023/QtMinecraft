#include "LibraryManager.h"

#include "JsonHandler.h"
#include "XmlHandler.h"

LibraryManager::LibraryManager() {}

LibraryManager::~LibraryManager() {
    qDeleteAll(objects);
    objects.clear();
}

void LibraryManager::addObject(MinecraftObj* obj) {
    if (obj) {
        objects.append(obj);
    }
}

void LibraryManager::deleteObject(const MinecraftObj* obj) {
    if (objects.removeOne(obj)) {
        delete obj;
    }
}

const QList<MinecraftObj*>& LibraryManager::getObjects() const {
    return objects;
}

const QList<Material*> LibraryManager::getMaterials() const {
    QList<Material*> materialsList;

    for (MinecraftObj* obj : objects) {
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

void LibraryManager::saveToJson(const QString& filename) const {
    JsonHandler::saveObjectsToFile(filename, objects);
}

void LibraryManager::loadFromJson(const QString& filename) {
    qDeleteAll(objects);
    objects.clear();
    JsonHandler::loadObjectsFromFile(filename, objects);
}

void LibraryManager::saveToXML(const QString& filename) const {
    XmlHandler::saveObjectsToFile(filename, objects);
}

void LibraryManager::loadFromXML(const QString& filename) {
    qDeleteAll(objects);
    objects.clear();
    XmlHandler::loadObjectsFromFile(filename, objects);
}