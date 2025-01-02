#ifndef MINECRAFTOBJVISITOR_H
#define MINECRAFTOBJVISITOR_H

class Item;
class Material;
class Weapon;
class Block;
class OreBlock;
class LightBlock;

class MinecraftObjVisitor {
public:
    virtual ~MinecraftObjVisitor() = default;

    virtual void visit(Item& item) = 0;
    virtual void visit(Material& material) = 0;
    virtual void visit(Weapon& weapon) = 0;
    virtual void visit(Block& block) = 0;
    virtual void visit(OreBlock& oreBlock) = 0;
    virtual void visit(LightBlock& lightBlock) = 0;
};

#endif // MINECRAFTOBJVISITOR_H
