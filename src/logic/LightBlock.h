#ifndef LIGHTBLOCK_H
#define LIGHTBLOCK_H

#include "Block.h"
class MinecraftObjVisitor;

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

public: //GREEN solo perchè è l'unico colore non primario tra i 4
    LightBlock(const std::string& nome = "", const std::string& imageName = "default.png", const int& hardness = 0, const LightColor& lightColor = LightColor::GREEN, const float& brightness = 0);
    ~LightBlock() override = default;

    LightBlock* clone() const override;

    // Getter
    LightColor getLightColor() const;
    float getBrightness() const;

    // Setter
    void setLightColor(LightColor newLightColor);
    void setBrightness(float newBrightness);

    // Funzione per ottenere la rarità come stringa
    static std::string colorToString(const LightColor& lightColor);
    static LightColor stringToColor(const std::string& s);
    static LightColor intToColor(const int& i);
    
    void accept(MinecraftObjVisitor& visitor) const override;
};

#endif // LIGHTBLOCK_H
