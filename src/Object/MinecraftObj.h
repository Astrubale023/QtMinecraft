#ifndef I_OGGETTOMINECRAFT_H
#define I_OGGETTOMINECRAFT_H

#include <string>
#include "MinecraftObjVisitor.h"

class MinecraftObj {
public:
    MinecraftObj(const std::string& nome);
    virtual ~MinecraftObj() = default;

    std::string getNome() const;
    void setNome(const std::string& nuovoNome);

    virtual void accept(MinecraftObjVisitor& visitor) = 0;

private:
    std::string nome;
};

#endif // I_OGGETTOMINECRAFT_H