#pragma once
#include "Pieza.h"

//la torre se mueve en linea recta, en vertical u horizontal
class Torre : public Pieza //clase Torre derivada de Pieza
{
public:
    Torre(int x, int y, bool color) : Pieza(x, y, color) {} //constructor especifico
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //devuelve si el movimiento es valido
    bool puedeatacar(int destX, int destY, class Pieza* tablero[5][5]); //comprueba si se puede comer al rey
    string getTipo() { return "Torre"; } //Devuelve una letra T para identificarlo
    int getValor() const { return 5; } //devuelve un valor de 5
};
