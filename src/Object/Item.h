#ifndef ITEM_H
#define ITEM_H

#include "MinecraftObj.h"

class Item : public MinecraftObj {
private:
    bool stackable;

public:
    Item(const std::string& nome = "", bool stackable = false);
    ~Item() override = default;

    // Getter
    bool isStackable() const;

    // Setter
    void setStackable(bool newStackable);
    
    void accept(MinecraftObjVisitor& visitor) override;
};

#endif // ITEM_H
