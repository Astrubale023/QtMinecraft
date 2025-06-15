#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "ListView.h"
#include "FormVisitor.h"
#include "../logic/LibraryManager.h"

enum class Format{ JSON, XML };

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(LibraryManager *libraryManager, QWidget *parent = nullptr);

private slots:
    void showListView();
    void showFormView(MinecraftObj* obj, const FormVisitor::FormMode& mode);
    void saveFile(const Format& format, const QString& fileName) const;
    void loadFile(const Format& format, const QString& fileName);

private:

    void createMenuBar();

    LibraryManager *libraryManager;
    QStackedWidget *stackedWidget;
    ListView *listView;
    QWidget *currentFormView;
};

#endif // MAINWINDOW_H
