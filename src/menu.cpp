#include "Menu.h"
#include "freeglut.h"
#include <string>
#include <iostream>


using namespace std;

void renderTexto(float x, float y, const char* texto) {
    glColor3f(1.0f, 1.0f, 1.0f);  // blanco
    glRasterPos2f(x, y);
    for (const char* c = texto; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

Menu::Menu() {}

void Menu::render() {
    switch (estadoActual) {
    case MENU_PRINCIPAL:
        renderTexto(-0.8f, 0.3f, "=== MENU PRINCIPAL ===");
        renderTexto(-0.8f, 0.1f, "1. Un jugador contra maquina");
        renderTexto(-0.8f, -0.1f, "2. Dos jugadores");
        break;
    case MENU_TIPO_AJEDREZ:
        renderTexto(-0.8f, 0.3f, "=== TIPO DE AJEDREZ ===");
        renderTexto(-0.8f, 0.1f, "1. Ajedrez Clasico");
        renderTexto(-0.8f, -0.1f, "2. Rey Leon");
        renderTexto(-0.8f, -0.3f, "3. ETSIDI");
        break;
    case MENU_MODOS_ESPECIALES:
        renderTexto(-0.8f, 0.3f, "=== MODO ESPECIAL ===");
        renderTexto(-0.8f, 0.1f, "1. Gardner");
        renderTexto(-0.8f, -0.1f, "2. Baby Chess");
        break;
    case MOSTRAR_TABLERO:
        break;
    }
}

void Menu::manejarInput(unsigned char key) {
    switch (estadoActual) {
    case MENU_PRINCIPAL:
        if (key == '1' || key == '2') {
            seleccion1 = key - '0';
            estadoActual = MENU_TIPO_AJEDREZ;
        }
        break;
    case MENU_TIPO_AJEDREZ:
        if (key >= '1' && key <= '3') {
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
            seleccion3 = key - '0';
            juegoIniciado = true;
            estadoActual = MOSTRAR_TABLERO;
        }
        break;
    case MOSTRAR_TABLERO:
        if (key == 'r') reiniciar();
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
