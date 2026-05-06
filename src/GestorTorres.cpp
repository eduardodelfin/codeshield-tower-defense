#include "../include/GestorTorres.h"
#include "../include/GestorEnemigos.h"
#include <iostream>

// Inicializa la lista de torres vacia y guarda una referencia al mapa.
GestorTorres::GestorTorres(MatrizJuego* mapaJuego) {
    inicio = 0;
    mapa = mapaJuego;
}

// Libera toda la memoria reservada por las torres y sus nodos.
GestorTorres::~GestorTorres() {
    NodoTorre* actual = inicio;

    while (actual != 0) {
        NodoTorre* siguiente = actual->siguiente;
        delete actual->torre;
        delete actual;
        actual = siguiente;
    }
}

// Coloca una torre si la posicion no esta fuera del mapa, no es camino,
// no es base y no tiene otra torre ocupando la misma celda.
void GestorTorres::colocarTorre(int fila, int col, std::string tipo, int rango, int danio, int cooldown) {
    if (fila < 0 || fila >= 10 || col < 0 || col >= 10) {
        std::cout << "Error: la posicion (" << fila << ", " << col
                  << ") esta fuera de los limites del mapa." << std::endl;
        return;
    }

    if (mapa == 0) {
        std::cout << "Error: no hay un mapa asociado para validar la posicion de la torre." << std::endl;
        return;
    }

    if (mapa->esCamino(fila, col)) {
        std::cout << "Error: no se puede colocar una torre en (" << fila
                  << ", " << col << ") porque esa celda es camino." << std::endl;
        return;
    }

    if (mapa->esBase(fila, col)) {
        std::cout << "Error: no se puede colocar una torre en (" << fila
                  << ", " << col << ") porque esa celda es la base." << std::endl;
        return;
    }

    NodoTorre* actual = inicio;

    while (actual != 0) {
        if (actual->torre->fila == fila && actual->torre->col == col) {
            std::cout << "Error: ya existe una torre en la posicion ("
                      << fila << ", " << col << ")." << std::endl;
            return;
        }

        actual = actual->siguiente;
    }

    Torre* nuevaTorre = new Torre;
    nuevaTorre->fila = fila;
    nuevaTorre->col = col;
    nuevaTorre->tipo = tipo;
    nuevaTorre->rango = rango;
    nuevaTorre->danio = danio;
    nuevaTorre->cooldown = cooldown;
    nuevaTorre->cooldownActual = 0;

    NodoTorre* nuevoNodo = new NodoTorre;
    nuevoNodo->torre = nuevaTorre;
    nuevoNodo->siguiente = 0;

    if (inicio == 0) {
        inicio = nuevoNodo;
    } else {
        actual = inicio;

        while (actual->siguiente != 0) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevoNodo;
    }
}

// Busca una torre por fila y columna, la quita de la lista y libera su memoria.
void GestorTorres::eliminarTorre(int fila, int col) {
    NodoTorre* actual = inicio;
    NodoTorre* anterior = 0;

    while (actual != 0) {
        if (actual->torre->fila == fila && actual->torre->col == col) {
            if (anterior == 0) {
                inicio = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            delete actual->torre;
            delete actual;
            std::cout << "Torre eliminada." << std::endl;
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    std::cout << "No se encontro una torre en esa posicion." << std::endl;
}

// Recorre la lista de torres e imprime su posicion y atributos principales.
void GestorTorres::mostrarTorres() {
    NodoTorre* actual = inicio;

    if (actual == 0) {
        std::cout << "No hay torres colocadas." << std::endl;
        return;
    }

    std::cout << "Torres colocadas:" << std::endl;

    while (actual != 0) {
        std::cout << "Posicion: (" << actual->torre->fila
                  << ", " << actual->torre->col << ")"
                  << " | Tipo: " << actual->torre->tipo
                  << " | Rango: " << actual->torre->rango
                  << " | Danio: " << actual->torre->danio
                  << " | Cooldown: " << actual->torre->cooldown
                  << " | Cooldown actual: " << actual->torre->cooldownActual
                  << std::endl;

        actual = actual->siguiente;
    }
}

// Reduce el cooldown de cada torre y, si puede disparar, busca el primer
// enemigo dentro de su rango usando distancia Manhattan.
void GestorTorres::actualizarTorres(GestorEnemigos& gestorEnemigos) {
    NodoTorre* actualTorre = inicio;

    while (actualTorre != 0) {
        actualTorre->torre->cooldownActual = actualTorre->torre->cooldownActual - 1;

        if (actualTorre->torre->cooldownActual <= 0) {
            NodoEnemigo* actualEnemigo = gestorEnemigos.obtenerPrimerEnemigo();

            while (actualEnemigo != 0) {
                int distancia = actualTorre->torre->fila - actualEnemigo->posicion.x;

                if (distancia < 0) {
                    distancia = distancia * -1;
                }

                int diferenciaColumna = actualTorre->torre->col - actualEnemigo->posicion.y;

                if (diferenciaColumna < 0) {
                    diferenciaColumna = diferenciaColumna * -1;
                }

                distancia = distancia + diferenciaColumna;

                if (distancia <= actualTorre->torre->rango) {
                    gestorEnemigos.recibirDanio(actualEnemigo, actualTorre->torre->danio);
                    actualTorre->torre->cooldownActual = actualTorre->torre->cooldown;
                    break;
                }

                actualEnemigo = actualEnemigo->siguiente;
            }
        }

        actualTorre = actualTorre->siguiente;
    }
}

// Indica si existe una torre colocada en una posicion especifica del mapa.
bool GestorTorres::hayTorreEn(int fila, int col) {
    NodoTorre* actual = inicio;

    while (actual != 0) {
        if (actual->torre->fila == fila && actual->torre->col == col) {
            return true;
        }

        actual = actual->siguiente;
    }

    return false;
}

NodoTorre* GestorTorres::obtenerPrimeraTorre() {
    return inicio;
}
