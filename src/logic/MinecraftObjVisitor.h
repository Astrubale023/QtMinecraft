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

    virtual void visit(const Item& item) = 0;
    virtual void visit(const Material& material) = 0;
    virtual void visit(const Weapon& weapon) = 0;
    virtual void visit(const Block& block) = 0;
    virtual void visit(const OreBlock& oreBlock) = 0;
    virtual void visit(const LightBlock& lightBlock) = 0;
};

#endif // MINECRAFTOBJVISITOR_H
