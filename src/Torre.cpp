#include <cmath>
#include "Torre.h"

bool Torre::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) 
{
    return x == destX || y == destY; //valido si se mueve en vertical u horizontal
}