#ifndef OREBLOCK_H
#define OREBLOCK_H

#include "Block.h"
#include "Material.h"
class MinecraftObjVisitor;

class OreBlock : public Block {
private:
    int minDrop;
    int maxDrop;
    Material* material;

public:
    OreBlock(const std::string& nome = "", int hardness = 0, int minDrop = 0, int maxDrop = 0, Material* material = const_cast<Material *>(&Material::DEFAULT_MAT));
    ~OreBlock() override = default;

    // Getter
    Material* getMaterial() const;
    int getMaxDrop() const;
    int getMinDrop() const;

    // Setter
    void setMaterial(Material* newMaterial);
    void setMaxDrop(int newMaxDrop);
    void setMinDrop(int newMinDrop);
    
    void accept(MinecraftObjVisitor& visitor) override;
};

#endif // OREBLOCK_H
