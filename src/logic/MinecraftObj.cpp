#include "MinecraftObj.h"
#include <stdexcept>

// Costruttore
MinecraftObj::MinecraftObj(const std::string& nome, const std::string& imageName)
    : nome(nome), imageName(imageName) {}

std::string MinecraftObj::getNome() const {
    return nome;
}

void MinecraftObj::setNome(const std::string& nuovoNome) {
    nome = nuovoNome;
}

std::string MinecraftObj::getImage() const {
    return imageName;
}

void MinecraftObj::setImage(const std::string& newImage) {
    if (newImage.empty()) {
        imageName = "default.png";
    }
    else {
        imageName = newImage;
    }
}