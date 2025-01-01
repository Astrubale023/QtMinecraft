#ifndef OREBLOCK_H
#define OREBLOCK_H

#include "Block.h"
#include "Material.h"

class OreBlock : public Block {
private:
    Material material;
    int maxDrop;
    int minDrop;

public:
    OreBlock(const std::string& nome, float hardness, const Material& material, int minDrop, int maxDrop);
    ~OreBlock() override = default;

    // Getter
    Material getMaterial() const;
    int getMaxDrop() const;
    int getMinDrop() const;

    // Setter
    void setMaterial(const Material& newMaterial);
    void setMaxDrop(int newMaxDrop);
    void setMinDrop(int newMinDrop);
};

#endif // OREBLOCK_H
