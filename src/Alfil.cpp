#include "Alfil.h"
#include <cmath>

bool Alfil::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) 
{
    return std::abs(destX - x) == std::abs(destY - y); //distancia en vertical y en horizontal, para que sea valido tiene que ser la misma
}