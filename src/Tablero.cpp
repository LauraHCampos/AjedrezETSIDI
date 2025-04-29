#include "Tablero.h"
#include "C:\Users\Laura\OneDrive\Escritorio\PruebaAna\freeglut.h"
#include <iostream>

Tablero::Tablero() : turnoBlancas(true), seleccionX(-1), seleccionY(-1) //constructor tablero con inicializacion del turno blanco (empiezan ellas) 
{
    for (int i = 0; i < 5; ++i) //bucle
        for (int j = 0; j < 5; ++j) //bucle dentro de bucle para la matriz del tablero
            casillas[i][j] = nullptr; //se inicializan en 0
    
    //posiciones iniciales de las piezas blancas
    casillas[4][0] = new Torre(4, 0, true);
    casillas[4][1] = new Caballo(4, 1, true);
    casillas[4][2] = new Rey(4, 2, true);
    casillas[4][3] = new Alfil(4, 3, true);
    casillas[4][4] = new Reina(4, 4, true);
    for (int j = 0; j < 5; j++)
        casillas[3][j] = new Peon(3, j, true);

    //posiciones iniciales de las piezas negras
    casillas[0][0] = new Reina(0, 0, false);
    casillas[0][1] = new Alfil(0, 1, false);
    casillas[0][2] = new Rey(0, 2, false);
    casillas[0][3] = new Caballo(0, 3, false);
    casillas[0][4] = new Torre(0, 4, false);
    for (int j = 0; j < 5; j++)
        casillas[1][j] = new Peon(1, j, false);
}

Tablero::~Tablero() //destructor (libera memoria)
{
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            delete casillas[i][j];
}

void Tablero::dibujar() //dibuja el tablero y las piezas
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) { //recorrer casillas 
            if ((i + j) % 2 == 0) //si es par imprime la casilla de un color claro
                glColor3f(0.9f, 0.9f, 0.9f);
            else //si no en un color oscuro
                glColor3f(0.3f, 0.3f, 0.3f);

            //dibujo de los cuadrados de las casillas
            glBegin(GL_QUADS);
            glVertex2f(j, i);
            glVertex2f(j + 1, i);
            glVertex2f(j + 1, i + 1);
            glVertex2f(j, i + 1);
            glEnd();

            if (casillas[i][j]) {
                //color de la spiezas (las blancas enr rojo y las negras en azul)
                glColor3f(casillas[i][j]->getColor() ? 1.0f : 0.0f, 0.0f, casillas[i][j]->getColor() ? 0.0f : 1.0f);
                glRasterPos2f(j + 0.4f, i + 0.4f); //posicion texto
                //dibuja la inicial de cada tipo de pieza
                string tipo = casillas[i][j]->getTipo();
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tipo[0]);
            }
        }
    }
}

void Tablero::click(float x, float y) 
{
    int j = static_cast<int>(x);
    int i = static_cast<int>(y);

    if (seleccionX == -1) //si no hay pieza seleccionada 
    {
        if (casillas[i][j] && casillas[i][j]->getColor() == turnoBlancas) //si es el turno correspondiente
        {
            seleccionX = i;
            seleccionY = j;
            //se selecciona la pieza
        }
    }

    else //si ya hay una seleccionada
    {
        if (casillas[seleccionX][seleccionY]->movimientoValido(i, j, casillas)) //si el movimiento es valido
        {
            delete casillas[i][j]; //elimina pieza que habia en la posicion final (en caso de captura)
            casillas[i][j] = casillas[seleccionX][seleccionY]; // mueve la pieza a la nueva posicion
            casillas[seleccionX][seleccionY] = nullptr; //elimina la pieza que has seleccionado de su posicion anterior 
            casillas[i][j]->setPos(i, j); //actualiza su nueva posicion
            turnoBlancas = !turnoBlancas; //cambio de turno
        }
        seleccionX = seleccionY = -1; //deja de seleccionar
    }
}
