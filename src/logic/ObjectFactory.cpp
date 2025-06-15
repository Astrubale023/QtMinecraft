#include <QDebug>

#include "ObjectFactory.h"
#include "Item.h"
#include "Block.h"
#include "OreBlock.h"
#include "LightBlock.h"
#include "Weapon.h"
#include "Material.h"

MinecraftObj* ObjectFactory::createTemporaryObject(const QString& type) {
    if (type == "Item") {
        return new Item();
    } 
    else if (type == "Material") {
        return new Material();
    }
    else if (type == "Weapon") {
        return new Weapon();
    }
    else if (type == "Block") {
        return new Block();
    } 
    else if (type == "OreBlock") {
        return new OreBlock();
    } 
    else if (type == "LightBlock") {
        return new LightBlock();
    } 

    return nullptr;
}
