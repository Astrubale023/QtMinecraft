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
    void viewItem(MinecraftObj* obj);
    void editItem(MinecraftObj* obj);
    void addItem(MinecraftObj* tempObj);

public slots:
    void onRefreshClicked();
    void onSearchTextChanged();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    LibraryManager *libraryManager;
    
    QLineEdit *searchBar;
    QPushButton *refreshButton;
    QPushButton *addButton;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QGridLayout *cardLayout;
    
    int columnCount;

    void populateList(const QString& filter = "");
    void adjustGridLayout();
    void onDeleteConfirmed(MinecraftObj* item);
    void onAddItemClicked();
};

#endif // LISTVIEW_H
