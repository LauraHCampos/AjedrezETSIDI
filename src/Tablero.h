#pragma once
#include "Rey.h"
#include "Reina.h"
#include "Torre.h"
#include "Alfil.h"
#include "Caballo.h"
#include "Peon.h"

enum EstadoJuego {
    NORMAL,
    JAQUE,
    JAQUE_MATE
};

struct Movimiento {
    int origenX;
    int origenY;
    int destinoX;
    int destinoY;
};

class Tablero
{
private:
    Pieza* casillas[5][5]; //tablero de 5x5 
    bool turnoBlancas; //control de turno
    int seleccionX, seleccionY; //posicion de la pieza seleccionada a mover

public:
    Tablero(int sel3); //constructor
    ~Tablero(); //destructor

    void dibujar(int sel2); //dibujar el tablero y las piezas
    void imprimirTextura(const std::string& ruta, int x, int y); //para imprimir las imagenes de las piezas
    EstadoJuego click(float x, float y, int sel1); //control del raton al hacer clic para el movimiento de las piezas
    void pintarmovimiento(float r, float g, float b, int i, int j);
    bool estaEnJaque(bool turnoBlanco);
    bool esJaqueMate(bool turnoBlanco);
    int evaluarTablero();
    EstadoJuego moverIA();
};

