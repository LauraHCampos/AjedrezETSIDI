#include <cmath>
#include "Peon.h"


bool Peon::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) {
    int dir = color ? -1 : 1;  // blancas suben, negras bajan
    int dx = destX - x;
    int dy = destY - y;
    if (tablero[destX][destY] && tablero[destX][destY]->getTipo() == "Rey")
    {
        return false; // no se puede capturar al rey
    }

    // Movimiento recto hacia adelante
    if (dy == 0 && dx == dir && tablero[destX][destY] == nullptr)
        return true;

    // Captura en diagonal: solo si hay pieza y es del oponente
    if (std::abs(dy) == 1 && dx == dir && tablero[destX][destY] != nullptr) {
        return tablero[destX][destY]->getColor() != color;
    }

    return false;
}



bool Peon::puedeatacar(int destX, int destY, Pieza* tablero[5][5]) 
{
    int dir = color ? -1 : 1; // blanco sube, negro baja
    return destX == x + dir && std::abs(destY - y) == 1;
}
