#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Material.h"
class MinecraftObjVisitor;

class Weapon : public Item {
private:
    int damage;
    Material* material;

public://qui const_cast perchè dereferenziondo DEFAULT_MAT mi da un puntatore a const e a noi conveniva così
    Weapon(const std::string& nome = "", const std::string& imageName = "default.png", bool stackable=false, int damage = 0, Material* material = nullptr);
    ~Weapon() override = default;

    Weapon* clone() override;

    // Getter
    int getDamage() const;
    Material* getMaterial() const;

    // Setter
    void setDamage(int damage);
    void setMaterial(Material* newMaterial);
    
    void accept(MinecraftObjVisitor& visitor) override;
};
#endif // WEAPON_H
