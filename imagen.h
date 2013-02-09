#ifndef IMAGEN_H
#define IMAGEN_H

#include "figura.h"
#include <QPixmap>
#include <QImage>

class Imagen: public Figura{

public:
    Imagen();
    Imagen(QString, int, int);
    void setImage(QString);
    virtual void Dibujar(QPainter *painter);
private:
    QPixmap imagen;
protected:
};

#endif // IMAGEN_H
