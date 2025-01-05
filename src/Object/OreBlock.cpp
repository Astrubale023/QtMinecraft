#include "OreBlock.h"

OreBlock::OreBlock(const std::string& nome, int hardness, int minDrop, int maxDrop, Material* material)
    : Block(nome, hardness), minDrop(minDrop), maxDrop(maxDrop), material(material) {}

Material* OreBlock::getMaterial() const {
    return material;
}

int OreBlock::getMaxDrop() const {
    return maxDrop;
}

int OreBlock::getMinDrop() const {
    return minDrop;
}

void OreBlock::setMaterial(Material* newMaterial) {
    material = newMaterial;
}

void OreBlock::setMaxDrop(int newMaxDrop) {
    maxDrop = newMaxDrop;
}

void OreBlock::setMinDrop(int newMinDrop) {
    minDrop = newMinDrop;
}

void OreBlock::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}