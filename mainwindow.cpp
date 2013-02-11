#include "mainwindow.h"
#include "texto.h"
#include <QColorDialog>
#include <QFontDialog>
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
    initColors();
    board = new PaintBoard();
    lista = new Lista();
    bocas = new Lista();
    for(int i = 1; i <= 6; i++){
        QString s(":/mouth/res/zombie/mouth");
        s.append(QString::number(i)).append(".png");
        Figura * img = new Imagen(s, 0,0,1, 640,480);
        bocas->agregar(img);
    }
    fillList(bocas, ui->lwBocas, QString("Boca"));
    orejas = new Lista();
    for(int i = 1; i <= 3; i++){
        QString s(":/ear/res/zombie/ears");
        s.append(QString::number(i)).append(".png");
        Figura * img = new Imagen(s, 0,0,1, 640,480);
        orejas->agregar(img);
    }
    fillList(orejas, ui->lwOrejas, QString("Orejas"));
    narices = new Lista();
    for(int i = 1; i <= 5; i++){
        QString s(":/nose/res/zombie/nose");
        s.append(QString::number(i)).append(".png");
        Figura * img = new Imagen(s, 0,0,1, 640,480);
        narices->agregar(img);
    }
    fillList(narices, ui->lwNarices, QString("Nariz"));
    pelos = new Lista();
    for(int i = 1; i <= 6; i++){
        QString s(":/hair/res/zombie/hair");
        s.append(QString::number(i)).append(".png");
        Figura * img = new Imagen(s, 0,0,1, 640,480);
        pelos->agregar(img);
    }
    fillList(pelos, ui->lwPelos, QString("Pelo"));
    ojos = new Lista();
    for(int i = 1; i <= 4; i++){
        QString s(":/eye/res/zombie/eyes");
        s.append(QString::number(i)).append(".png");
        Figura * img = new Imagen(s, 0,0,1, 640,480);
        ojos->agregar(img);
    }
    fillList(ojos, ui->lwOjos, QString("Ojos"));
    board->setListaFiguras(lista);
    ui->grid->addWidget(board);
    actualX = actualY = 0;
    actualZ = 1;
    connect(ui->spPosx, SIGNAL(valueChanged(int)), this, SLOT(setX(int)));
    connect(ui->spPosy, SIGNAL(valueChanged(int)), this, SLOT(setY(int)));
    connect(ui->spPosz, SIGNAL(valueChanged(int)), this, SLOT(setZ(int)));
    connect(board, SIGNAL(listChanged()), this, SLOT(updateListWidget()));
    connect(ui->lwObjects, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setWHValues(QListWidgetItem*)));
}

void MainWindow::initColors(){
    setLBColor(Qt::black, ui->lbColor);
    setLBColor(Qt::blue, ui->lbFondo);
}

void MainWindow::fillList(Lista *list, QListWidget *lw, QString &prefix){
    int count = list->getCuantos();
    qDebug() << "count is: " << count;
    list->ir_a_inicio();
    for(int i = 1; i <= count; i++){
        Imagen* img = new Imagen();
        img = ((Imagen*)list->recuperar());
        QIcon icon(img->getPath());
        QListWidgetItem *ql = new QListWidgetItem(icon, prefix + QString::number(i), 0, 0);
        lw->insertItem(i -  1, ql);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(
                this, "Archivo de Imagen",".", "JPG (*.jpg);; PNG (*.png);; GIF (*.gif);; BMP (*.bmp)");
    Imagen *i;
    if(!file.isEmpty()){
        i = new Imagen();
        QPixmap pix(file);
        i->setImage(pix.scaled(640 - actualX, 480 - actualY, Qt::KeepAspectRatio));
        i->setXYZ(actualX,actualY,actualZ);
        i->setNombre("Imagen Cargada");
        lista->insertar(actualZ, i);
        emit board->listChanged();
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
    ui->lwObjects->clear();
    lista->ir_a_inicio();
    for(int i = 1; i <= lista->getCuantos(); i++){
        Figura * f = lista->recuperar();
        char t = f->tipoFigura();
        QString item(f->getNombre() + " ");
        if(t == 'I'){
            item.append(QString::number(((Imagen*)f)->getW()) + " x ");
            item.append(QString::number(((Imagen*)f)->getH()));
        }else if(t == 'T'){
            item.append("\"" + ((Texto*)f)->getTexto());
            item.append("\"");
        }
        ui->lwObjects->addItem(item);
    }
}

void MainWindow::setWHValues(QListWidgetItem * it){
    int index = ui->lwObjects->currentRow() + 1;
    if(!index > 0)
        return;
    Figura* fig = lista->recuperar(index);
    char tipo = fig->tipoFigura();

    ui->spPosx->setValue((fig->getX()));
    ui->spPosy->setValue((fig->getY()));
    ui->spPosz->setValue((fig->getZ()));

    if(tipo == 'I'){
        Imagen* img = (Imagen*)(fig);

        ui->spWidth->setValue(img->getW());
        ui->spHeight->setValue(img->getH());
    }else if(tipo == 'T'){
        ui->toolBox->setCurrentWidget(ui->pgText);
    }
}

void MainWindow::on_pbUpdate_clicked()
{
    int index = ui->lwObjects->currentRow() + 1;
    if(!index > 0)
        return;
    int w = ui->spWidth->value();
    int h = ui->spHeight->value();
    Figura *fig = lista->recuperar(index);
    char tipo = fig->tipoFigura();
    fig->setXYZ(actualX, actualY, actualZ);
    if(tipo == 'I'){
        Imagen* img = (Imagen*)(fig);
        QPixmap current = img->getImage();
        img->setImage(current.scaled(ui->spWidth->value(), ui->spHeight->value(), Qt::KeepAspectRatio));
    }else if(tipo == 'T'){

    }
    emit board->listChanged();
    if(lista->recuperar() != 0){
        ui->lwObjects->item(index - 1)->setSelected(true);
        ui->lwObjects->setCurrentRow(index - 1);
    }
}

void MainWindow::on_pbFont_clicked()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, ui->lbFont->font(), this,
                                      "Seleccione la Fuente para el texto", 0);
    if(ok)
        ui->lbFont->setFont(font);
}

void MainWindow::on_pbRemove_clicked()
{
    int index = ui->lwObjects->currentRow() + 1;
    if(!index > 0)
        return;
    lista->remover(index);
    emit board->listChanged();
    if(lista->recuperar() != 0){
        ui->lwObjects->item(index - 1)->setSelected(true);
        ui->lwObjects->setCurrentRow(index - 1);
    }
}

void MainWindow::on_pbAdd_clicked()
{
    QWidget* cPage = ui->toolBox->currentWidget();
    if(cPage == ui->pgText){
        ui->actionInsertText->trigger();
    }else if(cPage == ui->pgEyes){
        ui->actionInsertEyes->trigger();
    }else if(cPage == ui->pgEars){
        ui->actionInsertEars->trigger();
    }else if(cPage == ui->pgHair){
        ui->actionInsertHair->trigger();
    }else if(cPage == ui->pgMouth){
        ui->actionInsertMouth->trigger();
    }else if(cPage == ui->pgNoses){
        ui->actionInsertNose->trigger();
    }else{
        qDebug() << "none of them";
    }
}

void MainWindow::on_actionInsertText_triggered()
{
    Texto *t = new Texto(actualX, actualY, actualZ,
             ui->lbColor->palette().background().color(),
             ui->lbFondo->palette().background().color(),
             ui->lbFont->font(),
             ui->leTexto->text()  );
    t->setNombre("Texto ");
    lista->insertar(actualZ, t);
    emit board->listChanged();
}

void MainWindow::takeFromList(QListWidget * from, Lista * stor, Lista * to, QString nom){
    int index = from->currentRow();
    if(index < 0)
        return;
    Imagen* imagen = ((Imagen*)stor->recuperar(index + 1));
    imagen->setXYZ(actualX, actualY, actualZ);
    imagen->setNombre(nom);
    to->insertar(actualZ, imagen);
    emit board->listChanged();
}

void MainWindow::on_actionInsertEyes_triggered()
{
    takeFromList(ui->lwOjos, ojos, lista, "Ojos ");
}

void MainWindow::on_actionInsertEars_triggered()
{
    takeFromList(ui->lwOrejas, orejas, lista, "Orejas ");
}

void MainWindow::on_actionInsertMouth_triggered()
{
    takeFromList(ui->lwBocas, bocas, lista, "Boca ");
}

void MainWindow::on_actionInsertNose_triggered()
{
    takeFromList(ui->lwNarices, narices, lista, "Nariz ");
}

void MainWindow::on_actionInsertHair_triggered()
{
    takeFromList(ui->lwPelos, pelos, lista, "Pelo ");
}

void MainWindow::on_actionClean_triggered()
{
    lista->limpiar();
    emit board->listChanged();
}

QColor MainWindow::retColor(QColor def){
    return QColorDialog::getColor(def, this, "Seleccion de Color",0);
}

void MainWindow::setLBColor(QColor c, QWidget *wid){
    QPalette pal = wid->palette();
    pal.setColor(wid->backgroundRole(),c);
    wid->setPalette(pal);
    wid->setAutoFillBackground(true);
}

void MainWindow::on_pbFondo_clicked()
{
    setLBColor(retColor(ui->lbFondo->palette().background().color()), ui->lbFondo);
}

void MainWindow::on_pbColor_clicked()
{
    setLBColor(retColor(ui->lbColor->palette().background().color()), ui->lbColor);
}
