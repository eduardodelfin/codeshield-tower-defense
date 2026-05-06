#include "../include/MatrizJuego.h"
#include "../include/GestorTorres.h"
#include "../include/GestorEnemigos.h"
#include <SFML/Graphics.hpp>

void dibujarMapa(sf::RenderWindow& ventana, MatrizJuego& mapa, int tamCelda) {
    sf::RectangleShape celda(sf::Vector2f((float) tamCelda, (float) tamCelda));
    celda.setOutlineColor(sf::Color::Black);
    celda.setOutlineThickness(1.0f);

    for (int fila = 0; fila < 10; fila++) {
        for (int col = 0; col < 10; col++) {
            if (mapa.esBase(fila, col)) {
                celda.setFillColor(sf::Color(92, 26, 26));
            } else if (mapa.esCamino(fila, col)) {
                celda.setFillColor(sf::Color(26, 58, 92));
            } else {
                celda.setFillColor(sf::Color(45, 45, 68));
            }

            celda.setPosition((float) (col * tamCelda), (float) (fila * tamCelda));
            ventana.draw(celda);
        }
    }
}

void dibujarTorres(sf::RenderWindow& ventana, GestorTorres& gestorTorres, int tamCelda) {
    sf::RectangleShape torre(sf::Vector2f(40.0f, 40.0f));
    torre.setFillColor(sf::Color(45, 106, 45));

    NodoTorre* actual = gestorTorres.obtenerPrimeraTorre();

    while (actual != 0) {
        float offset = (tamCelda - 40.0f) / 2.0f;
        float x = actual->torre->col * tamCelda + offset;
        float y = actual->torre->fila * tamCelda + offset;

        torre.setPosition(x, y);
        ventana.draw(torre);

        actual = actual->siguiente;
    }
}

void dibujarEnemigos(sf::RenderWindow& ventana, GestorEnemigos& gestorEnemigos, int tamCelda) {
    sf::CircleShape enemigo(15.0f);
    enemigo.setFillColor(sf::Color(204, 34, 0));

    NodoEnemigo* actual = gestorEnemigos.obtenerPrimerEnemigo();

    while (actual != 0) {
        float offset = (tamCelda - 30.0f) / 2.0f;
        float x = actual->posicion.y * tamCelda + offset;
        float y = actual->posicion.x * tamCelda + offset;

        enemigo.setPosition(x, y);
        ventana.draw(enemigo);

        actual = actual->siguiente;
    }
}

void dibujarHUD(sf::RenderWindow& ventana, sf::Font& fuente, int vidaBase, int turno) {
    sf::Text texto;
    texto.setFont(fuente);
    texto.setCharacterSize(20);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(10.0f, 10.0f);
    texto.setString("Vida base: " + std::to_string(vidaBase) + "  Turno: " + std::to_string(turno));
    ventana.draw(texto);
}

int main() {
    sf::RenderWindow ventana(sf::VideoMode(600, 600), "CODESHIELD");
    sf::Color colorFondo(26, 26, 46);

    MatrizJuego mapa;
    GestorTorres gestorTorres(&mapa);
    GestorEnemigos gestorEnemigos;
    sf::Font fuente;
    NodoRuta* inicioRuta;
    int vidaBase = 5;
    int turno = 1;
    const int tamCelda = 60;

    if (!fuente.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        return 1;
    }

    mapa.inicializar();
    inicioRuta = mapa.obtenerInicioRuta();

    gestorTorres.colocarTorre(2, 2, "Basica", 3, 20, 1);
    gestorEnemigos.insertarEnemigo(1, 30, 1, 0, 0, inicioRuta);
    gestorEnemigos.insertarEnemigo(2, 50, 1, 0, 0, inicioRuta);
    gestorEnemigos.insertarEnemigo(3, 80, 1, 0, 0, inicioRuta);

    while (ventana.isOpen() && vidaBase > 0) {
        sf::Event evento;

        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
                ventana.close();
            }
        }

        ventana.clear(colorFondo);
        dibujarMapa(ventana, mapa, 60);
        dibujarTorres(ventana, gestorTorres, 60);
        dibujarEnemigos(ventana, gestorEnemigos, 60);
        dibujarHUD(ventana, fuente, vidaBase, turno);
        ventana.display();
        sf::sleep(sf::milliseconds(300));
        gestorTorres.actualizarTorres(gestorEnemigos);
        gestorEnemigos.moverEnemigos();
        gestorEnemigos.verificarLlegadaABase(vidaBase);
        gestorEnemigos.limpiarMuertos();
        turno++;
    }

    if (ventana.isOpen() && vidaBase <= 0) {
        sf::Text gameOver;
        gameOver.setFont(fuente);
        gameOver.setString("GAME OVER");
        gameOver.setCharacterSize(48);
        gameOver.setFillColor(sf::Color::White);
        gameOver.setPosition(130.0f, 260.0f);

        ventana.clear(colorFondo);
        ventana.draw(gameOver);
        ventana.display();
        sf::sleep(sf::seconds(3));
    }

    ventana.close();
    return 0;
}
