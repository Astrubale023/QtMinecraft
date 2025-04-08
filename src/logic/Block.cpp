#include "Block.h"
#include "MinecraftObjVisitor.h"
#include <stdexcept> // Per std::invalid_argument

Block::Block(const std::string& nome, const std::string& imageName, int hardness)
    : MinecraftObj(nome, imageName), hardness(hardness) {
    if (hardness < 0) {
        throw std::invalid_argument("La durezza deve essere maggiore di zero.");
    }
}

Block* Block::clone() {
    return new Block(*this);
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
