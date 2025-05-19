#pragma once
#include "Pieza.h"

//se mueve en L
class Caballo : public Pieza //clase Caballo derivada de Pieza
{
public:
    Caballo(int x, int y, bool color) : Pieza(x, y, color) {} //constructor especifico
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //devuelve si el movimiento es valido
    bool puedeatacar(int destX, int destY, class Pieza* tablero[5][5]); //comprueba si se puede comer al rey
    string getTipo() { return "Caballo"; } //Devuelve una letra C para identificarlo
    int getValor() const { return 5; } //devuelve un valor de 5
};
