#include "Weapon.h"
#include "Material.h"
#include "MinecraftObjVisitor.h"

Weapon::Weapon(const std::string& nome, const std::string& imageName, const bool& stackable, const int& damage, Material* material)
    : Item(nome, imageName, stackable), damage(damage), material(material) {}

Weapon* Weapon::clone() const {
    return new Weapon(*this);
}

int Weapon::getDamage() const {
    return damage;
}

Material* Weapon::getMaterial() const {
    return material;
}

void Weapon::setDamage(int newDamage) {
    damage = newDamage;
}

void Weapon::setMaterial(Material* newMaterial) {
    material = newMaterial;
}

void Weapon::accept(MinecraftObjVisitor& visitor) const {
    visitor.visit(*this);
}
