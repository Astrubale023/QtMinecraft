#include "OreBlock.h"
#include "Material.h"
#include "MinecraftObjVisitor.h"

OreBlock::OreBlock(const std::string& nome, const std::string& imageName, const int& hardness, const int& minDrop, const int& maxDrop, Material* material)
    : Block(nome, imageName, hardness), minDrop(minDrop), maxDrop(maxDrop), material(material) {}

OreBlock* OreBlock::clone() const {
    return new OreBlock(*this);
}

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

void OreBlock::setMaxDrop(const int& newMaxDrop) {
    maxDrop = newMaxDrop;
}

void OreBlock::setMinDrop(const int& newMinDrop) {
    minDrop = newMinDrop;
}

void OreBlock::accept(MinecraftObjVisitor& visitor) const {
    visitor.visit(*this);
}