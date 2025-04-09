#include "FormVisitor.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QLabel>
#include <QFileDialog>
#include "../logic/MinecraftObj.h"
#include "../logic/Item.h"
#include "../logic/Weapon.h"
#include "../logic/Block.h"
#include "../logic/LightBlock.h"
#include "../logic/OreBlock.h"
#include "../logic/LibraryManager.h"

FormVisitor::FormVisitor(FormMode mode, LibraryManager* libraryManager, QWidget *parent)
    : QWidget(parent), mode(mode), libraryManager(libraryManager), currentObj(nullptr) {
    
    formLayout = new QFormLayout();
    saveButton = new QPushButton("Salva");
    cancelButton = new QPushButton("Annulla");

    cancelButton->setShortcut(QKeySequence("Ctrl+X"));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &FormVisitor::onSave);
    connect(cancelButton, &QPushButton::clicked, this, &FormVisitor::onCancel);

    if (mode == FormMode::DETAIL) {
        saveButton->setDisabled(true);
    }
}

void FormVisitor::buildForm(MinecraftObj *obj) {
    currentObj = obj;
    fields.clear();
    obj->accept(*this);

    if (mode == FormMode::DETAIL) {
        setReadOnly();
    }
}

void FormVisitor::visit(const MinecraftObj &obj) {
    createLineEdit("Nome:", "name", QString::fromStdString(obj.getNome()));

    // Pulsante per selezionare un'immagine
    QPushButton *selectImageButton = new QPushButton("Seleziona Icona");
    QLabel *imagePreview = new QLabel(this);
    imagePreview->setAlignment(Qt::AlignCenter);
    imagePreview->setFixedSize(100, 100); // Dimensione anteprima

    // Controlla se l'oggetto ha già un'icona salvata
    QString imagePath = QString::fromStdString("icons/"+obj.getImage());
    if (!imagePath.isEmpty() && QFile::exists(imagePath)) {
        qDebug() << "ora qui";
        imagePreview->setPixmap(QPixmap(imagePath).scaled(100, 100, Qt::KeepAspectRatio));
    }

    formLayout->addRow("Icona:", selectImageButton);
    formLayout->addRow(imagePreview);

    if (mode == FormMode::DETAIL) {
        selectImageButton->setDisabled(true);
    }

    // Collega il pulsante alla funzione di selezione dell'immagine
    connect(selectImageButton, &QPushButton::clicked, this, [this, imagePreview]() {
        selectImage(imagePreview);
    });

    // Salva l'anteprima nel dizionario dei campi
    fields["iconPreview"] = imagePreview;
}

void FormVisitor::visit(const Item &item) {
    visit(static_cast<const MinecraftObj&>(item));
    createComboBox("Impilabile:", "stackable", {"No", "Sì"}, item.isStackable() ? 1 : 0);
}

void FormVisitor::visit(const Block &block) {
    visit(static_cast<const MinecraftObj&>(block));
    createSpinBox("Durezza:", "hardness", 0, 100, block.getHardness());
}

void FormVisitor::visit(const Material &material) {
    visit(static_cast<const Item&>(material));
    createComboBox("Rarità:", "rarity", {"Comune", "Raro", "Epico", "Leggendario"}, static_cast<int>(material.getRarity()));
}

void FormVisitor::visit(const Weapon &weapon) {
    visit(static_cast<const Item&>(weapon));
    createSpinBox("Danno:", "damage", 0, 100, weapon.getDamage());

    QList<Material*> materials = libraryManager->getMaterials(); // Otteniamo la lista di materiali

    QStringList materialNames;
    materialNames.append("Nessun Materiale"); // Opzione per nessun materiale
    int selectedIndex = 0;

    for (int i = 0; i < materials.size(); ++i) {
        materialNames.append(QString::fromStdString(materials[i]->getNome()));
        if (materials[i] == weapon.getMaterial()) {
            selectedIndex = i + 1; // +1 perché "Nessun Materiale" è il primo elemento
        }
    }

    createComboBox("Materiale:", "material", materialNames, selectedIndex);
}

void FormVisitor::visit(const LightBlock &lightBlock) {
    visit(static_cast<const Block&>(lightBlock));
    createSpinBox("Luminosità:", "brightness", 0, 100, lightBlock.getBrightness());
}

void FormVisitor::visit(const OreBlock &oreBlock) {
    visit(static_cast<const Block&>(oreBlock));
    createSpinBox("Min Drop:", "minDrop", 0, 100, oreBlock.getMinDrop());
    createSpinBox("Max Drop:", "maxDrop", 0, 100, oreBlock.getMaxDrop());

    QList<Material*> materials = libraryManager->getMaterials(); // Otteniamo la lista di materiali

    QStringList materialNames;
    materialNames.append("Nessun Materiale"); // Opzione per nessun materiale
    int selectedIndex = 0;

    for (int i = 0; i < materials.size(); ++i) {
        materialNames.append(QString::fromStdString(materials[i]->getNome()));
        if (materials[i] == oreBlock.getMaterial()) {
            selectedIndex = i + 1; // +1 perché "Nessun Materiale" è il primo elemento
        }
    }

    createComboBox("Materiale:", "material", materialNames, selectedIndex);
}

void FormVisitor::onSave() {
    if (!currentObj || mode == FormMode::DETAIL) return;

    MinecraftObj* newObj = currentObj->clone();

    newObj->setNome(getLineEditValue("name").toStdString());

    // Controlla se è stata selezionata un'immagine
    auto it = fields.find("imagePath");
    if (it != fields.end()) {
        QLabel *imageLabel = dynamic_cast<QLabel*>(it.value());
        if (imageLabel) {
            QString imagePath = imageLabel->text();
            newObj->setImage(imagePath.toStdString()); // Salviamo il percorso nell'oggetto
        }
    }

    if (auto* item = dynamic_cast<Item*>(newObj)) {
        item->setStackable(getComboBoxValue("stackable"));
    }
    if (auto* block = dynamic_cast<Block*>(newObj)) {
        block->setHardness(getSpinBoxValue("hardness"));
    }
    if (auto* material = dynamic_cast<Material*>(newObj)) {
        material->setRarity(static_cast<Rarity>(getComboBoxValue("rarity")));
    }
    if (auto* weapon = dynamic_cast<Weapon*>(newObj)) {
        weapon->setDamage(getSpinBoxValue("damage"));

        QList<Material*> materials = libraryManager->getMaterials();
        int materialIndex = getComboBoxValue("material") - 1; // -1 perché il primo elemento è "Nessun Materiale"

        if (materialIndex >= 0 && materialIndex < materials.size()) {
            weapon->setMaterial(materials[materialIndex]);
        } else {
            weapon->setMaterial(nullptr); // Nessun materiale selezionato
        }
    }
    if (auto* lightBlock = dynamic_cast<LightBlock*>(newObj)) {
        lightBlock->setBrightness(getSpinBoxValue("brightness"));
    }
    if (auto* oreBlock = dynamic_cast<OreBlock*>(newObj)) {
        oreBlock->setMinDrop(getSpinBoxValue("minDrop"));
        oreBlock->setMaxDrop(getSpinBoxValue("maxDrop"));

        QList<Material*> materials = libraryManager->getMaterials();
        int materialIndex = getComboBoxValue("material") - 1; // -1 perché il primo elemento è "Nessun Materiale"

        if (materialIndex >= 0 && materialIndex < materials.size()) {
            oreBlock->setMaterial(materials[materialIndex]);
        } else {
            oreBlock->setMaterial(nullptr); // Nessun materiale selezionato
        }
    }

    if (mode == FormMode::ADD) {
        libraryManager->addObject(newObj);
        emit objectAdded();
    } else if (mode == FormMode::EDIT) {
        libraryManager->updateObject(currentObj, newObj);
        emit objectSaved();
    }

    close();
}

void FormVisitor::onCancel() {
    emit cancelled();
    close();
}

void FormVisitor::createLineEdit(const QString& label, const QString& key, const QString& value) {
    QLineEdit *field = new QLineEdit(value);
    formLayout->addRow(label, field);
    fields[key] = field;
}

void FormVisitor::createComboBox(const QString& label, const QString& key, const QStringList& options, const int& currentIndex) {
    QComboBox *field = new QComboBox();
    field->addItems(options);
    field->setCurrentIndex(currentIndex);
    formLayout->addRow(label, field);
    fields[key] = field;
}

void FormVisitor::createSpinBox(const QString& label, const QString& key, const int& min, const int& max, const int& value) {
    QSpinBox *field = new QSpinBox();
    field->setRange(min, max);
    field->setValue(value);
    formLayout->addRow(label, field);
    fields[key] = field;
}

void FormVisitor::setReadOnly() {
    for (auto field : fields) {
        if (auto* lineEdit = dynamic_cast<QLineEdit*>(field)) {
            lineEdit->setReadOnly(true);
        } else if (auto* comboBox = dynamic_cast<QComboBox*>(field)) {
            comboBox->setDisabled(true);
        } else if (auto* spinBox = dynamic_cast<QSpinBox*>(field)) {
            spinBox->setDisabled(true);
        }
    }
}

QString FormVisitor::getLineEditValue(const QString &field) const {
    auto it = fields.find(field);
    if (it != fields.end()) {
        QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(it.value());
        if (lineEdit) {
            return lineEdit->text();
        }
    }
    return "";
}

int FormVisitor::getSpinBoxValue(const QString &field) const {
    auto it = fields.find(field);
    if (it != fields.end()) {
        QSpinBox *spinBox = dynamic_cast<QSpinBox*>(it.value());
        if (spinBox) {
            return spinBox->value();
        }
    }
    return 0;
}

int FormVisitor::getComboBoxValue(const QString &field) const {
    auto it = fields.find(field);
    if (it != fields.end()) {
        QComboBox *comboBox = dynamic_cast<QComboBox*>(it.value());
        if (comboBox) {
            return comboBox->currentIndex();
        }
    }
    return 0;
}

void FormVisitor::selectImage(QLabel* previewLabel) {
    QString filePath = QFileDialog::getOpenFileName(this, "Seleziona un'icona", "", "Immagini (*.png *.jpg *.jpeg)");
    if (filePath.isEmpty()) return;

    // Estrarre solo il nome del file (senza percorso)
    QFileInfo fileInfo(filePath);
    QString imageName = fileInfo.fileName();

    // Creiamo la cartella icons/ se non esiste
    QDir dir("icons");
    if (!dir.exists()) dir.mkpath(".");

    // Percorso di salvataggio
    QString openPath = "icons/" + imageName;

    if (QFile::exists(openPath)) {
        previewLabel->setPixmap(QPixmap(openPath).scaled(100, 100, Qt::KeepAspectRatio));
        qDebug() << "Immagine già esistente in:" << openPath;

        // Salviamo temporaneamente il percorso nel campo "imagePath"
        fields["imagePath"] = new QLabel(imageName); // Non verrà mostrata, ma serve per onSave()
    }
    else {
        // Copia il file nella cartella icons/
        if (QFile::copy(filePath, openPath)) {
            previewLabel->setPixmap(QPixmap(openPath).scaled(100, 100, Qt::KeepAspectRatio));
            qDebug() << "Immagine salvata in:" << openPath;

            // Salviamo temporaneamente il percorso nel campo "imagePath"
            fields["imagePath"] = new QLabel(imageName); // Non verrà mostrata, ma serve per onSave()
        } else {
            qDebug() << "Errore nel salvataggio dell'immagine!";
        }
    }
}