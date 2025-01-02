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

public:
    static const Material IRON;
    static const Material GOLD;
    static const Material DIAMOND;

    explicit Material(const std::string& nome, bool stackable, Rarity rarity);
    ~Material() override = default;

    Rarity getRarita() const;
    std::string getRaritaString() const;
    
    void accept(MinecraftObjVisitor& visitor) override;
};

#endif // MATERIAL_H
