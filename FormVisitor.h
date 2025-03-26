#ifndef FORMVISITOR_H
#define FORMVISITOR_H

#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QMap>
#include <QLabel>
#include "MinecraftObjVisitor.h"

class LibraryManager;
class MinecraftObj;

class FormVisitor : public QWidget, public MinecraftObjVisitor {
    Q_OBJECT

public:
    enum class FormMode { ADD, EDIT, DETAIL };

    explicit FormVisitor(FormMode mode, LibraryManager* libraryManager, QWidget *parent = nullptr);
    void buildForm(MinecraftObj *obj);
    QWidget* getFormWidget() { return this; }

    void visit(const Item &item) override;
    void visit(const Block &block) override;
    void visit(const Material &material) override;
    void visit(const Weapon &weapon) override;
    void visit(const LightBlock &lightBlock) override;
    void visit(const OreBlock &oreBlock) override;

signals:
    void objectSaved();
    void objectAdded();
    void cancelled();

private slots:
    void onSave();
    void onCancel();

private:
    FormMode mode;
    LibraryManager* libraryManager;
    MinecraftObj* currentObj;
    QFormLayout *formLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QMap<QString, QWidget*> fields;

    void visit(const MinecraftObj &obj);

    void createLineEdit(const QString& label, const QString& key, const QString& value);
    void createComboBox(const QString& label, const QString& key, const QStringList& options, int currentIndex);
    void createSpinBox(const QString& label, const QString& key, int min, int max, int value);
    void selectImage(QLabel* previewLabel);
    
    QString getLineEditValue(const QString& key) const;
    int getComboBoxValue(const QString& key) const;
    int getSpinBoxValue(const QString& key) const;
    
    void setReadOnly();
};

#endif // FORMVISITOR_H
