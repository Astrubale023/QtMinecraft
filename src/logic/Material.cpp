#include "Material.h"
#include "MinecraftObjVisitor.h"

//const Material Material::IRON("Iron", true, Rarity::COMMON);
//const Material Material::GOLD("Gold", true, Rarity::RARE);
//const Material Material::DIAMOND("Diamond", true, Rarity::EPIC);
//const Material Material::DEFAULT_MAT("Default", false, Rarity::COMMON);

Material::Material(const std::string& nome, const std::string& imageName, bool stackable, Rarity rarity) : Item(nome, imageName, stackable), rarity(rarity) {}

Material* Material::clone() {
    return new Material(*this);
}

Rarity Material::getRarity() const {
    return rarity;
}

void Material::setRarity(Rarity r) {
    rarity = r;
}
void Material::setRarity(int r) {
    setRarity(Material::intToRarity(r));
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
Rarity Material::stringToRarity(std::string s) {
    if (s == "Rare")
        return Rarity::RARE;
    if (s == "Epic")
        return Rarity::EPIC;
    if(s == "Leggendary")
        return Rarity::LEGENDARY;
    return Rarity::COMMON;
}
Rarity Material::intToRarity(int r) {
    switch (r) {
        case 0:
            return Rarity::COMMON;
        case 1:
            return Rarity::RARE;
        case 2:
            return Rarity::EPIC;
        case 3:
            return Rarity::LEGENDARY;
        default:
            return Rarity::COMMON;
    }
}

void Material::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}
