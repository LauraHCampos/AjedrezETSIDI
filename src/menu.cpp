#include "menu.h"
#include "freeglut.h"
#include <iostream>
#include "ETSIDI.h"

using namespace std;

EstadoApp estadoActual = MENU_PRINCIPAL;
TipoJuego tipoJuegoSeleccionado;
ModoJuego modoJuegoSeleccionado;
TipoTablero tipoTableroSeleccionado;

struct Boton {
    float x, y, ancho, alto;
    const char* texto;
    void (*accion)();

    void dibujar(float r, float g, float b) {
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING); 

        // Sombra
        glColor3f(
        min(r + 0.2f, 1.0f),            //ponemos min para no pasarle el valor maximo del color (1,0) ya que es el color del boton
        min(g + 0.2f, 1.0f),
        min(b + 0.2f, 1.0f)
        );        
        glBegin(GL_QUADS);
        glVertex2f(x + 0.02f, y - 0.02f);
        glVertex2f(x + ancho + 0.02f, y - 0.02f);
        glVertex2f(x + ancho + 0.02f, y + alto - 0.02f);
        glVertex2f(x + 0.02f, y + alto - 0.02f);
        glEnd();

        // Botón
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + ancho, y);
        glVertex2f(x + ancho, y + alto);
        glVertex2f(x, y + alto);
        glEnd();

        // Texto
        glColor3f(0, 0, 0);
        glRasterPos2f(x + ancho / 4, y + alto / 3);
        const char* c = texto;
        while (*c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
            ++c;
        }

        glEnable(GL_LIGHTING); 
    }

};

void iniciarJuegoVsMaquina() {
    tipoJuegoSeleccionado = VS_MAQUINA;
    estadoActual = MENU_MODO_JUEGO;
    cout << "Modo Jugador vs Máquina (no implementado todavía)" << endl;
}

void iniciarJuegoVsJugador() {
    tipoJuegoSeleccionado = VS_JUGADOR;
    estadoActual = MENU_MODO_JUEGO;
    cout << "Modo Jugador vs Jugador activado" << endl;
}

void salir() {
    exit(0);
}

void iniciarmodo1() {
    modoJuegoSeleccionado = CLASICO;
    estadoActual = MENU_TIPO;
    cout << "Modo clasico activado" << endl;
   
}

void iniciarmodo2() {
    modoJuegoSeleccionado = ETSIDI_;
    estadoActual = MENU_TIPO;
    cout << "Modo ETSIDI activado" << endl;
}

void iniciarmodo3() {
    modoJuegoSeleccionado = REY_PEON;
    estadoActual = MENU_TIPO;
    cout << "Modo Rey Leon activado" << endl;
}

Boton botones[3] = {
    {-0.6f, 0.2f, 1.2f, 0.2f, "1. Jugador vs Maquina", iniciarJuegoVsMaquina},
    {-0.6f, -0.1f, 1.2f, 0.2f, "2. Jugador vs Jugador", iniciarJuegoVsJugador},
    {-0.15f, -0.5f, 0.3f, 0.15f, " Salir", salir}
};

Boton botonesModos[3] = {
    {-0.6f, 0.2f, 1.2f, 0.2f, "      Modo Clasico",iniciarmodo1},
    {-0.6f, -0.1f, 1.2f, 0.2f, "      Modo ETSIDI",iniciarmodo2},
    {-0.6f, -0.4f, 1.2f, 0.2f, "      Modo Rey Leon",iniciarmodo3}
};

Boton botonesTipo[2] = {
    {-0.6f, 0.2f, 1.2f, 0.2f, "      BABY", seleccionarbaby},
    {-0.6f, -0.1f, 1.2f, 0.2f, "      GARDNER", seleccionarGarden}

};



void mostrarMenu() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Proyección centrada (para -1.0 a 1.0)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // sistema de coordenadas de los botones
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 2. Dibujar imagen de fondo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/FondoAjedrez.png").id);
    glDisable(GL_LIGHTING);  // desactivar luz para evitar efectos raros

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); // sin color
    glTexCoord2f(0, 1); glVertex2f(-1.0f, -1.0f); // abajo izquierda
    glTexCoord2f(1, 1); glVertex2f(1.0f, -1.0f);  // abajo derecha
    glTexCoord2f(1, 0); glVertex2f(1.0f, 1.0f);   // arriba derecha
    glTexCoord2f(0, 0); glVertex2f(-1.0f, 1.0f);  // arriba izquierda
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING); 

    // 3. Título con sombra
    glColor3f(0.0f, 0.0f, 0.0f);  // sombra negra
    glRasterPos2f(-0.53f, 0.72f);
    const char* sombra = "       Ajedrez - El Rey Peon";
    for (const char* c = sombra; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    glColor3f(1.0f, 1.0f, 0.6f);  // texto claro
    glRasterPos2f(-0.55f, 0.75f);
    const char* titulo = "       Ajedrez - El Rey Peon";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    // 4. Botones (desactiva textura para evitar que salgan negros)
    glDisable(GL_TEXTURE_2D);
    botones[0].dibujar(0.0f, 0.6f, 0.8f); // azul cielo
    botones[1].dibujar(0.3f, 0.8f, 0.3f); // verde
    botones[2].dibujar(0.8f, 0.2f, 0.2f); // rojo

    glFlush();
}
void mostrarMenuModos() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Proyección centrada
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 2. Fondo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/FondoAjedrez.png").id);
    glDisable(GL_LIGHTING);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 0); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 0); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    // 3. Título del menú
    glColor3f(0.0f, 0.0f, 0.0f);  // sombra negra
    glRasterPos2f(-0.3f, 0.72f);
    const char* sombra = "Selecciona Modo de Juego";
    for (const char* c = sombra; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    glColor3f(1.0f, 1.0f, 0.6f);  // texto claro
    glRasterPos2f(-0.32f, 0.75f);
    const char* titulo = "Selecciona Modo de Juego";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    // 4. Dibujar los 3 botones
    // Botón Modo 1
    botonesModos[0].dibujar(0.0f, 0.6f, 0.8f); // azul cielo
    // Botón Modo 2
    botonesModos[1].dibujar(0.3f, 0.8f, 0.3f); // verde
    // Botón Modo 3
    botonesModos[2].dibujar(0.8f, 0.2f, 0.2f); // rojo

    glFlush();
}

void mostrarMenuTipo() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Proyección centrada
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 2. Fondo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/FondoAjedrez.png").id);
    glDisable(GL_LIGHTING);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1, 0); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0, 0); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    // 3. Título del menú
    glColor3f(0.0f, 0.0f, 0.0f);  // sombra negra
    glRasterPos2f(-0.3f, 0.72f);
    const char* sombra = "Selecciona Tipo de juego:";
    for (const char* c = sombra; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    glColor3f(1.0f, 1.0f, 0.6f);  // texto claro
    glRasterPos2f(-0.32f, 0.75f);
    const char* titulo = "Selecciona Tipo de juego";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    // 4. Dibujar los 2 botones
    // Botón Tipo 1
    botonesTipo[0].dibujar(0.0f, 0.6f, 0.8f); // azul cielo
    // Botón Tipo 2
    botonesTipo[1].dibujar(0.3f, 0.8f, 0.3f); // verde

    glFlush();
}



void clickMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && estadoActual == MENU_PRINCIPAL) {
        float xf = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float yf = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

        for (auto& boton : botones) {
            if (xf >= boton.x && xf <= boton.x + boton.ancho &&
                yf >= boton.y && yf <= boton.y + boton.alto) {
                ETSIDI::play("sonidos/boton_click.wav");
                boton.accion();  // Aquí ejecuta la acción asignada
                glutPostRedisplay();
                return;
            }
        }

    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && estadoActual == MENU_TIPO) {
        float xf = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float yf = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

        for (auto& boton : botonesTipo) {
            if (xf >= boton.x && xf <= boton.x + boton.ancho &&
                yf >= boton.y && yf <= boton.y + boton.alto) {
                ETSIDI::play("sonidos/boton_click.wav");
                boton.accion();  // Aquí ejecuta la acción asignada
                glutPostRedisplay();
                return;
            }
        }

    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && estadoActual == MENU_MODO_JUEGO) {
        float xf = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float yf = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

        for (auto& boton : botonesModos) {
            if (xf >= boton.x && xf <= boton.x + boton.ancho &&
                yf >= boton.y && yf <= boton.y + boton.alto) {
                ETSIDI::play("sonidos/boton_click.wav");
                boton.accion();  // Aquí ejecuta la acción asignada
                glutPostRedisplay();
                return;
            }
        }

    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (estadoActual) {
    case MENU_PRINCIPAL:
        mostrarMenu();  
        break;
    case MENU_MODO_JUEGO:
        mostrarMenuModos();  
        break;

    case MENU_TIPO:
        mostrarMenuTipo();
        break;

    }

    glutSwapBuffers();
}

