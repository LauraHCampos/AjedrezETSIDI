#include "Tablero.h"
#include "freeglut.h"
#include <iostream>
#include <vector>

Tablero::Tablero() : turnoBlancas(true), seleccionX(-1), seleccionY(-1) //constructor tablero con inicializacion del turno blanco (empiezan ellas) 
{
    for (int i = 0; i < 5; ++i) //bucle
        for (int j = 0; j < 5; ++j) //bucle dentro de bucle para la matriz del tablero
            casillas[i][j] = nullptr; //se inicializan en 0


            //IF BABY
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


    //IF GARDNER
    /*
    // Piezas negras (fila 0)
    casillas[0][0] = new Torre(0, 0, false);
    casillas[0][1] = new Caballo(0, 1, false);
    casillas[0][2] = new Alfil(0, 2, false);
    casillas[0][3] = new Reina(0, 3, false);
    casillas[0][4] = new Rey(0, 4, false);

    // Peones negros (fila 1)
    for (int j = 0; j < 5; ++j)
        casillas[1][j] = new Peon(1, j, false);

    // Peones blancos (fila 3)
    for (int j = 0; j < 5; ++j)
        casillas[3][j] = new Peon(3, j, true);

    // Piezas blancas (fila 4)
    casillas[4][0] = new Torre(4, 0, true);
    casillas[4][1] = new Caballo(4, 1, true);
    casillas[4][2] = new Alfil(4, 2, true);
    casillas[4][3] = new Reina(4, 3, true);
    casillas[4][4] = new Rey(4, 4, true);
    */

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
                glColor3f(0.82f, 0.729f, 0.647f); //glColor3f(0.9f, 0.9f, 0.9f);
            else //si no en un color oscuro
                glColor3f(0.1804f, 0.129f, 0.0902f); //glColor3f(0.3f, 0.3f, 0.3f);

            //Colores a los movimientos 

            if (i == seleccionX && j == seleccionY)
            {
                if (turnoBlancas) //si es blanca imprime la casilla seleccionada de un color morado claro
                    glColor3f(0.653f, 0.625f, 0.77f);
                else //si es negra imprime la casilla seleccionada de un color morado oscuro
                    glColor3f(0.3f, 0.1f, 0.4f);
            }
            
            else if (seleccionX != -1 && seleccionY != -1 && casillas[seleccionX][seleccionY] && casillas[seleccionX][seleccionY]->movimientoValido(i, j, casillas))
            {
                if (turnoBlancas) //si es blanca imprime la casilla seleccionada de un color verde claro
                    glColor3f(0.615f, 0.757f, 0.514f); //glColor3f(0.6f, 0.8f, 0.7f);
                else //si es negra imprime la casilla seleccionada de un color verde oscuro
                    glColor3f(0.17f, 0.4f, 0.3f); //glColor3f(0.17f, 0.4f, 0.3f);
            }

            //dibujo de los cuadrados de las casillas
            glBegin(GL_QUADS);
            glVertex2f(j, i);
            glVertex2f(j + 1, i);
            glVertex2f(j + 1, i + 1);
            glVertex2f(j, i + 1);
            glEnd();

            //dibujo de lineas en los cuadrados de las casillas 
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINE_LOOP);
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

EstadoJuego Tablero::click(float x, float y)
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

            if (turnoBlancas)
                std::cout << "\t\t\tMueve " << casillas[i][j]->getTipo() <<" blanco de (" << seleccionX << ", " << seleccionY << ") a(" << i << ", " << j << ")\n";
            else
                std::cout << "Mueve " << casillas[i][j]->getTipo() << " negro de (" << seleccionX << "," << seleccionY << ") a (" << i << "," << j << ")\n";
            //turnoBlancas = !turnoBlancas; //cambio de turno
            seleccionX = seleccionY = -1; //deja de seleccionar
           

            if (esJaqueMate(!turnoBlancas))
            {

                if (turnoBlancas)
                    cout << "\t\t\tRey negro en Jaque Mate. Ganan blancas" << endl;
                else
                    cout << "Rey blanco en Jaque Mate. Ganan negras" << endl;

                return JAQUE_MATE;
            }

            if (estaEnJaque(!turnoBlancas))
            {

                if (turnoBlancas)
                    cout << "\t\t\tRey negro en Jaque" << endl;
                else
                    cout << "Rey blanco en Jaque" << endl;
                // IF 2 JUGADORES
                //turnoBlancas = !turnoBlancas; //cambio de turno

                //IF IA
                turnoBlancas = false;
                moverIA(); // Llama a la IA para que juegue su turno negro

                return JAQUE;
            }

            else
            { 

                if (turnoBlancas)
                    cout << "\t\t\tRey negro en Normal" << endl;
                else
                    cout << "Rey blanco en Normal" << endl;

                // IF 2 JUGADORES
                //turnoBlancas = !turnoBlancas; //cambio de turno

                //IF IA
                turnoBlancas = false;
                moverIA(); // Llama a la IA para que juegue su turno negro

                return NORMAL;
            }
        }
        else {
            seleccionX = seleccionY = -1; //deja de seleccionar
        }

    }
    return NORMAL;
    
}

bool Tablero::estaEnJaque(bool turnoBlanco) {// Devuelve true si el rey del jugador en turno está amenazado
    int reyX = -1, reyY = -1;

    // Encontrar al rey del jugador actual
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) //recorriendo el tablero 
        {
            Pieza* p = casillas[i][j];
            if (p && p->getTipo() == "Rey" && p->getColor() == turnoBlanco) // si es el rey y es la pieza blanca
            {
                reyX = i; //guarda en reyX la posicion de i
                reyY = j; //guarda en reyY la posicion de j
                //posicion del rey
            }
        }
    }

    if (reyX == -1 || reyY == -1) return false; //valores no validos

    // Revisar si alguna pieza enemiga puede atacarlo
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) { //recorre el tablero
            Pieza* p = casillas[i][j];
            if (p && p->getColor() != turnoBlanco) //si es del turno opuesto
            {
                if (p->puedeatacar(reyX, reyY, casillas)) //si se puede mover a la casilla en la que esta el rey
                    return true; //esta en jaque 
            }
        }
    }

    return false; 
}


bool Tablero::esJaqueMate(bool turnoBlanco) {
    if (!estaEnJaque(turnoBlanco)) return false; //si no esta en jaque no puede hacer jaque_mate

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) { //recorriendo el tablero 
            Pieza* p = casillas[i][j];
            if (p && p->getColor() == turnoBlanco) { //si hay una pieza y es del turno correspondiente 
                int fromX = i, fromY = j; //se guarda la posicion de la pieza

                for (int x = 0; x < 5; ++x) {
                    for (int y = 0; y < 5; ++y) { //vuelve a recorrer el tablero 
                        if (p->puedeatacar(x, y, casillas)) { //si puede moverse 
                            // Simula el posible movimiento
                            Pieza* destino = casillas[x][y];
                            casillas[x][y] = p;
                            casillas[fromX][fromY] = nullptr;
                            p->setPos(x, y); //actualiza la posicion interna

                            // Buscar la nueva posición del rey tras mover
                            int reyX = -1, reyY = -1;
                            if (p->getTipo() == "Rey") { //si la pieza que se mueve es el rey 
                                // guarda su nueva posicion
                                reyX = x; 
                                reyY = y;
                            }
                            else { //si no lo fuera
                                for (int a = 0; a < 5; ++a) {
                                    for (int b = 0; b < 5; ++b) { //se busca al rey por el tablero
                                        Pieza* r = casillas[a][b];
                                        if (r && r->getTipo() == "Rey" && r->getColor() == turnoBlanco) {
                                            //guarda su posicion
                                            reyX = a;
                                            reyY = b;
                                        }
                                    }
                                }
                            }

                            // Comprobar si el rey sigue en jaque
                            bool sigueEnJaque = false; //inicializamos la variable a false
                            for (int a = 0; a < 5 && !sigueEnJaque; ++a) {
                                for (int b = 0; b < 5 && !sigueEnJaque; ++b) { //recorriendo el tablero
                                    Pieza* atacante = casillas[a][b]; 
                                    if (atacante && atacante->getColor() != turnoBlanco && atacante->puedeatacar(reyX, reyY, casillas)) { //si hay una pieza, del color contrario y puede atacar al rey
                                        sigueEnJaque = true; //sigue en jaque (posible jaque_mate)
                                    }
                                }
                            }

                            // Deshacer el movimiento que hemos simulado 
                            casillas[fromX][fromY] = p;
                            casillas[x][y] = destino;
                            p->setPos(fromX, fromY); //vuelve a la posicion en la que estaba antes de la simulacion y se vuelve a repetir el bucle hasta comprobar todos los movimientos posibles

                            if (!sigueEnJaque) { //logra salir del estado jaque 
                                return false; // hay al menos un movimiento legal
                            }
                        }
                    }
                }
            }
        }
    }

    return true; // No hay movimientos legales para que el rey escape del jaque, por lo que es jaque mate
}

int Tablero::evaluarTablero() {
    int valor = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            Pieza* p = casillas[i][j];
            if (p) {
                int v = p->getValor();
                valor += (p->getColor() ? v : -v); // blancas +, negras -
            }
        }
    }
    return valor;
}

EstadoJuego Tablero::moverIA() {
    std::vector<Movimiento> movimientosPosibles;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            Pieza* p = casillas[i][j];
            if (p && !p->getColor()) { // Si es negra
                for (int x = 0; x < 5; ++x) {
                    for (int y = 0; y < 5; ++y) {
                        if (p->movimientoValido(x, y, casillas)) {
                            // Simular
                            Pieza* destino = casillas[x][y];
                            casillas[x][y] = p;
                            casillas[i][j] = nullptr;
                            p->setPos(x, y);

                            bool autoJaque = estaEnJaque(false);

                            // Revertir
                            casillas[i][j] = p;
                            casillas[x][y] = destino;
                            p->setPos(i, j);

                            if (!autoJaque) {
                                movimientosPosibles.push_back({ i, j, x, y });
                            }
                        }
                    }
                }
            }
        }
    }

    if (movimientosPosibles.empty()) {
        std::cout << "La IA no tiene movimientos legales. Ganan blancas" << std::endl;
        return JAQUE_MATE;
    }

    // Elegir el mejor movimiento
    int mejorPuntaje = INT_MAX;
    Movimiento mejorMovimiento;

    for (const Movimiento& mov : movimientosPosibles) {
        int i = mov.origenX;
        int j = mov.origenY;
        int x = mov.destinoX;
        int y = mov.destinoY;

        Pieza* p = casillas[i][j];
        Pieza* destino = casillas[x][y];

        casillas[x][y] = p;
        casillas[i][j] = nullptr;
        p->setPos(x, y);

        int puntaje = evaluarTablero();

        casillas[i][j] = p;
        casillas[x][y] = destino;
        p->setPos(i, j);

        if (puntaje < mejorPuntaje) {
            mejorPuntaje = puntaje;
            mejorMovimiento = mov;
        }
    }

    // Ejecutar el mejor movimiento
    int i = mejorMovimiento.origenX;
    int j = mejorMovimiento.origenY;
    int x = mejorMovimiento.destinoX;
    int y = mejorMovimiento.destinoY;

    Pieza* p = casillas[i][j];
    Pieza* destino = casillas[x][y];
    delete destino;

    casillas[x][y] = p;
    casillas[i][j] = nullptr;
    p->setPos(x, y);

    turnoBlancas = true;
    std::cout << "IA mueve " << casillas[x][y]->getTipo() << " negro de (" << i << "," << j << ") a (" << x << "," << y << ")\n";
    if (esJaqueMate(turnoBlancas))
    {
        cout << "Rey blanco en Jaque Mate. Ganan negras" << endl;
        return JAQUE_MATE;
    }

    else if (estaEnJaque(turnoBlancas))
    {
        cout << "Rey blanco en Jaque" << endl;
        return JAQUE;
    }

    else
    {
        cout << "Rey blanco en Normal" << endl;
        return NORMAL;
    }
}
