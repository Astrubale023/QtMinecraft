#ifndef BLOCK_H
#define BLOCK_H

#include "MinecraftObj.h"

class Block : public MinecraftObj {
private:
    int hardness;

public:
    Block(const std::string& nome = "", int hardness = 0);
    ~Block() override = default;

    // Getter
    int getHardness() const;

    // Setter
    void setHardness(int newHardness);
    
    void accept(MinecraftObjVisitor& visitor) override;
};

#endif // BLOCK_H
