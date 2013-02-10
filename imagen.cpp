#include "imagen.h"

Imagen::Imagen():Figura(){
}

Imagen::Imagen(QString file, int x, int y):Figura(x, y, Qt::black, Qt::white){
    setImage(file);
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
