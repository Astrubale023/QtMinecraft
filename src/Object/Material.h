#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "Item.h"

enum class Rarity {
    COMMON,
    RARE,
    EPIC,
    LEGENDARY
};

class Material : public Item {
private:
    Rarity rarity;
    
    // Funzione per ottenere la rarità come stringa
    static std::string rarityToString(Rarity rarita);
    static Rarity stringToRarity(string s);

public:
    //static const Material IRON;
    //static const Material GOLD;
    //static const Material DIAMOND;
    static const Material DEFAULT_MAT;

    explicit Material(const std::string& nome = "", bool stackable=false, Rarity rarity=Rarity::COMMON);
    ~Material() override = default;

    Rarity getRarity() const;
    
    void accept(MinecraftObjVisitor& visitor) override;
};

#endif // MATERIAL_H
