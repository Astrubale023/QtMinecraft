#ifndef TYPESELECTIONDIALOG_H
#define TYPESELECTIONDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

class TypeSelectionDialog : public QDialog {
    Q_OBJECT

private:
    QComboBox* typeComboBox;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QString selectedType;

public:
    explicit TypeSelectionDialog(QWidget* parent = nullptr);
    QString getSelectedType() const;

private slots:
    void onOkClicked();
};

#endif // TYPESELECTIONDIALOG_H
