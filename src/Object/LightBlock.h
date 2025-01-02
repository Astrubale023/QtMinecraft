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

public:
    LightBlock(const std::string& nome, float hardness, LightColor lightColor, float brightness);
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
