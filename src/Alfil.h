#pragma once
#include "Pieza.h"

//alfil se mueve en diagonal
class Alfil : public Pieza  //clase Alfil derivada de Pieza
{
public:
    Alfil(int x, int y, bool color) : Pieza(x, y, color) {} //constructor posicion inicial y color
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //se puede hacer ese movimiento?
    bool puedeatacar(int destX, int destY, class Pieza* tablero[5][5]); //comprueba si se puede comer al rey
    string getTipo() { return "Alfil"; } //devuelve el nombre de la pieza
    int getValor() const { return 5; } //devuelve un valor de 5
};
