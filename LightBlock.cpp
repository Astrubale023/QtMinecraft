#include "LightBlock.h"
#include "MinecraftObjVisitor.h"

LightBlock::LightBlock(const std::string& nome, int hardness, LightColor lightColor, float brightness)
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

std::string LightBlock::colorToString(LightColor lightColor) {
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

LightColor LightBlock::stringToColor(const std::string& s) {
    if(s == "Red")
        return LightColor::RED;
    if(s == "Blue")
        return LightColor::BLUE;
    if(s == "Yellow")
        return LightColor::YELLOW;
    return LightColor::GREEN;
}
LightColor LightBlock::intToColor(int r) {
    switch (r) {
        case 0:
            return LightColor::RED;
        case 1:
            return LightColor::BLUE;
        case 2:
            return LightColor::YELLOW;
        case 3:
            return LightColor::GREEN;
        default:
            return LightColor::GREEN;
    }
}

void LightBlock::accept(MinecraftObjVisitor& visitor) {
    visitor.visit(*this);
}
