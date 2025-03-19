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
class MinecraftObj;

class JsonHandler {
public:
    // Salva una lista di oggetti Minecraft in un file JSON
    static void saveObjectsToFile(const QString& filename, const QList<MinecraftObj*>& objects);

    // Carica oggetti da un file JSON, popola un MaterialRepository e una lista di oggetti
    static void loadObjectsFromFile(const QString& filename, QList<MinecraftObj*>& objects);
};

#endif // JSONHANDLER_H
