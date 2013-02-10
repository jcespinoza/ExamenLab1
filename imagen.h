#ifndef IMAGEN_H
#define IMAGEN_H

#include "figura.h"
#include <QPixmap>
#include <QImage>

class Imagen: public Figura{

public:
    Imagen();
    Imagen(QString, int, int, int, int);
    void setImage(QString);
    void setImage(QPixmap);
    QPixmap getImage() const{return imagen;}
    QString getPath() const{return imgPath;}
    virtual void Dibujar(QPainter *painter);
    virtual char tipoFigura();
    virtual double area(){return 0;}

    ~Imagen();
private:
    QPixmap imagen;
    QString imgPath;
    int wScale;
    int hScale;
protected:
};

#endif // IMAGEN_H
