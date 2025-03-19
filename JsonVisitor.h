#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include "MinecraftObjVisitor.h"
#include <QJsonObject>

class JsonVisitor : public MinecraftObjVisitor {
private:
    QJsonObject jsonobject;

public:
    QJsonObject getJsonObject();

    void visit(const Item& item) override;
    void visit(const Weapon& weapon) override;
    void visit(const Material& material) override;

    void visit(const Block& block) override;
    void visit(const OreBlock& oreBlock) override;
    void visit(const LightBlock& lightBlock) override;
};

#endif // JSONVISITOR_H
