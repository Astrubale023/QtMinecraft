#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Material.h"
class MinecraftObjVisitor;

class Weapon : public Item {
private:
    int damage;
    Material* material;

public:
    Weapon(const std::string& nome = "", const std::string& imageName = "default.png", const bool& stackable=false, const int& damage = 0, Material* material = nullptr);
    ~Weapon() override = default;

    Weapon* clone() const override;

    int getDamage() const;
    Material* getMaterial() const;

    void setDamage(int damage);
    void setMaterial(Material* newMaterial);
    
    void accept(MinecraftObjVisitor& visitor) const override;
};
#endif // WEAPON_H
