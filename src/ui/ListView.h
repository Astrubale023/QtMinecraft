#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QMessageBox>
#include "../logic/MinecraftObj.h"

class LibraryManager;

class ListView : public QWidget {
    Q_OBJECT

public:
    explicit ListView(LibraryManager *libraryManager, QWidget *parent = nullptr);

signals:
    void viewItem(MinecraftObj* obj);  // Segnale per mostrare i dettagli
    void editItem(MinecraftObj* obj);  // Segnale per modificare un oggetto
    void addItem(MinecraftObj* tempObj); // Segnale per aggiungere un nuovo oggetto

public slots:
    void onRefreshClicked(); // Aggiorna la lista
    void onSearchTextChanged(); // Filtra gli elementi in base alla barra di ricerca

protected:
    void resizeEvent(QResizeEvent *event) override; // Adatta la griglia alla finestra

private:
    LibraryManager *libraryManager;
    
    // UI Components
    QLineEdit *searchBar;
    QPushButton *refreshButton;
    QPushButton *addButton;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QGridLayout *cardLayout;
    
    int columnCount;

    // Metodi privati
    void populateList(const QString& filter = ""); // Carica gli oggetti nella lista
    void adjustGridLayout(); // Adatta la griglia in base alla dimensione della finestra
    void onDeleteConfirmed(MinecraftObj* item); // Conferma ed elimina un oggetto
    void onAddItemClicked(); // Mostra il form per aggiungere un oggetto
};

#endif // LISTVIEW_H
