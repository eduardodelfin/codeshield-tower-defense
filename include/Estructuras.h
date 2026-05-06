#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>

struct Coordenada {
    int x;
    int y;
};

struct NodoRuta {
    Coordenada posicion;
    NodoRuta* siguiente;
};

struct NodoEnemigo {
    int id;
    int vida;
    int velocidad;
    Coordenada posicion;

    NodoRuta* objetivoRuta;

    NodoEnemigo* siguiente;
    NodoEnemigo* anterior;

    int vidaMaxima;
    bool estaVivo;
};

struct Torre {
    int fila;
    int col;
    std::string tipo;
    int rango;
    int danio;
    int cooldown;
    int cooldownActual;
};

struct NodoTorre {
    Torre* torre;
    NodoTorre* siguiente;
};

struct NodoMejora {
    int costo;
    int nuevoDano;
    int nuevoRango;

    NodoMejora* izquierda;
    NodoMejora* derecha;
};

#endif
