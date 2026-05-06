#include "../include/MatrizJuego.h"
#include "../include/GestorTorres.h"
#include "GestorEnemigos.cpp"
#include <iostream>

int main() {
    MatrizJuego mapa;
    GestorTorres gestorTorres(&mapa);
    GestorEnemigos gestorEnemigos;
    NodoRuta* inicioRuta;

    mapa.inicializar();
    inicioRuta = mapa.obtenerInicioRuta();

    gestorTorres.colocarTorre(2, 2, "Basica", 3, 20, 1);
    gestorEnemigos.insertarEnemigo(1, 60, 1, 0, 0, inicioRuta);

    for (int i = 0; i < 6; i++) {
        std::cout << "Iteracion " << i + 1 << ":" << std::endl;
        gestorEnemigos.mostrarEnemigos();
        gestorTorres.actualizarTorres(gestorEnemigos);
        gestorEnemigos.moverEnemigos();
        std::cout << std::endl;
    }

    return 0;
}
