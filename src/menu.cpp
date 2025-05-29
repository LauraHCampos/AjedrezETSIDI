#include "Menu.h"
#include "freeglut.h"
#include <string>
#include <iostream>
#include "ETSIDI.h"

using namespace std;

void renderTexto(float x, float y, const char* texto) {
    glColor3f(1.0f, 1.0f, 1.0f);  // blanco
    glRasterPos2f(x, y);
    for (const char* c = texto; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

Menu::Menu() {}

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
    /*glColor3f(0.0f, 0.0f, 0.0f);  // sombra negra
    glRasterPos2f(-0.53f, 0.72f);
    const char* sombra = "       Ajedrez - El Rey Peon";
    for (const char* c = sombra; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);*/

    glColor3f(1.0f, 1.0f, 0.6f);  // texto claro
    glRasterPos2f(-0.32f, 0.75f);
    const char* titulo = "AJEDREZ - EL REY PEON";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

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
    /*glColor3f(0.0f, 0.0f, 0.0f);  // sombra negra
    glRasterPos2f(-0.3f, 0.72f);
    const char* sombra = "Selecciona Tipo de Juego";
    for (const char* c = sombra; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);*/

    glColor3f(1.0f, 1.0f, 0.6f);  // texto claro
    glRasterPos2f(-0.32f, 0.75f);
    const char* titulo = "Selecciona Tipo de Juego";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);


}
void mostrarMenuModo() {
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
    /*glColor3f(0.0f, 0.0f, 0.0f);  // sombra negra
    glRasterPos2f(-0.3f, 0.72f);
    const char* sombra = "Selecciona Modo de juego:";
    for (const char* c = sombra; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);*/

    glColor3f(1.0f, 1.0f, 0.6f);  // texto claro
    glRasterPos2f(-0.32f, 0.75f);
    const char* titulo = "Selecciona Modo de juego";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

}
void Menu::render() {
    switch (estadoActual) {
    case MENU_PRINCIPAL:
        mostrarMenu();
        renderTexto(-0.32f, 0.5f, "=== MENU PRINCIPAL ===");
        renderTexto(-0.32f, 0.3f, "1. Un jugador contra maquina");
        renderTexto(-0.32f, 0.1f, "2. Dos jugadores");
        break;
    case MENU_TIPO_AJEDREZ:
        mostrarMenuTipo();
        renderTexto(-0.32f, 0.5f, "=== TIPO DE AJEDREZ ===");
        renderTexto(-0.32f, 0.3f, "1. Ajedrez Clasico");
        renderTexto(-0.32f, 0.1f, "2. Rey Leon");
        renderTexto(-0.32f, -0.1f, "3. ETSIDI");
        break;
    case MENU_MODOS_ESPECIALES:
        mostrarMenuModo();
        renderTexto(-0.32f, 0.5f, "=== MODO ESPECIAL ===");
        renderTexto(-0.32f, 0.3f, "1. Gardner");
        renderTexto(-0.32f, 0.1f, "2. Baby Chess");
        break;
    case MOSTRAR_TABLERO:
        break;
    }
}

void Menu::manejarInput(unsigned char key) {
    switch (estadoActual) {
    case MENU_PRINCIPAL:
        if (key == '1' || key == '2') {
            ETSIDI::play("sonidos/boton_click.wav");
            seleccion1 = key - '0';
            estadoActual = MENU_TIPO_AJEDREZ;
        }
        break;
    case MENU_TIPO_AJEDREZ:
        if (key >= '1' && key <= '3') {
            ETSIDI::play("sonidos/boton_click.wav");
            seleccion2 = key - '0';

            if (seleccion2 == 2)
            {
                cout << "Peon blanco: Timon\t\t\tPeon negro: Hienas" << endl;
                cout << "Alfil blanco: Rafiki\t\t\tAlfil negro: Nuka" << endl;
                cout << "Caballo blanco: Pumba\t\t\tCaballo negro: Kovu" << endl;
                cout << "Rey blanco: Simba\t\t\tRey negro: Scar" << endl;
                cout << "Reina blanca: Nala\t\t\tReina negra: Zira" << endl;
                cout << "Torre blanca: Zazu\t\t\tTorre negra: Vitani\n\n" << endl;
            }

            estadoActual = MENU_MODOS_ESPECIALES;
        }
        break;
    case MENU_MODOS_ESPECIALES:
        if (key == '1' || key == '2') {
            ETSIDI::play("sonidos/boton_click.wav");
            seleccion3 = key - '0';
            juegoIniciado = true;
            estadoActual = MOSTRAR_TABLERO;
        }
        break;
    case MOSTRAR_TABLERO:
        if (key == 'r') {
            ETSIDI::play("sonidos/boton_click.wav");
            reiniciar();
        }

        break;
    }
}

bool Menu::haIniciadoJuego() const {
    return juegoIniciado;
}

EstadoMenu Menu::obtenerEstado() const {
    return estadoActual;
}

int Menu::getSeleccion1() const { return seleccion1; }
int Menu::getSeleccion2() const { return seleccion2; }
int Menu::getSeleccion3() const { return seleccion3; }

void Menu::reiniciar() {
    seleccion1 = 0;
    seleccion2 = 0;
    seleccion3 = 0;
    estadoActual = MENU_PRINCIPAL;
    juegoIniciado = false;
}
