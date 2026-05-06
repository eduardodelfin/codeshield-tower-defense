#ifndef GESTORENEMIGOS_H
#define GESTORENEMIGOS_H

#include "Estructuras.h"

class GestorEnemigos {
private:
    NodoEnemigo* cabeza;
    NodoEnemigo* cola;

public:
    GestorEnemigos();
    ~GestorEnemigos();

    void insertarEnemigo(int id, int vida, int velocidad, int x, int y, NodoRuta* inicioRuta);
    void moverEnemigos();
    void verificarLlegadaABase(int& vidaBase);
    void limpiarMuertos();
    NodoEnemigo* obtenerPrimerEnemigo();
    void recibirDanio(NodoEnemigo* enemigo, int danio);
    void eliminarEnemigo(int id);
    void mostrarEnemigos();
};

#endif
