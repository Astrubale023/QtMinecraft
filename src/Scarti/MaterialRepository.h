#ifndef MATERIALREPOSITORY_H
#define MATERIALREPOSITORY_H

#include <QMap>
#include <QString>
#include "Material.h"

class MaterialRepository {
public:
    static MaterialRepository& instance() {
        static MaterialRepository repo;
        return repo;
    }

    Material* getMaterial(const QString& name) const;
    void addMaterial(const Material& material);
    void updateMaterial(const QString& name, const Material& newMaterial);
    void removeMaterial(const QString& name);
    bool contains(const QString& name) const;

    const QMap<QString, Material*>& getAllMaterials() const;

private:
    QMap<QString, Material*> materials;

    MaterialRepository() = default;
    ~MaterialRepository();
    MaterialRepository(const MaterialRepository&) = delete;
    MaterialRepository& operator=(const MaterialRepository&) = delete;
};

#endif // MATERIALREPOSITORY_H
