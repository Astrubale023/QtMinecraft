#include "LightBlock.h"

LightBlock::LightBlock(const std::string& nome, float hardness, LightColor lightColor, float brightness)
    : Block(nome, hardness), lightColor(lightColor), brightness(brightness) {}

LightColor LightBlock::getLightColor() const {
    return lightColor;
}

float LightBlock::getBrightness() const {
    return brightness;
}

void LightBlock::setLightColor(LightColor newLightColor) {
    lightColor = newLightColor;
}

void LightBlock::setBrightness(float newBrightness) {
    brightness = newBrightness;
}
