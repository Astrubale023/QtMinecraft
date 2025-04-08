#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QString>
#include <QList>
#include "MinecraftObj.h"

class XmlHandler {
public:
    static void saveObjectsToFile(const QString& filename, const QList<MinecraftObj*>& objects);
    static void loadObjectsFromFile(const QString& filename, QList<MinecraftObj*>& objects);
};

#endif // XMLHANDLER_H
