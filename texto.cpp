#include "texto.h"
#include <QDebug>

Texto::Texto():Figura()
{}

Texto::Texto(int x, int y, int z, QColor c, QColor f, QFont ft, QString t){
    setFondo(f);
    setColor(c);
    setXYZ(x,y,z);
    font = ft;
    texto = t;
}

void Texto::Dibujar(QPainter *painter){
    QPen pen(this->getColor(), 5);
    painter->setPen( pen);
    painter->setBrush(Figura::getFondo());
    painter->setFont(font);
    QRect r = QRect(getX(), getY(), 640, 480);
    painter->drawText(r, Qt::AlignTop, texto);
}
