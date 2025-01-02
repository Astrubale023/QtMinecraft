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

std::string colorToString(LightColor lightColor) {
    switch (lightColor) {
        case LightColor::RED:
            return "Red";
        case LightColor::BLUE:
            return "Blue";
        case LightColor::YELLOW:
            return "Yellow";
        case LightColor::GREEN:
            return "Green";
        default:
            return "Sconosciuto";
    }
}

void LightBlock::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}