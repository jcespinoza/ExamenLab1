#include "imagen.h"

Imagen::Imagen():Figura(){
    wScale=hScale=0;
}

Imagen::Imagen(QString file, int x=0, int y=0, int w=0, int h=0):Figura(x, y, Qt::black, Qt::white){
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
}
