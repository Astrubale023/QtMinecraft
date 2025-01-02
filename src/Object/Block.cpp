#include "Block.h"
#include <stdexcept> // Per std::invalid_argument

Block::Block(const std::string& nome, float hardness)
    : MinecraftObj(nome), hardness(hardness) {
    if (hardness <= 0) {
        throw std::invalid_argument("La durezza deve essere maggiore di zero.");
    }
}

// Getter
float Block::getHardness() const {
    return hardness;
}

// Setter
void Block::setHardness(float newHardness) {
    if (newHardness <= 0) {
        throw std::invalid_argument("La durezza deve essere maggiore di zero.");
    }
    hardness = newHardness;
}

void Block::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}