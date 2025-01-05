#ifndef MINECRAFTOBJVISITOR_H
#define MINECRAFTOBJVISITOR_H

#include "Item.h"
#include "Material.h"
#include "Weapon.h"
#include "Block.h"
#include "OreBlock.h"
#include "LightBlock.h"

class MinecraftObjVisitor {
public:
    virtual ~MinecraftObjVisitor() = default;

    virtual void visit(const Item& item) = 0;
    virtual void visit(const Material& material) = 0;
    virtual void visit(const Weapon& weapon) = 0;
    virtual void visit(const Block& block) = 0;
    virtual void visit(const OreBlock& oreBlock) = 0;
    virtual void visit(const LightBlock& lightBlock) = 0;
};

#endif // MINECRAFTOBJVISITOR_H
