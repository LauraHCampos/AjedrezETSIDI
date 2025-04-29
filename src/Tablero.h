#pragma once
#include "Rey.h"
#include "Reina.h"
#include "Torre.h"
#include "Alfil.h"
#include "Caballo.h"
#include "Peon.h"

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
    void click(float x, float y); //control del raton al hacer clic para el movimiento de las piezas
};



