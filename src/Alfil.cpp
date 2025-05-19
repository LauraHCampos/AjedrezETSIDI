#include "Alfil.h"
#include <cmath>

bool Alfil::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) {

    if (tablero[destX][destY] && tablero[destX][destY]->getTipo() == "Rey")
    {
        return false; // no se puede capturar al rey
    }

    int dx = destX - x;
    int dy = destY - y;

    if (std::abs(dx) != std::abs(dy)) return false;

    int stepX = dx > 0 ? 1 : -1;
    int stepY = dy > 0 ? 1 : -1;
    int i = x + stepX;
    int j = y + stepY;

    while (i != destX && j != destY) {
        if (tablero[i][j]) return false;
        i += stepX;
        j += stepY;
    }

    return true;
}


bool Alfil::puedeatacar(int destX, int destY, Pieza* tablero[5][5]) {
    int dx = destX - x;
    int dy = destY - y;

    if (std::abs(dx) != std::abs(dy)) return false;

    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;
    int i = x + stepX, j = y + stepY;

    while (i != destX && j != destY) {
        if (tablero[i][j]) return false;
        i += stepX;
        j += stepY;
    }

    return true;
}
