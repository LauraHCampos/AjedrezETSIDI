#include "menu.h"
#include "freeglut.h"
#include <iostream>

using namespace std;

EstadoApp estadoActual = MENU_PRINCIPAL;

struct Boton {                  //los 3 botones que hay en el menu principal, cajitas
    float x, y, ancho, alto;    //coordenada izquierda del boton (x), derecha(y); cuanto ocupa el boton horizontalmente(ancho) y verticalmente (alto)
    const char* texto;          //por ejemplo Jugador vs Maquina" es el valor que se guarda en const char* texto
    void (*accion)();           //puntero a funcion, cuando hacemos click en el boton, ejecuta accion

    void dibujar(float r, float g, float b) {
        // Sombra,      Dibuja sombras en cada boton
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
        glColor3f(1, 1, 1);
        glRasterPos2f(x + ancho / 4, y + alto / 3);
        const char* c = texto;
        while (*c) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
            ++c;
        }
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
    {-0.5f, 0.2f, 1.0f, 0.2f, "1 Jugador vs Maquina", iniciarJuegoVsMaquina},
    {-0.5f, -0.1f, 1.0f, 0.2f, "2 Jugador vs Jugador", iniciarJuegoVsJugador},
    {-0.3f, -0.5f, 0.6f, 0.15f, "Salir", salir}
};

void mostrarMenu() {
    // Fondo tipo "gradiente simulado"
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // base azul oscuro
    glClear(GL_COLOR_BUFFER_BIT);

    // Título con sombra
    glColor3f(0.96f, 0.96f, 0.86f);
    glRasterPos2f(-0.53f, 0.72f);
    const char* sombra = "Ajedrez - El Rey Peon";
    while (*sombra) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *sombra);
        sombra++;
    }

    glColor3f(1, 0.8f, 0.5f);
    glRasterPos2f(-0.55f, 0.75f);
    const char* titulo = "Ajedrez - El Rey Peon";
    while (*titulo) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *titulo);
        titulo++;
    }

    // Botones con diferentes colores llamativos
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