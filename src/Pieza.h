#pragma once

#include <string>
using namespace std;

class Pieza {
protected:
    int x, y; // coordenadas de la pieza 
    bool color; // true = blancas, false = negras

public:
    Pieza(int x, int y, bool color) : x(x), y(y), color(color) {} //constructor generico
    virtual ~Pieza() {} // destructor generico
    
    virtual bool movimientoValido(int destX, int destY, class Pieza* tablero[5][5]) = 0;//devuelve si el movimiento es valido
    
    bool getColor() { return color; } //devuelve el color de la pieza
    void setPos(int nx, int ny) { x = nx; y = ny; } //define la posicion de la pieza
    int getX() { return x; } //devuelve la coordenada x de la pieza
    int getY() { return y; } //devuelve la coordenada y de la pieza
    virtual string getTipo() = 0; //devuelve el tipo de pieza (virtual puro)
};



