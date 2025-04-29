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

Tablero* tablero;

void dibuja() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    tablero->dibujar(); //dibuja el tablero
    glutSwapBuffers();
}

void pantalla(int w, int h) 
{
    glMatrixMode(GL_PROJECTION); //definicion sist coord. 
    glLoadIdentity();
    gluOrtho2D(0, 5, 5, 0); //limites de la proyeccion (el tablero será de 5x5)
    glViewport(0, 0, w, h); //ajuste al nuevo tamaño de la pantalla (w de ancho y h de alto)
}

void mouse(int button, int state, int x, int y) //interaccion con el raton
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int w = glutGet(GLUT_WINDOW_WIDTH); //ancho de la ventana
        int h = glutGet(GLUT_WINDOW_HEIGHT); //alto de la ventana 
        float xf = (float)x / w * 5; //la coord. x del raton de pixeles a formato de goord. GL
        float yf = (float)y / h * 5; //la coord. y del raton
        tablero->click(xf, yf); //pasa las nuevas coord. 
        glutPostRedisplay(); //vuelve a imprimir el tablero habiendo cambiado la pieza a la indicada por el raton
    } // marcas la pieza a cambiar y el destino final y lo actualiza
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600); //tamaño inicial ventana en pixeles
    glutCreateWindow("MiniChess Baby 2D"); //titulo de la ventana

    tablero = new Tablero(); //nuevo objeto (puntero global)

    //para que llame a las funciones al ser necesario (sin seguir el ordende linea a linea)
    glutDisplayFunc(dibuja);
    glutReshapeFunc(pantalla);
    glutMouseFunc(mouse);

    glClearColor(0, 0, 0, 1); //color de fondo negro

    glutMainLoop();

    delete tablero; //liberacion de memoria asignada al obj tablero
    return 0;
}
