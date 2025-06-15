#ifndef BLOCK_H
#define BLOCK_H

#include "MinecraftObj.h"
class MinecraftObjVisitor;

class Block : public MinecraftObj {
private:
    int hardness;

public:
    Block(const std::string& nome = "", const std::string& imageName = "default.png", const int hardness = 0);
    ~Block() override = default;

    Block* clone() const override;

    int getHardness() const;

    void setHardness(int newHardness);
    
    void accept(MinecraftObjVisitor& visitor) const override;
};

#endif // BLOCK_H
