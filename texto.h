#ifndef TEXTO_H
#define TEXTO_H

#include "figura.h"

class Texto: public Figura
{
public:
    Texto();
    Texto(int, int, int, QColor, QColor, QFont, QString);
    virtual void Dibujar(QPainter *painter);
    virtual char tipoFigura(){return 'T';}
    double area(){return 0;}

    void setFont(QFont f){font = f;}
    QFont getFont() const {return font;}

    void setText(QString s){texto = s;}
    QString getTexto() const{return texto;}

private:
    QFont font;
    QString texto;
};

#endif // TEXTO_H
