#pragma once
#include "RegistroPuntaje.h"
#include "../config/Constants.h"

class TablaPuntajes {
public:
    TablaPuntajes();

    bool calificaParaTop10(int puntaje) const;
    void insertar(const std::string& nombre, int puntaje);

    int getCantidad() const;
    const RegistroPuntaje& getRegistro(int indice) const;

private:
    RegistroPuntaje registros[MAX_PUNTAJES_GUARDADOS];
    int cantidad;

    void cargarDesdeArchivo();
    void guardarEnArchivo() const;
    void ordenarInsercion(); 
};