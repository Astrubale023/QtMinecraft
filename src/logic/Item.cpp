#include "Item.h"
#include "MinecraftObjVisitor.h"
#include <stdexcept> // Per std::invalid_argument

Item::Item(const std::string& nome, const std::string& imageName, const bool& stackable)
    : MinecraftObj(nome, imageName),stackable(stackable) {}

Item* Item::clone() const {
    return new Item(*this);
}

// Getter
bool Item::isStackable() const {
    return stackable;
}

// Setter
void Item::setStackable(bool newStackable) {
    stackable = newStackable;
}

void Item::accept(MinecraftObjVisitor& visitor) const {
    visitor.visit(*this);
}
