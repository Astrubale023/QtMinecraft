#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QList>
#include "MinecraftObj.h"
#include "Material.h"

class LibraryManager {
private:
    QList<MinecraftObj*> objects;

public:
    LibraryManager();
    ~LibraryManager();

    void addObject(MinecraftObj* obj);
    void deleteObject(const MinecraftObj* obj);

    const QList<MinecraftObj*>& getObjects() const;
    const QList<Material*> getMaterials() const;
    MinecraftObj* getItem(MinecraftObj* obj) const;
    QList<MinecraftObj*> filterObjectsByName(const QString& filter) const;

    void saveToJson(const QString& filename) const;
    void loadFromJson(const QString& filename);

    void saveToXML(const QString& filename) const;
    void loadFromXML(const QString& filename);
};

#endif // LIBRARYMANAGER_H
