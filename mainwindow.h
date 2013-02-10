#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDebug>
#include "paintboard.h"
#include "lista_figura.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionOpen_triggered();
    void on_actionSaveAs_triggered();
    void setX(int x){actualX = x;}
    void setY(int y){actualY = y;}
    void setZ(int z){actualZ = z;}
    void updateListWidget();
    void setWHValues(QListWidgetItem*);

private:
    Ui::MainWindow *ui;
    PaintBoard * board;
    Lista *lista;
    int actualX;
    int actualY;
    int actualZ;
    void init();
    Lista* bocas;
    Lista* ojos;
    Lista* narices;
    Lista* pelos;
    Lista* cicatrices;
    Lista* orejas;
};

#endif // MAINWINDOW_H
