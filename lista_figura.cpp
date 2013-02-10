#include "lista_figura.h"
#include <QDebug>

Lista::Lista()
{
    inicio=final=actual=0;
    cuantos=0;
}

void Lista::ir_a_inicio()
{ this->actual = this->inicio; }
void Lista::ir_a_final()
{ this->actual = this->final; }
void Lista::siguiente()
{ this->actual = this->actual->siguiente; }
void Lista::anterior()
{ this->actual = this->actual->anterior; }

Figura* Lista::recuperar()
{
    if(actual!=0)
         return actual->Fig;
    else
        return 0;
}

Figura* Lista::recuperar(int pos)
{
    if(cuantos==0 || pos>cuantos || pos <=0)
        return 0;
    else
    {
        this->ir_a_inicio();
        for(int i=1; i<pos;i++)
        {
            this->siguiente();
        }
        return this->actual->Fig;



    }
}

int Lista::getCuantos()
{
    return cuantos;
}
void Lista::agregar(Figura *F)
{
    nodo_figura *nuevo;
    nuevo = new nodo_figura(F);
    if(this->cuantos==0)
    {
        inicio=final=nuevo;
        actual=nuevo;
    }
    else
    {
        final->siguiente=nuevo;
        nuevo->anterior = final;
        final = nuevo;

    }
    this->cuantos++;

}

Lista::~Lista(){
   this->limpiar();
}
void Lista::limpiar(){
   //this->limpiar_recursivamente(this->inicio);
   this->actual = this->inicio;
   while(this->actual!=0)
   {
       this->inicio=this->inicio->siguiente;
       delete actual->Fig;
       delete actual;
       actual = this->inicio;
   }
   this->inicio =0;
   this->final = 0;
   this->actual =0;
   this->cuantos =0;
}

void Lista::limpiar_recursivamente(nodo_figura *n)
{
    if (n==0)  return;
    else
    {
        this->limpiar_recursivamente(n->siguiente);
        delete n;
    }
}

void Lista::printList(){
    irA(0);
    int i = 1;
    while(actual!=0){
        qDebug() << i << ": " << actual->Fig->tipoFigura();
        actual = actual->siguiente;
        i++;
    }
}

//Lista es 1-based
Figura * Lista::remover(int pos){
    Figura * fig = 0;
    ir_a_inicio();
    for(int i = 1; i < pos; i++)
        siguiente();
    if(pos != 1 && pos != cuantos){
        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
    }else if(pos==1){
        inicio = actual->siguiente;
        if(actual->siguiente != 0)
            actual->siguiente->anterior = 0;
    }else if(pos == cuantos){
        final = actual->anterior;
        actual->anterior->siguiente = 0;
    }else{
        //pos es outOfBounds;
    }
    if(pos >0 && pos <= cuantos){
        cuantos--;
        fig = actual->Fig;
        delete actual;
    }
    return fig;
}

bool Lista::vacia(){
    return inicio == 0 || cuantos == 0;
}

void Lista::irA(int p){
    if(p <= 1){
        ir_a_inicio(); return;
    }
    if(p == cuantos - 1){
        ir_a_final(); return;
    }
    ir_a_inicio();
    for(int i = 1; i <= p; i++){
        if(actual->siguiente != 0)
            siguiente();
    }
}

void Lista::insertar(int pos, Figura * f){
    if(pos >= 1){
        if(vacia() || cuantos <= pos){
            agregar(f);
            return;
        }
        irA(pos);
        nodo_figura * nuevo = new nodo_figura(f);
        if(pos==1){
            inicio = nuevo;
            actual->anterior = nuevo;
            nuevo->siguiente = actual;

        }else{
            actual->anterior->siguiente = nuevo;
            actual->anterior = nuevo;
            nuevo->siguiente = actual;
            nuevo->anterior = actual->anterior;
            if(pos > cuantos)
                final = nuevo;
        }
        cuantos++;
    }
}
