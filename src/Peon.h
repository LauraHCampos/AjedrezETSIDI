#pragma once
#include "Pieza.h"

//se muven hacia delante o en diagonal SOLO para capturar
class Peon : public Pieza //clase Peon derivada de Pieza
{
public:
    Peon(int x, int y, bool color) : Pieza(x, y, color) {} //constructor con la posicion y el color
    bool movimientoValido(int destX, int destY, Pieza* tablero[5][5]); //llama a la funcion de movimeintos validos
    bool puedeatacar(int destX, int destY, class Pieza* tablero[5][5]); //comprueba si se puede comer al rey
    string getTipo() { return "Peon"; } //devuelve el nombre de la pieza
    int getValor() const { return 1; } //devuelve un valor de 1
};
