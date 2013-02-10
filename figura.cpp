#include "figura.h"

Figura::Figura()
{
    x = y = z = 0;
    color = Qt::black;
    fondo = Qt::white;
    nombre = "Figura";
}
Figura::Figura(int x, int y, int z, QColor color, QColor fondo)
{
    this->x =x;
    this->y = y;
    this->z = z;
    this->color = color;
    this->fondo = fondo;
}
void Figura::Mover(int newx, int newy)
{
  this->setX(newx);
  this->setY(newy);
}
void Figura::setX(int newx)
{
    this->x=newx;
}
void Figura::setY(int newy)
{
    this->y=newy;
}
void Figura::setZ(int newz)
{
    this->z=newz;
}
void Figura::setXYZ(int xx, int yy, int zz){
    x = xx;
    y = yy;
    z = zz;
}

int Figura::getX() const
{
    return x;
}
int Figura::getY() const
{
    return y;
}
void Figura::setColor(QColor color)
{
    this->color = color;
}
void Figura::setFondo(QColor fondo)
{
    this->fondo = fondo;
}
QColor Figura::getColor() const
{
  return this->color;
}
QColor Figura::getFondo() const
{
  return this->fondo;
}

void Figura::setNombre(QString s){
    nombre = s;
}
