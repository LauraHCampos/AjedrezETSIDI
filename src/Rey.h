#pragma once
#include "Pieza.h"

//el rey se puede mover una casilla en cualquier direccion
class Rey : public Pieza //clase Rey derivada de Pieza
{
public:
    Rey(int x, int y, bool color) : Pieza(x, y, color) {} //constructor especifico
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //devuelve si el movimiento es valido
    string getTipo() { return "R"; } //Devuelve una letra R para identificarlo
};

