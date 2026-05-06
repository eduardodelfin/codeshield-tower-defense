#include "../include/MatrizJuego.h"
#include "../include/GestorTorres.h"
#include "../include/GestorEnemigos.h"
#include <iostream>

int main() {
    MatrizJuego mapa;
    GestorTorres gestorTorres(&mapa);
    GestorEnemigos gestorEnemigos;
    NodoRuta* inicioRuta;
    int vidaBase = 5;
    int turno = 1;

    mapa.inicializar();
    inicioRuta = mapa.obtenerInicioRuta();

    gestorTorres.colocarTorre(2, 2, "Basica", 3, 20, 1);
    gestorEnemigos.insertarEnemigo(1, 30, 1, 0, 0, inicioRuta);
    gestorEnemigos.insertarEnemigo(2, 50, 1, 0, 0, inicioRuta);
    gestorEnemigos.insertarEnemigo(3, 80, 1, 0, 0, inicioRuta);

    while (vidaBase > 0) {
        std::cout << "Iteracion " << turno << ":" << std::endl;
        mapa.imprimirMapa(gestorTorres);
        gestorEnemigos.mostrarEnemigos();
        gestorTorres.actualizarTorres(gestorEnemigos);
        gestorEnemigos.moverEnemigos();
        gestorEnemigos.verificarLlegadaABase(vidaBase);
        gestorEnemigos.limpiarMuertos();
        std::cout << "Vida base: " << vidaBase << std::endl;
        std::cout << std::endl;
        std::cin.get();
        turno = turno + 1;
    }

    std::cout << "GAME OVER" << std::endl;

    return 0;
}
