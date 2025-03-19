#include "ObjectFactory.h"
#include "Item.h"
#include "Block.h"
#include "OreBlock.h"
#include "LightBlock.h"
#include "Weapon.h"

MinecraftObj* ObjectFactory::createTemporaryObject(const QString& type) {
    if (type == "Item") {
        return new Item();  // Nome di default, non impilabile
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
    else if (type == "Weapon") {
        return new Weapon();  // Nome, danno, durata
    }

    return nullptr;  // Tipo non riconosciuto
}
