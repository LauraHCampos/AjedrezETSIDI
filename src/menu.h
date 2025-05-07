#pragma once

// Enumeración para controlar en qué estado está la aplicación
enum EstadoApp {
    MENU_PRINCIPAL,
    MENU_MODO_JUEGO,
    MENU_FINAL,
    JUEGO_VS_MAQUINA,
    JUEGO_VS_JUGADOR
};

// Variable global que indica el estado actual
extern EstadoApp estadoActual;

// Funciones públicas del menú
void mostrarMenu();
void clickMouse(int button, int state, int x, int y);
void display();
