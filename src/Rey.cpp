#include "Rey.h"
#include <cmath>


bool Rey::movimientoValido(int destX, int destY, Pieza* tablero[5][5])
{
    if (tablero[destX][destY] && tablero[destX][destY]->getTipo() == "Rey")
    {
        return false; // no se puede capturar al rey
    }

    int dx = std::abs(destX - x); //cambio en x
    int dy = std::abs(destY - y); //cambio en y
    if (dx > 1 || dy > 1)
        return false;

    // Simula el movimiento para ver si quedaría amenazado
    Pieza* destino = tablero[destX][destY];
    tablero[destX][destY] = this;
    tablero[x][y] = nullptr;

    bool enPeligro = false;
    for (int i = 0; i < 5 && !enPeligro; ++i) {
        for (int j = 0; j < 5 && !enPeligro; ++j) {
            Pieza* p = tablero[i][j];
            if (p && p->getColor() != color && p->getTipo() != "Rey") {
                if (p->puedeatacar(destX, destY, tablero)) {
                    enPeligro = true;
                }
            }
        }
    }

    // Revertir el movimiento simulado
    tablero[x][y] = this;
    tablero[destX][destY] = destino;

    if (enPeligro)
        return false;

    return true;
}


bool Rey::puedeatacar(int destX, int destY, Pieza* tablero[5][5]){
    int dx = std::abs(destX - x); //cambio en x
    int dy = std::abs(destY - y); //cambio en y
    return dx <= 1 && dy <= 1 && (dx != 0 || dy != 0); //valido si se mueve una casilla en cualquier direccion
}
