#pragma once
#include "RegistroPuntaje.h"
#include "../config/Constants.h"
#include <string>

enum class AlgoritmoOrdenamiento {
    INSERCION,
    MERGE
};

class TablaPuntajes {
public:
    TablaPuntajes();

    bool calificaParaTop10(int puntaje) const;
    void insertar(const std::string& nombre, int puntaje);

    void setAlgoritmo(AlgoritmoOrdenamiento algo);
    std::string nombreAlgoritmoActual() const;
    void reordenar(); 

    int getCantidad() const;
    const RegistroPuntaje& getRegistro(int indice) const;

private:
    RegistroPuntaje registros[MAX_PUNTAJES_GUARDADOS];
    int cantidad;
    AlgoritmoOrdenamiento algoritmoActual;

    void cargarDesdeArchivo();
    void guardarEnArchivo() const;

    void ordenar(); 
    void ordenarInsercion();
    void ordenarMerge();
    void mergeSortRango(int inicio, int fin);
    void mezclar(int inicio, int medio, int fin);
};