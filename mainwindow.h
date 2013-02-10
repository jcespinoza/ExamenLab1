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

    void on_pbUpdate_clicked();

    void on_pbFont_clicked();

    void on_pbRemove_clicked();

    void on_pbAdd_clicked();

    void on_actionInsertText_triggered();

    void on_actionInsertEyes_triggered();

    void on_actionInsertEars_triggered();

    void on_actionInsertMouth_triggered();

    void on_actionInsertNose_triggered();

    void on_actionInsertHair_triggered();

    void on_actionClean_triggered();

    void on_pbFondo_clicked();

    void on_pbColor_clicked();

private:
    Ui::MainWindow *ui;
    PaintBoard * board;
    Lista *lista;
    int actualX;
    int actualY;
    int actualZ;
    void init();
    void initColors();
    QColor retColor(QColor def);
    void setLBColor(QColor c, QWidget *wid);
    Lista* bocas;
    Lista* ojos;
    Lista* narices;
    Lista* pelos;
    Lista* cicatrices;
    Lista* orejas;
};

#endif // MAINWINDOW_H
