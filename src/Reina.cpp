#include "Reina.h"
#include <cmath>
#include "Torre.h"
#include "Alfil.h"

bool Reina::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) {

    if (tablero[destX][destY] && tablero[destX][destY]->getTipo() == "Rey")
    {
        return false; // no se puede capturar al rey
    }

    int dx = std::abs(destX - x);
    int dy = std::abs(destY - y);

    if (dx ==0 && dy == 0)
        return false;

    else if (dx == dy) {
        // Movimiento diagonal
        int stepX = (destX - x) / dx;
        int stepY = (destY - y) / dy;
        int i = x + stepX;
        int j = y + stepY;

        while (i != destX && j != destY) {
            if (tablero[i][j]) return false;
            i += stepX;
            j += stepY;
        }
        return true;
    }
    else if (x == destX || y == destY) {
        // Movimiento recto
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
   
    return false;
}


bool Reina::puedeatacar(int destX, int destY, Pieza* tablero[5][5]) {
    Torre torre(x, y, color);
    Alfil alfil(x, y, color);
    return torre.puedeatacar(destX, destY, tablero) || alfil.puedeatacar(destX, destY, tablero);
}
