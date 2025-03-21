#include "Weapon.h"
#include "Material.h"
#include "MinecraftObjVisitor.h"

Weapon::Weapon(const std::string& nome, bool stackable, int damage, Material* material)
    : Item(nome, stackable), damage(damage), material(material) {}

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

void Weapon::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}
