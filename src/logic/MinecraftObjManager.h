#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QList>
#include "item.h"

class LibraryManager {
private:
    QList<MinecraftObj*> items; // Lista di oggetti

public:
    ~LibraryManager(); // Distruttore per liberare memoria

    void addItem(Item* item);
    void removeItem(int index);
    Item* getItem(int index) const;
    QList<Item*> getItems() const { return items; }

    void loadFromJson(const QString &filename);
    void saveToJson(const QString &filename);
};

#endif // LIBRARYMANAGER_H
