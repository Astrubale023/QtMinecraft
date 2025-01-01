#include "MinecraftObj.h"
#include <stdexcept>

// Costruttore
MinecraftObj::MinecraftObj(const std::string& nome)
    : nome(nome) {
        if (nome.empty()) {
            throw std::invalid_argument("Il nome non può essere vuoto.");
        }
    }

// Getter per nome
std::string MinecraftObj::getNome() const {
    return nome;
}

// Setter per nome
void MinecraftObj::setNome(const std::string& nuovoNome) {
    if (nuovoNome.empty()) {
        throw std::invalid_argument("Il nome non può essere vuoto.");
    }
    nome = nuovoNome;
}
