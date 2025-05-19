#include <cmath>
#include "Torre.h"


bool Torre::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) {
    
    if (tablero[destX][destY] && tablero[destX][destY]->getTipo() == "Rey")
    {
        return false; // no se puede capturar al rey
    }

    if (x != destX && y != destY) return false;
    if (x == destX && y == destY) return false;//NUEVO

    int stepX = (destX - x) != 0 ? (destX - x) / std::abs(destX - x) : 0;
    int stepY = (destY - y) != 0 ? (destY - y) / std::abs(destY - y) : 0;

    int i = x + stepX;
    int j = y + stepY;

    while (i != destX || j != destY) {
        if (tablero[i][j]) return false;
        i += stepX;
        j += stepY;
    }

    return true;
}


bool Torre::puedeatacar(int destX, int destY, Pieza* tablero[5][5]) {
    if (x == destX) {
        int dir = (destY > y) ? 1 : -1;
        for (int j = y + dir; j != destY; j += dir)
            if (tablero[x][j]) return false;
        return true;
    }
    if (y == destY) {
        int dir = (destX > x) ? 1 : -1;
        for (int i = x + dir; i != destX; i += dir)
            if (tablero[i][y]) return false;
        return true;
    }
    return false;
}
