#include "Caballo.h"
#include <cmath>

bool Caballo::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) 
{
    int dx = std::abs(destX - x); //cambio en x
    int dy = std::abs(destY - y); //cambio en y
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2); //valido si se mueve en L en cualquier direccion
}