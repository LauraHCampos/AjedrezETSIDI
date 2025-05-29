#include "Tablero.h"
#include "freeglut.h"
#include <iostream>
#include <vector>
#include "ETSIDI.h"

Tablero::Tablero(int s3) : turnoBlancas(true), seleccionX(-1), seleccionY(-1) //constructor tablero con inicializacion del turno blanco (empiezan ellas) 
{
    for (int i = 0; i < 5; ++i) //bucle
        for (int j = 0; j < 5; ++j) //bucle dentro de bucle para la matriz del tablero
            casillas[i][j] = nullptr; //se inicializan en 0

    //NUEVO
  
    if (s3 == 2) //BABY
    {

        //posiciones iniciales de las piezas blancas
        casillas[4][0] = new Torre(4, 0, true);
        casillas[4][1] = new Caballo(4, 1, true);
        casillas[4][2] = new Alfil(4, 2, true);
        casillas[4][3] = new Reina(4, 3, true);
        casillas[4][4] = new Rey(4, 4, true);

        for (int j = 0; j < 5; j++)
            casillas[3][j] = new Peon(3, j, true);

        //posiciones iniciales de las piezas negras
        casillas[0][0] = new Rey(0, 0, false);
        casillas[0][1] = new Reina(0, 1, false);
        casillas[0][2] = new Alfil(0, 2, false);
        casillas[0][3] = new Caballo(0, 3, false);
        casillas[0][4] = new Torre(0, 4, false);

        for (int j = 0; j < 5; j++)
            casillas[1][j] = new Peon(1, j, false);
    }

    else if (s3 == 1) //GARDNER
    {
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
    }

}

Tablero::~Tablero() //destructor (libera memoria)
{
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            delete casillas[i][j];
}

void Tablero::dibujar(int s2) //dibuja el tablero y las piezas
{

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) { //recorrer casillas 
           
           
            if ((i + j) % 2 == 0) //si es par imprime la casilla de un color claro
                glColor3f(0.82f, 0.729f, 0.647f); 
            else //si no en un color oscuro
                glColor3f(0.694f, 0.47f, 0.329f); 

            //Colores a los movimientos 

            //pieza seleccionada. Morados
            if (i == seleccionX && j == seleccionY)
            {
                if (turnoBlancas) //si es blanca imprime la casilla seleccionada de un color morado claro
                    pintarmovimiento(0.653f, 0.625f, 0.77f, i, j);

                else //si es negra imprime la casilla seleccionada de un color morado oscuro
                    pintarmovimiento(0.3f, 0.1f, 0.4f, i, j);
                    
            }
            
            //posibles movimientos. Verdes
            else if (seleccionX != -1 && seleccionY != -1 && casillas[seleccionX][seleccionY] && casillas[seleccionX][seleccionY]->movimientoValido(i, j, casillas))
            {
                if (turnoBlancas) //si es blanca imprime la casilla de movimientos de un color verde claro
                    pintarmovimiento(0.615f, 0.757f, 0.514f, i, j);

                else //si es negra imprime la casilla de movimientos de un color verde oscuro
                    pintarmovimiento(0.17f, 0.4f, 0.3f, i, j);

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

                //PONER FOTOS 
                if (s2 == 1) //MODO CLASICO
                {
                    string tipo = casillas[i][j]->getTipo();
                    bool color = casillas[i][j]->getColor();

                    if (color == 1) // piezas blancas
                    {
                        if (tipo == "Peon")
                            imprimirTextura("imagenes/pawnwhite.png", j, i);

                        else if (tipo == "Alfil")
                            imprimirTextura("imagenes/bishopwhite.png", j, i);


                        else if (tipo == "Caballo")
                            imprimirTextura("imagenes/horsewhite.png", j, i);

                        else if (tipo == "Queen")
                            imprimirTextura("imagenes/queenwhite.png", j, i);

                        else if (tipo == "Rey")
                            imprimirTextura("imagenes/kingwhite.png", j, i);

                        else if (tipo == "Torre")
                            imprimirTextura("imagenes/towerwhite.png", j, i);

                    }

                    if (color == 0) //piezas negras
                    {
                        if (tipo == "Peon")
                            imprimirTextura("imagenes/pawnblack.png", j, i);

                        else if (tipo == "Alfil")
                            imprimirTextura("imagenes/bishopblack.png", j, i);

                        else if (tipo == "Caballo")
                            imprimirTextura("imagenes/horseblack.png", j, i);

                        else if (tipo == "Queen")
                            imprimirTextura("imagenes/queenblack.png", j, i);

                        else if (tipo == "Rey")
                            imprimirTextura("imagenes/kingblack.png", j, i);

                        else if (tipo == "Torre")
                            imprimirTextura("imagenes/towerblack.png", j, i);

                    }

                }

                else if (s2 == 2) //MODO REY LEON
                {
                    string tipo = casillas[i][j]->getTipo();
                    bool color = casillas[i][j]->getColor();

                    if (color == 1) // piezas blancas
                    {
                        if (tipo == "Peon")
                            imprimirTextura("imagenes/timon.png", j, i);

                        else if (tipo == "Alfil")
                            imprimirTextura("imagenes/rafiki.png", j, i);

                        else if (tipo == "Caballo")
                            imprimirTextura("imagenes/pumba.png", j, i);

                        else if (tipo == "Queen")
                            imprimirTextura("imagenes/nala.png", j, i);

                        else if (tipo == "Rey")
                            imprimirTextura("imagenes/simba1.png", j, i);

                        else if (tipo == "Torre")
                            imprimirTextura("imagenes/zazu.png", j, i);

                    }

                    if (color == 0) //piezas negras
                    {
                        if (tipo == "Peon")
                            imprimirTextura("imagenes/hyena.png", j, i);

                        else if (tipo == "Alfil")
                            imprimirTextura("imagenes/nuka.png", j, i);

                        else if (tipo == "Caballo")
                            imprimirTextura("imagenes/kovu.png", j, i);

                        else if (tipo == "Queen")
                            imprimirTextura("imagenes/zira.png", j, i);

                        else if (tipo == "Rey")
                            imprimirTextura("imagenes/scar.png", j, i);

                        else if (tipo == "Torre")
                            imprimirTextura("imagenes/vitani.png", j, i);

                    }

                }

                else if (s2 == 3) //MODO ETSIDI
                {

                    string tipo = casillas[i][j]->getTipo();
                    bool color = casillas[i][j]->getColor();

                    if (color == 1) // piezas blancas
                    {
                        if (tipo == "Peon")
                            imprimirTextura("imagenes/etsidipawnwhite.png", j, i);

                        else if (tipo == "Alfil")
                            imprimirTextura("imagenes/etsidibishopwhite.png", j, i);

                        else if (tipo == "Caballo")
                            imprimirTextura("imagenes/etsidihorsewhite.png", j, i);

                        else if (tipo == "Queen")
                            imprimirTextura("imagenes/etsidiqueenwhite.png", j, i);

                        else if (tipo == "Rey")
                            imprimirTextura("imagenes/etsidikingwhite.png", j, i);

                        else if (tipo == "Torre")
                            imprimirTextura("imagenes/etsiditowerwhite.png", j, i);

                    }

                    if (color == 0) //piezas negras
                    {
                        if (tipo == "Peon")
                            imprimirTextura("imagenes/etsidipawnblack.png", j, i);

                        else if (tipo == "Alfil")
                            imprimirTextura("imagenes/etsidibishopblack.png", j, i);

                        else if (tipo == "Caballo")
                            imprimirTextura("imagenes/etsidihorseblack.png", j, i);

                        else if (tipo == "Queen")
                            imprimirTextura("imagenes/etsidiqueenblack.png", j, i);

                        else if (tipo == "Rey")
                            imprimirTextura("imagenes/etsidikingblack.png", j, i);

                        else if (tipo == "Torre")
                            imprimirTextura("imagenes/etsiditowerblack.png", j, i);

                    }
                }

            }
        }
    }
}

void Tablero::imprimirTextura(const std::string& ruta, int x, int y) 
{
    
    auto tex = ETSIDI::getTexture(ruta.c_str());

    if (tex.id == 0) {
        std::cerr << "No se pudo cargar la textura: " << ruta << std::endl;
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, tex.id);
    
    if ((x + y) % 2 == 0) //si es par imprime la casilla de un color claro
    {
        glColor3f(0.82f, 0.729f, 0.647f); // Este es el marron claro   

    }
    else //si no en un color oscuro
    {
        glColor3f(0.694f, 0.47f, 0.329f); //marron oscuro
    }
    
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(x, y, 0.1f);
    glTexCoord2f(1, 0); glVertex3f(x + 1, y, 0.1f);
    glTexCoord2f(1, 1); glVertex3f(x + 1, y + 1, 0.1f);
    glTexCoord2f(0, 1); glVertex3f(x, y + 1, 0.1f);
    glEnd();

}

void Tablero::pintarmovimiento(float r, float g, float b, int i, int j){
    glColor3f(r, g, b); //
    glLineWidth(10.0f); // más grueso para que se note
    glBegin(GL_LINE_LOOP);
    glVertex2f(j, i);
    glVertex2f(j + 1, i);
    glVertex2f(j + 1, i + 1);
    glVertex2f(j, i + 1);
    glEnd();
    glLineWidth(1.0f); // restaurar grosor
}

EstadoJuego Tablero::click(float x, float y, int s1)
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
                ETSIDI::play("sonidos/Checkmate.mp3");

                if (turnoBlancas)
                    cout << "\t\t\tRey negro en Jaque Mate. Ganan blancas. Pulse r para volver al menu inicial" << endl;
                else
                    cout << "Rey blanco en Jaque Mate. Ganan negras. Pulse r para volver al menu inicial" << endl;

                return JAQUE_MATE;
            }

            if (estaEnJaque(!turnoBlancas))
            {

                if (turnoBlancas)
                    cout << "\t\t\tRey negro en Jaque" << endl;
                else
                    cout << "Rey blanco en Jaque" << endl;
                // IF 2 JUGADORES             
                if (s1 == 2)
                    turnoBlancas = !turnoBlancas; //cambio de turno

                //IF IA
                if (s1 == 1)
                {
                    turnoBlancas = false;
                    moverIA(); // Llama a la IA para que juegue su turno negro
                }


                return JAQUE;
            }

            else
            { 

                if (turnoBlancas)
                    cout << "\t\t\tRey negro en Normal" << endl;
                else
                    cout << "Rey blanco en Normal" << endl;

                //IF 2 JUGADORES
                if (s1 == 2)
                    turnoBlancas = !turnoBlancas; //cambio de turno

                //IF IA
                if (s1 == 1)
                {
                    turnoBlancas = false;
                    moverIA(); // Llama a la IA para que juegue su turno negro
                }

                return NORMAL;
            }
        }
        else {
            seleccionX = seleccionY = -1; //deja de seleccionar
        }

    }
    return NORMAL;
    
}


//HAY CAMBIOS DE LO DE PUEDEATACAR
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

//NUEVO

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
        std::cout << "La IA no tiene movimientos legales. Ganan blancas. Pulse r para volver al menu inicial" << std::endl;
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
        ETSIDI::play("sonidos/Checkmate.mp3");
        cout << "Rey blanco en Jaque Mate. Ganan negras. Pulse r para volver al menu inicial" << endl;
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
