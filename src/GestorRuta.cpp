#include "../include/Estructuras.h"
#include <iostream>

class GestorRuta {
private:
    NodoRuta* inicio;
    NodoRuta* fin;

public:
    GestorRuta() {
        inicio = 0;
        fin = 0;
    }

    ~GestorRuta() {
        NodoRuta* actual = inicio;

        while (actual != 0) {
            NodoRuta* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void agregarPaso(int x, int y) {
        NodoRuta* nuevo = new NodoRuta;

        nuevo->posicion.x = x;
        nuevo->posicion.y = y;
        nuevo->siguiente = 0;

        if (inicio == 0) {
            inicio = nuevo;
            fin = nuevo;
        } else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
    }

    NodoRuta* obtenerInicio() {
        return inicio;
    }

    void mostrarRuta() {
        NodoRuta* actual = inicio;

        if (actual == 0) {
            std::cout << "La ruta esta vacia." << std::endl;
            return;
        }

        std::cout << "Ruta registrada:" << std::endl;

        while (actual != 0) {
            std::cout << "(" << actual->posicion.x
                      << ", " << actual->posicion.y << ")";

            if (actual->siguiente != 0) {
                std::cout << " -> ";
            }

            actual = actual->siguiente;
        }

        std::cout << std::endl;
    }
};
