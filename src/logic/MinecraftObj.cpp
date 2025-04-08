#include "MinecraftObj.h"
#include <stdexcept>

// Costruttore
MinecraftObj::MinecraftObj(const std::string& nome, const std::string& imageName)
    : nome(nome), imageName(imageName) {} // tolto controllo per stringa vuota

// Getter per nome
std::string MinecraftObj::getNome() const {
    return nome;
}

// Setter per nome
void MinecraftObj::setNome(const std::string& nuovoNome) {
    // if (nuovoNome.empty()) { throw std::invalid_argument("Il nome non può essere vuoto."); }
    nome = nuovoNome;
}

// Getter per img
std::string MinecraftObj::getImage() const {
    return imageName;
}

// Setter per img
void MinecraftObj::setImage(const std::string& newImage) {
    if (newImage.empty()) {
        imageName = "default.png";
    }
    else {
        imageName = newImage;
    }
}