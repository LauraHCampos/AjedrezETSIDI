#include "Rey.h"
#include <cmath>

bool Rey::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) 
{
    int dx = std::abs(destX - x); //cambio en x
    int dy = std::abs(destY - y); //cambio en y
    return dx <= 1 && dy <= 1; //valido si se mueve una casilla en cualquier direccion
}