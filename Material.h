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
    //static const Material IRON;
    //static const Material GOLD;
    //static const Material DIAMOND;
    static const Material DEFAULT_MAT;

    explicit Material(const std::string& nome = "", bool stackable=false, Rarity rarity=Rarity::COMMON);
    ~Material() override = default;

    Rarity getRarity() const;
    void setRarity(Rarity r);
    void setRarity(int r);

    // Funzione per ottenere la rarità come stringa
    static std::string rarityToString(Rarity rarita);
    static Rarity stringToRarity(std::string s);
    static Rarity intToRarity(int r);
    
    void accept(MinecraftObjVisitor& visitor) override;
};

#endif // MATERIAL_H
