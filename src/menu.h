#pragma once
#ifndef MENU_H
#define MENU_H

// Enumeración para controlar en que estado está la aplicación
enum EstadoApp {
    MENU_PRINCIPAL,
    MENU_MODO_JUEGO,
    MENU_TIPO,
    JUEGO_VS_MAQUINA,
    JUEGO_VS_JUGADOR
};
enum TipoJuego { VS_MAQUINA, VS_JUGADOR };
enum ModoJuego { CLASICO, ETSIDI_, REY_PEON };
enum TipoTablero { GARDEN, BABY };
// Variable global que indica el estado actual
extern EstadoApp estadoActual;

// Funciones públicas del menú
void mostrarMenu();
void clickMouse(int button, int state, int x, int y);
void display();

#endif
