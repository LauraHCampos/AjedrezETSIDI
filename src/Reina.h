#pragma once
#include "Pieza.h"

//la reina se mueve en todas las direcciones, salvo como el caballo
class Reina : public Pieza //clase Reina derivada de Pieza
{
public:
    Reina(int x, int y, bool color) : Pieza(x, y, color) {} //constructor espec�fico
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //devuelve si el movimiento es valido
    bool puedeatacar(int destX, int destY, class Pieza* tablero[5][5]); //comprueba si se puede comer al rey
    string getTipo() { return "Queen"; } //Devuelve una letra Q para identificarlo
    int getValor() const { return 9; } //devuelve un valor de 9
};

