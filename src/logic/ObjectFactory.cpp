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
        return new Item();  // Nome di default, non impilabile
    } 
    else if (type == "Material") {
        return new Material();
    }
    else if (type == "Weapon") {
        return new Weapon();  // Nome, danno, durata
    }
    else if (type == "Block") {
        return new Block();  // Nome di default, durezza 10
    } 
    else if (type == "OreBlock") {
        return new OreBlock();  // Nome, durezza, drop min/max
    } 
    else if (type == "LightBlock") {
        return new LightBlock();
    } 

    return nullptr;  // Tipo non riconosciuto
}
