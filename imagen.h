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
    QImage getImage() const{return imagen;}
    QString getPath() const{return imgPath;}
    virtual void Dibujar(QPainter *painter);
    ~Imagen();
private:
    QPixmap imagen;
    QString imgPath;
protected:
};

#endif // IMAGEN_H
