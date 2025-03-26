#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QList>
#include "MinecraftObj.h"
#include "Material.h"
#include "JsonHandler.h"

class LibraryManager {
private:
    QList<MinecraftObj*> objects;

public:
    LibraryManager();
    ~LibraryManager();

    void addObject(MinecraftObj* obj);
    void updateObject(MinecraftObj* oldObj, MinecraftObj* newObj);
    void deleteObject(MinecraftObj* obj);

    const QList<MinecraftObj*>& getObjects() const;
    const QList<Material*> getMaterials() const;
    MinecraftObj* getItem(MinecraftObj* obj) const;
    QList<MinecraftObj*> filterObjectsByName(const QString& filter) const;

    void saveToJson(const QString& filename);
    void loadFromJson(const QString& filename);
};

#endif // LIBRARYMANAGER_H
