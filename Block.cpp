#include "Block.h"
#include "MinecraftObjVisitor.h"
#include <stdexcept> // Per std::invalid_argument

Block::Block(const std::string& nome, int hardness)
    : MinecraftObj(nome), hardness(hardness) {
    if (hardness <= 0) {
        throw std::invalid_argument("La durezza deve essere maggiore di zero.");
    }
}

// Getter
int Block::getHardness() const {
    return hardness;
}

// Setter
void Block::setHardness(int newHardness) {
    if (newHardness <= 0) {
        throw std::invalid_argument("La durezza deve essere maggiore di zero.");
    }
    hardness = newHardness;
}

void Block::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}
