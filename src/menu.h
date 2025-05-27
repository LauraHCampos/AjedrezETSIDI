#pragma once

enum EstadoMenu {
    MENU_PRINCIPAL,
    MENU_TIPO_AJEDREZ,
    MENU_MODOS_ESPECIALES,
    MOSTRAR_TABLERO
};

class Menu {
private:
    int seleccion1 = 0;
    int seleccion2 = 0;
    int seleccion3 = 0;
    EstadoMenu estadoActual = MENU_PRINCIPAL;
    bool juegoIniciado = false;

public:
    Menu();

    void render();
    void manejarInput(unsigned char key);
    bool haIniciadoJuego() const;
    EstadoMenu obtenerEstado() const;
    int getSeleccion1() const;
    int getSeleccion2() const;
    int getSeleccion3() const;
    void reiniciar();
};
