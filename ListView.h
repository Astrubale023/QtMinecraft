#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QResizeEvent>

class LibraryManager;
class MinecraftObj;

class ListView : public QWidget {
    Q_OBJECT

private:
    LibraryManager *libraryManager;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QGridLayout *cardLayout; // GridLayout per un adattamento migliore
    QLineEdit *searchBar;
    QPushButton *refreshButton;
    QPushButton *addButton;
    int columnCount; // Numero di colonne per riga (calcolato dinamicamente)

    void populateList(const QString& filter = ""); // Aggiorna la lista con il filtro
    void adjustGridLayout(); // Regola il numero di colonne in base alla dimensione della finestra

public:
    explicit ListView(LibraryManager *libraryManager, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override; // Gestisce il ridimensionamento della finestra

signals:
    void viewItem(MinecraftObj* item);
    void editItem(MinecraftObj* item);
    void deleteItem(MinecraftObj* item);
    void addItem();

private slots:
    void onSearchTextChanged();      // Applica il filtro quando cambia il testo
    void onDeleteConfirmed(MinecraftObj* item); // Conferma ed elimina un oggetto
    void onAddItemClicked();         // Segnale per aggiungere un nuovo elemento

public slots:
    void onRefreshClicked();         // Ricarica la lista senza filtri

};

#endif // LISTVIEW_H
