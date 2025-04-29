#pragma once
#include "Pieza.h"

//la torre se mueve en linea recta, en vertical u horizontal
class Torre : public Pieza //clase Torre derivada de Pieza
{
public:
    Torre(int x, int y, bool color) : Pieza(x, y, color) {} //constructor específico
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //devuelve si el movimiento es valido
    string getTipo() { return "T"; } //Devuelve una letra T para identificarlo
};

