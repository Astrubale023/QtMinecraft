#ifndef I_OGGETTOMINECRAFT_H
#define I_OGGETTOMINECRAFT_H

#include <string>
class MinecraftObjVisitor;

class MinecraftObj {
public:
    MinecraftObj(const std::string& nome, const std::string& imageName);
    virtual ~MinecraftObj() = default;
    virtual MinecraftObj* clone() const = 0;

    std::string getNome() const;
    void setNome(const std::string& nuovoNome);

    std::string getImage() const;
    void setImage(const std::string& newImage);

    virtual void accept(MinecraftObjVisitor& visitor) const = 0;

private:
    std::string nome;
    std::string imageName;
};

#endif // I_OGGETTOMINECRAFT_H
