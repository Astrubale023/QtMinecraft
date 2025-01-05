#include "Material.h"

//const Material Material::IRON("Iron", true, Rarity::COMMON);
//const Material Material::GOLD("Gold", true, Rarity::RARE);
//const Material Material::DIAMOND("Diamond", true, Rarity::EPIC);
const Material Material::DEFAULT_MAT("Default", false, Rarity::COMMON);

Material::Material(const std::string& nome, bool stackable, Rarity rarity) : Item(nome, stackable), rarity(rarity) {}

Rarity Material::getRarity() const {
    return rarity;
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
Rarity Material::stringToRarity(string s) {

    if (s == "Rare")
        return Rarity::RARE;
    if (s == "Epic")
        return Rarity::EPIC;
    if(s == "Leggendary")
        return Rarity::LEGENDARY;
    return Rarity::COMMON;
}

void Material::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}