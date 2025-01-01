#include "OreBlock.h"

OreBlock::OreBlock(const std::string& nome, float hardness, const Material& material, int minDrop, int maxDrop)
    : Block(nome, hardness), material(material), minDrop(minDrop), maxDrop(maxDrop) {}

Material OreBlock::getMaterial() const {
    return material;
}

int OreBlock::getMaxDrop() const {
    return maxDrop;
}

int OreBlock::getMinDrop() const {
    return minDrop;
}

void OreBlock::setMaterial(const Material& newMaterial) {
    material = newMaterial;
}

void OreBlock::setMaxDrop(int newMaxDrop) {
    maxDrop = newMaxDrop;
}

void OreBlock::setMinDrop(int newMinDrop) {
    minDrop = newMinDrop;
}
