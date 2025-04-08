#include "LightBlock.h"
#include "MinecraftObjVisitor.h"

LightBlock::LightBlock(const std::string& nome, const std::string& imageName, const int& hardness, const LightColor& lightColor, const float& brightness)
    : Block(nome, imageName, hardness), lightColor(lightColor), brightness(brightness) {}

LightBlock* LightBlock::clone() const {
    return new LightBlock(*this);
}

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

std::string LightBlock::colorToString(const LightColor& lightColor) {
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
LightColor LightBlock::intToColor(const int& r) {
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

void LightBlock::accept(MinecraftObjVisitor& visitor) const {
    visitor.visit(*this);
}
