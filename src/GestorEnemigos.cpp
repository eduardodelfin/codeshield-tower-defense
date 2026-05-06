#include "../include/GestorEnemigos.h"
#include <iostream>

GestorEnemigos::GestorEnemigos() {
    cabeza = 0;
    cola = 0;
}

GestorEnemigos::~GestorEnemigos() {
    NodoEnemigo* actual = cabeza;

    while (actual != 0) {
        NodoEnemigo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void GestorEnemigos::insertarEnemigo(int id, int vida, int velocidad, int x, int y, NodoRuta* inicioRuta) {
    NodoEnemigo* nuevo = new NodoEnemigo;

    nuevo->id = id;
    nuevo->vida = vida;
    nuevo->velocidad = velocidad;
    nuevo->objetivoRuta = inicioRuta;
    nuevo->siguiente = 0;
    nuevo->anterior = cola;
    nuevo->vidaMaxima = vida;
    nuevo->estaVivo = true;

    if (inicioRuta != 0) {
        nuevo->posicion.x = inicioRuta->posicion.x;
        nuevo->posicion.y = inicioRuta->posicion.y;
    } else {
        nuevo->posicion.x = x;
        nuevo->posicion.y = y;
    }

    if (cabeza == 0) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        cola = nuevo;
    }
}

void GestorEnemigos::moverEnemigos() {
    NodoEnemigo* actual = cabeza;

    while (actual != 0) {
        if (actual->objetivoRuta != 0 && actual->objetivoRuta->siguiente != 0) {
            actual->objetivoRuta = actual->objetivoRuta->siguiente;
            actual->posicion.x = actual->objetivoRuta->posicion.x;
            actual->posicion.y = actual->objetivoRuta->posicion.y;
        }

        actual = actual->siguiente;
    }
}

void GestorEnemigos::verificarLlegadaABase(int& vidaBase) {
    NodoEnemigo* actual = cabeza;

    while (actual != 0) {
        if (actual->objetivoRuta != 0 && actual->objetivoRuta->siguiente == 0 && actual->estaVivo) {
            vidaBase = vidaBase - 1;
            actual->estaVivo = false;

            std::cout << "Enemigo " << actual->id
                      << " alcanzo la base. Vida base: "
                      << vidaBase << std::endl;
        }

        actual = actual->siguiente;
    }
}

void GestorEnemigos::limpiarMuertos() {
    NodoEnemigo* actual = cabeza;

    while (actual != 0) {
        NodoEnemigo* siguiente = actual->siguiente;

        if (actual->estaVivo == false) {
            if (actual->anterior != 0) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                cabeza = actual->siguiente;
            }

            if (actual->siguiente != 0) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                cola = actual->anterior;
            }

            std::cout << "Enemigo " << actual->id
                      << " eliminado por limpiarMuertos." << std::endl;

            delete actual;
        }

        actual = siguiente;
    }
}

NodoEnemigo* GestorEnemigos::obtenerPrimerEnemigo() {
    return cabeza;
}

void GestorEnemigos::recibirDanio(NodoEnemigo* enemigo, int danio) {
    if (enemigo == 0) {
        return;
    }

    enemigo->vida = enemigo->vida - danio;

    std::cout << "El enemigo " << enemigo->id
              << " recibio " << danio
              << " de danio. Vida restante: "
              << enemigo->vida << std::endl;

    if (enemigo->vida <= 0) {
        int idEnemigo = enemigo->id;
        enemigo->estaVivo = false;
        eliminarEnemigo(idEnemigo);
    }
}

void GestorEnemigos::eliminarEnemigo(int id) {
    NodoEnemigo* actual = cabeza;

    while (actual != 0) {
        if (actual->id == id) {
            if (actual->anterior != 0) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                cabeza = actual->siguiente;
            }

            if (actual->siguiente != 0) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                cola = actual->anterior;
            }

            delete actual;
            std::cout << "Enemigo con id " << id << " eliminado." << std::endl;
            return;
        }

        actual = actual->siguiente;
    }

    std::cout << "No se encontro un enemigo con id " << id << "." << std::endl;
}

void GestorEnemigos::mostrarEnemigos() {
    NodoEnemigo* actual = cabeza;

    if (actual == 0) {
        std::cout << "No hay enemigos activos." << std::endl;
        return;
    }

    std::cout << "Enemigos activos:" << std::endl;

    while (actual != 0) {
        std::cout << "ID: " << actual->id
                  << " | Vida: " << actual->vida
                  << " | Velocidad: " << actual->velocidad
                  << " | Posicion: (" << actual->posicion.x
                  << ", " << actual->posicion.y << ")"
                  << std::endl;

        actual = actual->siguiente;
    }
}
