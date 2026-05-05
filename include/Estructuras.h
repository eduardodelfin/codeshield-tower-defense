#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

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
};

struct Torre {
    int id;
    int dano;
    int rango;
    Coordenada posicion;
};

struct NodoMejora {
    int costo;
    int nuevoDano;
    int nuevoRango;

    NodoMejora* izquierda;
    NodoMejora* derecha;
};

#endif