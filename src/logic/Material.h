#ifndef MATERIAL_H
#define MATERIAL_H

#include "Item.h"
class MinecraftObjVisitor;

enum class Rarity {
    COMMON,
    RARE,
    EPIC,
    LEGENDARY
};

class Material : public Item {
private:
    Rarity rarity;

public:
    static const Material DEFAULT_MAT;

    explicit Material(const std::string& nome = "", const std::string& imageName = "default.png", const bool& stackable=false, const Rarity& rarity=Rarity::COMMON);
    ~Material() override = default;

    Material* clone() const override;

    Rarity getRarity() const;
    void setRarity(Rarity r);
    void setRarity(int r);

    static std::string rarityToString(const Rarity& rarita);
    static Rarity stringToRarity(const std::string& s);
    static Rarity intToRarity(const int& r);    // Come per lightblock probabilmente è evitabile
    
    void accept(MinecraftObjVisitor& visitor) const override;
};

#endif // MATERIAL_H
