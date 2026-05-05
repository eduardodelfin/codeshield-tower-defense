#include "../include/MatrizJuego.h"
#include "GestorEnemigos.cpp"
#include <iostream>

int main() {
    MatrizJuego mapa;
    NodoRuta* inicioRuta;
    GestorEnemigos gestor;

    mapa.inicializar();
    inicioRuta = mapa.obtenerInicioRuta();

    gestor.insertarEnemigo(1, 100, 1, 0, 0, inicioRuta);

    std::cout << "Posicion inicial:" << std::endl;
    gestor.mostrarEnemigos();

    for (int i = 0; i < 5; i++) {
        gestor.moverEnemigos();
        std::cout << "Movimiento " << i + 1 << ":" << std::endl;
        gestor.mostrarEnemigos();
    }

    return 0;
}
