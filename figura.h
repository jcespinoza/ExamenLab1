#ifndef FIGURA_H
#define FIGURA_H
#include <Qt>
#include <QPainter>
class Figura
{
public:
    Figura();
    Figura(int x, int y, QColor color, QColor fondo);

    virtual void Dibujar (QPainter *painter) = 0;
    virtual char tipoFigura() = 0;
    virtual double area() = 0;

    virtual void setX(int newx);  // Por ejemplo este no valida negativos
    virtual void setY(int newy);  // Se puede sobre escribir por las clases derivadas
    virtual void setZ(int newz);  // Y llamar a la clase base
    virtual void setXYZ(int, int, int);
    // Metodos publicos NO virtuales
    int getX() const;
    int getY() const;
    int getZ() const{return z;}
    void setColor(QColor color);
    void setFondo(QColor fondo);
    QColor getColor() const;
    QColor getFondo() const;
protected:
    virtual void Mover (int newx, int newy);  // PAra explicar lo de protected
 private:
    int x,y,z;
    QColor color,fondo;
};

#endif // FIGURA_H
