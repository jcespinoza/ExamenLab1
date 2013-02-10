#include "imagen.h"
#include <QDebug>

Imagen::Imagen():Figura(){
    wScale=hScale=0;
}

Imagen::Imagen(QString file, int x=0, int y=0, int z=0, int w=0, int h=0):Figura(x, y, z, Qt::black, Qt::white){
    setImage(file);
    wScale = w;
    hScale = h;
}

void Imagen::Dibujar(QPainter *painter){
    if(!imagen.isNull())
        painter->drawPixmap(getX(), getY(), imagen.width(), imagen.height(), imagen);
}

void Imagen::setImage(QString file){
    if(!file.isEmpty()){
        imagen.load(file);
        imgPath = file;
    }
}

char Imagen::tipoFigura(){
    return 'I';
}

void Imagen::setImage(QPixmap img){
    imagen = img;
    wScale = img.width();
    hScale = img.height();
    qDebug() << "width" << img.width();
}

void Imagen::setH(int h){
    if(h > 0)
        hScale = h;
}

void Imagen::setW(int w){
    if(w > 0)
        wScale = w;
}
