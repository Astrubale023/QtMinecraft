#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Material.h"

class Weapon : public Item {
private:
    int damage;
    Material material;

public:
    Weapon(const std::string& nome, bool stackable, int damage, const Material& material);
    ~Weapon() override = default;

    // Getter
    int getDamage() const;
    Material getMaterial() const;

    // Setter
    void setDamage(int damage);
    void setMaterial(const Material& newMaterial);
    
    void accept(MinecraftObjVisitor& visitor) override;
};
#endif // WEAPON_H
