#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QString>
#include <QList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include "MinecraftObj.h"
#include "Weapon.h"
#include "Item.h"
#include "Block.h"
#include "Material.h"
#include "OreBlock.h"
#include "LightBlock.h"
#include "JsonVisitor.h"

class JsonHandler {
public:
    // Salva una lista di oggetti Minecraft in un file JSON
    static void saveObjectsToFile(const QString& filename, const QList<MinecraftObj*>& objects);

    // Carica oggetti da un file JSON, popola un MaterialRepository e una lista di oggetti
    static void loadObjectsFromFile(const QString& filename, QList<MinecraftObj*>& objects);
};

#endif // JSONHANDLER_H
