#ifndef I_OGGETTOMINECRAFT_H
#define I_OGGETTOMINECRAFT_H

#include <string>
class MinecraftObjVisitor;

class MinecraftObj {
public:
    MinecraftObj(const std::string& nome);
    virtual ~MinecraftObj() = default;
    virtual MinecraftObj* clone() = 0;

    std::string getNome() const;
    void setNome(const std::string& nuovoNome);

    virtual void accept(MinecraftObjVisitor& visitor) = 0;

private:
    std::string nome;
};

#endif // I_OGGETTOMINECRAFT_H
