#ifndef BLOCK_H
#define BLOCK_H

#include "MinecraftObj.h"

class Block : public MinecraftObj {
private:
    float hardness;

public:
    Block(const std::string& nome, float hardness);
    ~Block() override = default;

    // Getter
    float getHardness() const;

    // Setter
    void setHardness(float newHardness);
};

#endif // BLOCK_H
