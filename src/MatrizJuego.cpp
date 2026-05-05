#include "../include/MatrizJuego.h"
#include <iostream>

MatrizJuego::MatrizJuego() {
    inicioRuta = 0;
    finRuta = 0;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matriz[i][j] = 0;
        }
    }
}

MatrizJuego::~MatrizJuego() {
    limpiarRuta();
}

void MatrizJuego::limpiarRuta() {
    NodoRuta* actual = inicioRuta;

    while (actual != 0) {
        NodoRuta* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    inicioRuta = 0;
    finRuta = 0;
}

void MatrizJuego::agregarPasoRuta(int x, int y) {
    NodoRuta* nuevo = new NodoRuta;
    nuevo->posicion.x = x;
    nuevo->posicion.y = y;
    nuevo->siguiente = 0;

    if (inicioRuta == 0) {
        inicioRuta = nuevo;
        finRuta = nuevo;
    } else {
        finRuta->siguiente = nuevo;
        finRuta = nuevo;
    }
}

void MatrizJuego::inicializar() {
    limpiarRuta();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matriz[i][j] = 0;
        }
    }

    for (int y = 0; y <= 4; y++) {
        matriz[0][y] = 1;
        agregarPasoRuta(0, y);
    }

    for (int x = 1; x <= 5; x++) {
        matriz[x][4] = 1;
        agregarPasoRuta(x, 4);
    }

    for (int y = 5; y <= 8; y++) {
        matriz[5][y] = 1;
        agregarPasoRuta(5, y);
    }

    matriz[5][9] = 8;
    agregarPasoRuta(5, 9);
}

void MatrizJuego::imprimir() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << matriz[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

NodoRuta* MatrizJuego::obtenerInicioRuta() {
    return inicioRuta;
}

bool MatrizJuego::esCamino(int x, int y) {
    return matriz[x][y] == 1;
}

bool MatrizJuego::esBase(int x, int y) {
    return matriz[x][y] == 8;
}

void MatrizJuego::mostrarRuta() {
    NodoRuta* actual = inicioRuta;

    while (actual != 0) {
        std::cout << "(" << actual->posicion.x
                  << "," << actual->posicion.y << ")";

        if (actual->siguiente != 0) {
            std::cout << " -> ";
        }

        actual = actual->siguiente;
    }

    std::cout << std::endl;
}
