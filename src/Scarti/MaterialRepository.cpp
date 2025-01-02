#include "MaterialRepository.h"

MaterialRepository::~MaterialRepository() {
    qDeleteAll(materials);
    materials.clear();
}

Material* MaterialRepository::getMaterial(const QString& name) const {
    return materials.value(name, nullptr);
}

void MaterialRepository::addMaterial(const Material& material) {
    if (!contains(QString::fromStdString(material.getNome()))) {
        materials.insert(QString::fromStdString(material.getNome()), new Material(material));
    }
}

void MaterialRepository::updateMaterial(const QString& name, const Material& newMaterial) {
    if (contains(name)) {
        delete materials[name];
        materials[name] = new Material(newMaterial);
    }
}

void MaterialRepository::removeMaterial(const QString& name) {
    if (contains(name)) {
        delete materials.take(name);
    }
}

bool MaterialRepository::contains(const QString& name) const {
    return materials.contains(name);
}

const QMap<QString, Material*>& MaterialRepository::getAllMaterials() const {
    return materials;
}
