#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "ListView.h"
#include "FormVisitor.h"
#include "LibraryManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(LibraryManager *libraryManager, QWidget *parent = nullptr);

private slots:
    void showListView();
    void showFormView(MinecraftObj* obj, FormVisitor::FormMode mode);
    void saveJson();
    void loadJson();

private:
    void createMenuBar();

    LibraryManager *libraryManager;
    QStackedWidget *stackedWidget;
    ListView *listView;
    QWidget *currentFormView;  // Widget generato dinamicamente dal FormVisitor
};

#endif // MAINWINDOW_H
