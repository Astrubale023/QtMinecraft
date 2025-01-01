#ifndef I_OGGETTOMINECRAFT_H
#define I_OGGETTOMINECRAFT_H

#include <string>

class MinecraftObj {
public:
    MinecraftObj(const std::string& nome);
    virtual ~MinecraftObj() = default;

    std::string getNome() const;
    void setNome(const std::string& nuovoNome);

private:
    std::string nome;
};

#endif // I_OGGETTOMINECRAFT_H