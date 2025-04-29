#include "Reina.h"
#include <cmath>

bool Reina::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) 
{
    int dx = std::abs(destX - x); //cambio en x
    int dy = std::abs(destY - y); //cambio en y
    return dx == dy || x == destX || y == destY; //valido si se mueve en vertical, horizontal o diagonal
}