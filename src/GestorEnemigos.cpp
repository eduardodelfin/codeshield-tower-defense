#include "../include/Estructuras.h"
#include <iostream>

class GestorEnemigos {
private:
    NodoEnemigo* cabeza;
    NodoEnemigo* cola;

public:
    GestorEnemigos() {
        cabeza = 0;
        cola = 0;
    }

    ~GestorEnemigos() {
        NodoEnemigo* actual = cabeza;

        while (actual != 0) {
            NodoEnemigo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void insertarEnemigo(int id, int vida, int velocidad, int x, int y) {
        NodoEnemigo* nuevo = new NodoEnemigo;

        nuevo->id = id;
        nuevo->vida = vida;
        nuevo->velocidad = velocidad;
        nuevo->posicion.x = x;
        nuevo->posicion.y = y;
        nuevo->objetivoRuta = 0;
        nuevo->siguiente = 0;
        nuevo->anterior = cola;

        if (cabeza == 0) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            cola = nuevo;
        }
    }

    void eliminarEnemigo(int id) {
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

    void mostrarEnemigos() {
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
};
