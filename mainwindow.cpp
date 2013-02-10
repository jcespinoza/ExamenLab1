#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagen.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board;
    delete lista, ojos, bocas, narices, orejas, pelos;
}

void MainWindow::init(){
    board = new PaintBoard();
    lista = new Lista();
    bocas = new Lista();
    orejas = new Lista();
    narices = new Lista();
    pelos = new Lista();
    ojos = new Lista();
    board->setListaFiguras(lista);
    ui->grid->addWidget(board);
    actualX = actualY = 0;
    actualZ = 1;
    connect(ui->spPosx, SIGNAL(valueChanged(int)), this, SLOT(setX(int)));
    connect(ui->spPosy, SIGNAL(valueChanged(int)), this, SLOT(setY(int)));
    connect(ui->spPosz, SIGNAL(valueChanged(int)), this, SLOT(setZ(int)));
    connect(board, SIGNAL(listChanged()), this, SLOT(updateListWidget()));
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(
                this, "Archivo de Imagen",".", "JPG (*.jpg);; PNG (*.png);; GIF (*.gif);; BMP (*.bmp)");
    Imagen *i;
    if(!file.isEmpty()){
        i = new Imagen();
        QPixmap pix(file);
        i->setImage(pix.scaled(640, 480, Qt::KeepAspectRatio));
        i->setXYZ(actualX,actualY,actualZ);
        i->setNombre("Imagen Cargada");
        lista->insertar(actualZ, i);
        board->update();
    }
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Nombre de la imagen",
                                                ".","PNG (*.png);; JPG (*.jpg);; GIF (*.gif);; BMP (*.bmp)");
    if(!file.isEmpty())
        board->guardar(file);
}

void MainWindow::updateListWidget(){
    lista->ir_a_inicio();
    for(int i = 1; i < lista->getCuantos(); i++){
        Figura * f = lista->recuperar();
    }
}
