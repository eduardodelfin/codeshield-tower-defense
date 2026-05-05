#include <iostream>
#include "GestorEnemigos.cpp"

int main() {
    GestorEnemigos gestor;

    gestor.insertarEnemigo(1, 100, 2, 0, 0);
    gestor.insertarEnemigo(2, 120, 1, 3, 1);
    gestor.insertarEnemigo(3, 80, 3, 5, 2);

    std::cout << "Lista inicial de enemigos:" << std::endl;
    gestor.mostrarEnemigos();

    std::cout << std::endl;
    std::cout << "Eliminando al enemigo con id 2..." << std::endl;
    gestor.eliminarEnemigo(2);

    std::cout << std::endl;
    std::cout << "Lista actualizada de enemigos:" << std::endl;
    gestor.mostrarEnemigos();

    return 0;
}
