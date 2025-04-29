#pragma once
#include "Pieza.h"

//la reina se mueve en todas las direcciones, salvo como el caballo
class Reina : public Pieza //clase Reina derivada de Pieza
{
public:
    Reina(int x, int y, bool color) : Pieza(x, y, color) {} //constructor específico
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //devuelve si el movimiento es valido
    string getTipo() { return "Q"; } //Devuelve una letra Q para identificarlo
};

