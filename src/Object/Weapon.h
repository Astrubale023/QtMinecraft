#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Material.h"
#include <string>

class Weapon : public Item {
private:
    int damage;
    Material* material;

public://qui const_cast perchè dereferenziondo DEFAULT_MAT mi da un puntatore a const e a noi conveniva così
    Weapon(const std::string& nome = "", bool stackable=false, int damage = 0, Material* material = const_cast<Material*>(&Material::DEFAULT_MAT));
    ~Weapon() override = default;

    // Getter
    int getDamage() const;
    Material* getMaterial() const;

    // Setter
    void setDamage(int damage);
    void setMaterial(Material* newMaterial);
    
    void accept(MinecraftObjVisitor& visitor) override;
};
#endif // WEAPON_H
