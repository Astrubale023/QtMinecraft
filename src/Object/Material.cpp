#include "Material.h"

const Material Material::IRON("Iron", true, Rarity::COMMON);
const Material Material::GOLD("Gold", true, Rarity::RARE);
const Material Material::DIAMOND("Diamond", true, Rarity::EPIC);

Material::Material(const std::string& nome, bool stackable, Rarity rarity) : Item(nome, stackable), rarity(rarity) {}

Rarity Material::getRarita() const {
    return rarity;
}

std::string Material::getRaritaString() const {
    return rarityToString(rarity);
}

std::string Material::rarityToString(Rarity rarity) {
    switch (rarity) {
        case Rarity::COMMON:
            return "Common";
        case Rarity::RARE:
            return "Rare";
        case Rarity::EPIC:
            return "Epic";
        case Rarity::LEGENDARY:
            return "Leggendary";
        default:
            return "Sconosciuto";
    }
}

void Material::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}