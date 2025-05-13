#include "menu.h"
#include "freeglut.h"
#include <iostream>
#include "ETSIDI.h"

using namespace std;

EstadoApp estadoActual = MENU_PRINCIPAL;

struct Boton {
    float x, y, ancho, alto;
    const char* texto;
    void (*accion)();

   
    void dibujar(float r, float g, float b) {
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING); // <--- Esto es CLAVE para que los colores planos funcionen

        // Sombra
        glColor3f(0.2f, 0.2f, 0.2f);
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

        glEnable(GL_LIGHTING); // Vuelve a activar iluminación si se usará después
    }

};

void iniciarJuegoVsMaquina() {
    estadoActual = JUEGO_VS_MAQUINA;
    cout << "Modo Jugador vs Máquina (no implementado todavía)" << endl;
}

void iniciarJuegoVsJugador() {
    estadoActual = JUEGO_VS_JUGADOR;
    cout << "Modo Jugador vs Jugador activado" << endl;
}

void salir() {
    exit(0);
}

Boton botones[3] = {
    {-0.6f, 0.2f, 1.2f, 0.2f, "1. Jugador vs Maquina", iniciarJuegoVsMaquina},
    {-0.6f, -0.1f, 1.2f, 0.2f, "2. Jugador vs Jugador", iniciarJuegoVsJugador},
    {-0.15f, -0.5f, 0.3f, 0.15f, " Salir", salir}
};


void mostrarMenu() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Proyección centrada (para -1.0 a 1.0)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // sistema de coordenadas usado en los botones
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 2. Dibujar imagen de fondo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/FondoAjedrez.png").id);
    glDisable(GL_LIGHTING);  // desactivar luz para evitar efectos raros

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); // sin tinte
    glTexCoord2f(0, 1); glVertex2f(-1.0f, -1.0f); // abajo izquierda
    glTexCoord2f(1, 1); glVertex2f(1.0f, -1.0f);  // abajo derecha
    glTexCoord2f(1, 0); glVertex2f(1.0f, 1.0f);   // arriba derecha
    glTexCoord2f(0, 0); glVertex2f(-1.0f, 1.0f);  // arriba izquierda
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);  // opcional si usarás luz luego

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



void clickMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && estadoActual == MENU_PRINCIPAL) {
        float xf = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float yf = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

        for (auto& boton : botones) {
            if (xf >= boton.x && xf <= boton.x + boton.ancho &&
                yf >= boton.y && yf <= boton.y + boton.alto) {
                boton.accion();
                glutPostRedisplay();
                return;
            }
        }
    }
}

void display() {
    if (estadoActual == MENU_PRINCIPAL)
        mostrarMenu();
    else {
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2f(-0.3f, 0);
        const char* mensaje = "(El juego ha comenzado)";
        while (*mensaje) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *mensaje);
            ++mensaje;
        }
        glFlush();
    }
    glutSwapBuffers();
}
