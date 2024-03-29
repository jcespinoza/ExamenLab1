#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include "figura.h"
#include "lista_figura.h"
#include <math.h>

class PaintBoard : public QWidget
{
   Q_OBJECT
public:
    PaintBoard(QWidget *parent = 0);

    void setListaFiguras ( Lista *l);
    Lista* getLista() const{return lista;}
    int getCurrentFigura() { return this->currentFigura;}
    void guardar(QString f){pix->save(f);}

signals:
    void currentFiguraChanged(int cualFigura);
    void listChanged();

private:
     float distancia(int x, int y, int x1, int y1);
     Lista *lista;
     int currentFigura; // Marca la posicion de la figura actual
     QImage image;
     QPixmap * pix;
protected:
     // Incluir figura.h, rectangulo.h, QPainter
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event );

};

#endif // PAINTBOARD_H
