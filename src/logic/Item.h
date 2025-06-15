#ifndef ITEM_H
#define ITEM_H

#include "MinecraftObj.h"
class MinecraftObjVisitor;

class Item : public MinecraftObj {
private:
    bool stackable;

public:
    Item(const std::string& nome = "", const std::string& imageName = "default.png", const bool& stackable = false);
    ~Item() override = default;

    Item* clone() const override;

    bool isStackable() const;

    void setStackable(bool newStackable);
    
    void accept(MinecraftObjVisitor& visitor) const override;
};

#endif // ITEM_H
