#include "TypeSelectionDialog.h"
#include <QDebug>

TypeSelectionDialog::TypeSelectionDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Seleziona Tipo Oggetto");

    typeComboBox = new QComboBox(this);
    typeComboBox->addItems({"Item", "Material", "Weapon", "Block", "OreBlock", "LightBlock"});  // Aggiungi qui i tipi disponibili

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Annulla", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(typeComboBox);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &TypeSelectionDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString TypeSelectionDialog::getSelectedType() const {
    return selectedType;
}

void TypeSelectionDialog::onOkClicked() {
    selectedType = typeComboBox->currentText();
    accept();  // Chiude il dialogo con stato "Accepted"
}
