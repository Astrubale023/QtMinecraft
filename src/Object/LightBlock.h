#ifndef LIGHTBLOCK_H
#define LIGHTBLOCK_H

#include "Block.h"

enum class LightColor {
    RED,
    BLUE,
    YELLOW,
    GREEN
};

class LightBlock : public Block {
private:
    LightColor lightColor;
    float brightness;

    // Funzione per ottenere la rarità come stringa
    static std::string colorToString(LightColor lightColor);
    static LightColor stringToColor(string s);

public: //GREEN solo perchè è l'unico colore non primario tra i 4
    LightBlock(const std::string& nome = "", int hardness = 0, LightColor lightColor = LightColor::GREEN, float brightness = 0);
    ~LightBlock() override = default;

    // Getter
    LightColor getLightColor() const;
    float getBrightness() const;

    // Setter
    void setLightColor(LightColor newLightColor);
    void setBrightness(float newBrightness);
    
    void accept(MinecraftObjVisitor& visitor) override;
};

#endif // LIGHTBLOCK_H
