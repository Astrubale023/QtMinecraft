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
    OreBlock(const std::string& nome = "", const std::string& imageName = "default.png", const int& hardness = 0, const int& minDrop = 0, const int& maxDrop = 0, Material* material = nullptr);
    ~OreBlock() override = default;

    OreBlock* clone() const override;

    // Getter
    Material* getMaterial() const;
    int getMaxDrop() const;
    int getMinDrop() const;

    // Setter
    void setMaterial(Material* newMaterial);
    void setMaxDrop(const int& newMaxDrop);
    void setMinDrop(const int& newMinDrop);
    
    void accept(MinecraftObjVisitor& visitor) const override;
};

#endif // OREBLOCK_H
