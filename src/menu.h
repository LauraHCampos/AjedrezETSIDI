#pragma once

// Enumeraci�n para controlar en qu� estado est� la aplicaci�n
enum EstadoApp {
    MENU_PRINCIPAL,
    MENU_MODO_JUEGO,
    MENU_FINAL,
    JUEGO_VS_MAQUINA,
    JUEGO_VS_JUGADOR
};

// Variable global que indica el estado actual
extern EstadoApp estadoActual;

// Funciones p�blicas del men�
void mostrarMenu();
void clickMouse(int button, int state, int x, int y);
void display();
