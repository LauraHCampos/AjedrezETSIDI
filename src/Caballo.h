#pragma once
#include "Pieza.h"

//se mueve en L
class Caballo : public Pieza //clase Caballo derivada de Pieza
{ 
public:
    Caballo(int x, int y, bool color) : Pieza(x, y, color) {} //constructor especifico
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //devuelve si el movimiento es valido
    string getTipo() { return "C"; } //Devuelve una letra C para identificarlo
};

