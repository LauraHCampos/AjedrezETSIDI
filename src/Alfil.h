#pragma once
#include "Pieza.h"

//alfil se mueve en diagonal
class Alfil : public Pieza  //clase Alfil derivada de Pieza
{
public:
    Alfil(int x, int y, bool color) : Pieza(x, y, color) {} //constructor posicion inicial y color
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //se puede hacer ese movimiento?
    string getTipo() { return "A"; } //letra que imprime en el tablero
};
