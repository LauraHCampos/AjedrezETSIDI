#pragma once
#include "Pieza.h"
#include "Tablero.h"

//el rey se puede mover una casilla en cualquier direccion
class Rey : public Pieza //clase Rey derivada de Pieza
{
public:
    Rey(int x, int y, bool color) : Pieza(x, y, color) {} //constructor especifico
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //devuelve si el movimiento es valido
    bool puedeatacar(int destX, int destY, class Pieza* tablero[5][5]); //comprueba si se puede comer al rey
    string getTipo() { return "Rey"; } //Devuelve una letra R para identificarlo
    int getValor() const { return 100; } //devuelve un valor de 100
};
