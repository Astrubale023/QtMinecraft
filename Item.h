#ifndef ITEM_H
#define ITEM_H

#include "MinecraftObj.h"
class MinecraftObjVisitor;

class Item : public MinecraftObj {
private:
    bool stackable;

public:
    Item(const std::string& nome = "", const std::string& imageName = "default.png", bool stackable = false);
    ~Item() override = default;

    Item* clone() override;

    // Getter
    bool isStackable() const;

    // Setter
    void setStackable(bool newStackable);
    
    void accept(MinecraftObjVisitor& visitor) override;
};

#endif // ITEM_H
