#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "MinecraftObj.h"
#include <QString>

class ObjectFactory {
public:
    static MinecraftObj* createTemporaryObject(const QString& type);
};

#endif // OBJECTFACTORY_H
