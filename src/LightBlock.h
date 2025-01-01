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

public:
    LightBlock(const std::string& nome, float hardness, LightColor lightColor, float brightness);
    ~LightBlock() override = default;

    // Getter
    LightColor getLightColor()) const;
    float getBrightness() const;

    // Setter
    void setLightColor(LightColor newLightColor);
    void setBrightness(float newBrightness);
};

#endif // LIGHTBLOCK_H
