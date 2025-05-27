#include "Rey.h"
#include "Reina.h"
#include "Torre.h"
#include "Alfil.h"
#include "Caballo.h"
#include "Peon.h"
#include "Pieza.h"
#include <cmath>
#include "freeglut.h"
#include "Tablero.h"
#include "Menu.h"

Menu menu;
Tablero* tablero = nullptr;

//Función tablero
void pantalla(int w, int h) 
{
    glMatrixMode(GL_PROJECTION); //definicion sist coord. 
    glLoadIdentity();
    gluOrtho2D(0, 5, 5, 0); //limites de la proyeccion (el tablero ser� de 5x5)
    glViewport(0, 0, w, h); //ajuste al nuevo tama�o de la pantalla (w de ancho y h de alto)
}

//Función tablero
void mouse(int button, int state, int x, int y) //tablero
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int w = glutGet(GLUT_WINDOW_WIDTH); //ancho de la ventana
        int h = glutGet(GLUT_WINDOW_HEIGHT); //alto de la ventana 
        float xf = (float)x / w * 5; //la coord. x del raton de pixeles a formato de goord. GL
        float yf = (float)y / h * 5; //la coord. y del raton
        tablero->click(xf, yf, menu.getSeleccion1()); //pasa las nuevas coord. y la seleccion de jugadores
        glutPostRedisplay(); //vuelve a imprimir el tablero habiendo cambiado la pieza a la indicada por el raton
    } // marcas la pieza a cambiar y el destino final y lo actualiza

}

void configurarProyeccionMenu() {
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // Coordenadas típicas para texto de menú
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Función dibujar pantalla 
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (!menu.haIniciadoJuego()) {
        configurarProyeccionMenu();

        menu.render();
    }
    else {
        if (!tablero) {
            tablero = new Tablero(menu.getSeleccion3()); // de manera que tablero sepa las selecciones del usuario

            int w = glutGet(GLUT_WINDOW_WIDTH);
            int h = glutGet(GLUT_WINDOW_HEIGHT);
            pantalla(w, h); // fuerza recalcular viewport y proyección para que imprima correctamente el tablero
        }
        tablero->dibujar(menu.getSeleccion2());
    }

    glutSwapBuffers();
}


// Función entrada de teclado 
void keyboard(unsigned char key, int x, int y) {
    menu.manejarInput(key);

    // Si se reinicia el juego, liberamos el tablero
    if (!menu.haIniciadoJuego() && tablero) {
        delete tablero;
        tablero = nullptr;
    }

    glutPostRedisplay();
}

//Función inicializar OpenGL 
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Fondo blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Coordenadas de dibujo
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);              // Tamaño ventana
    glutInitWindowPosition(100, 100);          // Posición en pantalla
    glutCreateWindow("Juego de Ajedrez");      // Título de la ventana

    initOpenGL();              // Configuración inicial de OpenGL
    glutDisplayFunc(display); // Dibujo
    glutKeyboardFunc(keyboard); // Entrada de teclado
    glutMouseFunc(mouse);

    glutMainLoop();            // Bucle principal de eventos
    //delete tablero; //liberacion de memoria asignada al obj tablero
    return 0;
}
