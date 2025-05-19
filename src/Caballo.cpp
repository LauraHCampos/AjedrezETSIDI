#include "Caballo.h"
#include <cmath>

bool Caballo::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) {

    if (tablero[destX][destY] && tablero[destX][destY]->getTipo() == "Rey")
    {
        return false; // no se puede capturar al rey
    }

    int dx = std::abs(destX - x);
    int dy = std::abs(destY - y);

    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))
        return true;

    return false;
}

bool Caballo::puedeatacar(int destX, int destY, Pieza* tablero[5][5]) {
    int dx = std::abs(destX - x);
    int dy = std::abs(destY - y);

    // Movimiento en L: dos en una dirección y uno en la otra
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
