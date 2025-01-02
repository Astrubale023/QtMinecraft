#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Material.h"
#include <string>

class Weapon : public Item {
private:
    int damage;
    Material* material;

public:
    Weapon(const std::string& nome, bool stackable, int damage, Material* material);
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
