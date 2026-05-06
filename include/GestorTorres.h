#ifndef GESTORTORRES_H
#define GESTORTORRES_H

#include "Estructuras.h"
#include "MatrizJuego.h"

class GestorEnemigos;

class GestorTorres {
private:
    NodoTorre* inicio;
    MatrizJuego* mapa;

public:
    GestorTorres(MatrizJuego* mapaJuego);
    ~GestorTorres();

    void colocarTorre(int fila, int col, std::string tipo, int rango, int danio, int cooldown);
    void eliminarTorre(int fila, int col);
    void mostrarTorres();
    void actualizarTorres(GestorEnemigos& gestorEnemigos);
    bool hayTorreEn(int fila, int col);
    NodoTorre* obtenerPrimeraTorre();
};

#endif
