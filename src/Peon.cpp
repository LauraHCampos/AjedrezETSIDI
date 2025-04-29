#include <cmath>
#include "Peon.h"

bool Peon::movimientoValido(int destX, int destY, Pieza* tablero[5][5]) 
{
    int direccion = color ? -1 : 1; //se mueven hacia arriba (blanco) abajo(negro)

    if (destX == x + direccion && y == destY && tablero[destX][destY] == nullptr) { //si la casilla esta libre se mueve hacia delante
        return true;
    }
    if (destX == x + direccion && std::abs(destY - y) == 1 && tablero[destX][destY] != nullptr) { //se mueve uno hacia delante y otro a la dch o izqd SOLO en caso de que haya opcion a capturar
        return true;
    }
    return false; //otros movimientos no son validos
}