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
    Tablero(); //constructor
    ~Tablero(); //destructor

    void dibujar(); //dibujar el tablero y las piezas
    EstadoJuego click(float x, float y); //control del raton al hacer clic para el movimiento de las piezas

    bool estaEnJaque(bool turnoBlanco);
    bool esJaqueMate(bool turnoBlanco);
    int evaluarTablero();
    EstadoJuego moverIA();
};
