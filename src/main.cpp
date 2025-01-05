#include <QCoreApplication>
#include <iostream>
#include "MinecraftObj.h"
#include "Item.h"
#include "Block.h"
#include "Material.h"
#include "Weapon.h"
#include "JsonHandler.h"

void displayMenu() {
    std::cout << "\n--- Menu ---\n";
    std::cout << "1. Aggiungi un oggetto\n";
    std::cout << "2. Modifica un oggetto\n";
    std::cout << "3. Elimina un oggetto\n";
    std::cout << "4. Visualizza tutti gli oggetti\n";
    std::cout << "5. Salva su JSON\n";
    std::cout << "6. Carica da JSON\n";
    std::cout << "7. Esci\n";
    std::cout << "Scegli un'opzione: ";
}

void displayObjects(const QList<MinecraftObj*>& objects) {
    std::cout << "\n--- Oggetti nella lista ---\n";
    for (int i = 0; i < objects.size(); ++i) {
        std::cout << i + 1 << ". " << objects[i]->getNome() << "\n";
    }
    std::cout << "--------------------------\n";
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QList<MinecraftObj*> objects;

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "\n--- Aggiungi un oggetto ---\n";
            std::cout << "1. Item\n2. Block\n3. Material\n4. Weapon\nScegli il tipo di oggetto: ";
            int type;
            std::cin >> type;

            std::string name;
            std::cout << "Inserisci il nome dell'oggetto: ";
            std::cin >> name;

            if (type == 1) {
                bool stackable;
                std::cout << "E' impilabile (0/1)? ";
                std::cin >> stackable;
                objects.append(new Item(name, stackable));
            } else if (type == 2) {
                float hardness;
                std::cout << "Inserisci la durezza: ";
                std::cin >> hardness;
                objects.append(new Block(name, hardness));
            } else if (type == 3) {
                int rarityInt;
                std::cout << "Inserisci rarità (0=COMMON, 1=RARE, 2=EPIC, 3=LEGENDARY): ";
                std::cin >> rarityInt;
                bool stackable;
                std::cout << "E' impilabile (0/1)? ";
                std::cin >> stackable;
                objects.append(new Material(name, stackable, static_cast<Rarity>(rarityInt)));
            } else if (type == 4) {
                int damage;
                std::cout << "Inserisci il danno: ";
                std::cin >> damage;
                std::string materialName;
                std::cout << "Inserisci il nome del materiale (deve essere già esistente): ";
                std::cin >> materialName;

                Material* material = nullptr;
                for (MinecraftObj* obj : objects) {
                    Material* mat = dynamic_cast<Material*>(obj);
                    if (mat && mat->getNome() == materialName) {
                        material = mat;
                        break;
                    }
                }

                if (material) {
                    objects.append(new Weapon(name, true, damage, material));
                } else {
                    std::cout << "Materiale non trovato!\n";
                }
            }
        } else if (choice == 2) {
            displayObjects(objects);
            int index;
            std::cout << "Inserisci l'indice dell'oggetto da modificare: ";
            std::cin >> index;

            if (index < 1 || index > objects.size()) {
                std::cout << "Indice non valido!\n";
                continue;
            }

            MinecraftObj* obj = objects[index - 1];
            if (Item* item = dynamic_cast<Item*>(obj)) {
                bool stackable;
                std::cout << "E' impilabile (0/1)? ";
                std::cin >> stackable;
                item->setStackable(stackable);
            } else if (Block* block = dynamic_cast<Block*>(obj)) {
                float hardness;
                std::cout << "Inserisci la nuova durezza: ";
                std::cin >> hardness;
                block->setHardness(hardness);
            } else if (Weapon* weapon = dynamic_cast<Weapon*>(obj)) {
                int damage;
                std::cout << "Inserisci il nuovo danno: ";
                std::cin >> damage;
                weapon->setDamage(damage);
            }
        } else if (choice == 3) {
            displayObjects(objects);
            int index;
            std::cout << "Inserisci l'indice dell'oggetto da eliminare: ";
            std::cin >> index;

            if (index < 1 || index > objects.size()) {
                std::cout << "Indice non valido!\n";
                continue;
            }

            delete objects.takeAt(index - 1);
            std::cout << "Oggetto eliminato.\n";
        } else if (choice == 4) {
            displayObjects(objects);
        } else if (choice == 5) {
            std::cout << "Inserisci il nome del file per il salvataggio: ";
            QString filename;
            std::cin >> filename;
            JsonHandler::saveObjectsToFile(filename, objects);
        } else if (choice == 6) {
            std::cout << "Inserisci il nome del file da cui caricare: ";
            QString filename;
            std::cin >> filename;
            JsonHandler::loadObjectsFromFile(filename, objects);
        } else if (choice == 7) {
            break;
        }
    }

    // Pulizia della memoria
    qDeleteAll(objects);
    return 0;
}
