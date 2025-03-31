#ifndef XMLVISITOR_H
#define XMLVISITOR_H

#include <QDomDocument>
#include "MinecraftObjVisitor.h"

class XmlVisitor : public MinecraftObjVisitor {
private:
    QDomElement xmlElement;

public:
    QDomElement getXmlElement();

    void visit(const Item& item) override;
    void visit(const Weapon& weapon) override;
    void visit(const Material& material) override;
    void visit(const Block& block) override;
    void visit(const OreBlock& oreBlock) override;
    void visit(const LightBlock& lightBlock) override;
};

#endif // XMLVISITOR_H
