#include "texto.h"
#include <QDebug>

Texto::Texto():Figura()
{}

Texto::Texto(int x, int y, int z, QColor c, QColor f, QFont ft, QString t):Figura(x, y, z, c, f){
    font = ft;
    texto = t;
}

void Texto::Dibujar(QPainter *painter){
    QPen pen(getColor(), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen( pen);
    painter->setBrush(getFondo());
    painter->setFont(font);
    QPointF punto(getX(),getY());
    painter->drawText(punto, texto);
}
