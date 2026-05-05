#ifndef MATRIZJUEGO_H
#define MATRIZJUEGO_H

#include "Estructuras.h"

class MatrizJuego {
private:
    int matriz[10][10];
    NodoRuta* inicioRuta;
    NodoRuta* finRuta;

    void limpiarRuta();
    void agregarPasoRuta(int x, int y);

public:
    MatrizJuego();
    ~MatrizJuego();

    void inicializar();
    void imprimir();
    NodoRuta* obtenerInicioRuta();
};

#endif
