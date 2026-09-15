#include "TablaPuntajes.h"
#include <fstream>

TablaPuntajes::TablaPuntajes() : cantidad(0) {
    cargarDesdeArchivo();
}

void TablaPuntajes::cargarDesdeArchivo() {
    cantidad = 0;
    std::ifstream archivo(ARCHIVO_PUNTAJES);
    if (!archivo.is_open()) return; 

    std::string nombre;
    int puntaje;
    while (cantidad < MAX_PUNTAJES_GUARDADOS && (archivo >> nombre >> puntaje)) {
        registros[cantidad].nombre = nombre;
        registros[cantidad].puntaje = puntaje;
        cantidad++;
    }
}

void TablaPuntajes::guardarEnArchivo() const {
    std::ofstream archivo(ARCHIVO_PUNTAJES);
    for (int i = 0; i < cantidad; i++) {
        archivo << registros[i].nombre << " " << registros[i].puntaje << "\n";
    }
}

bool TablaPuntajes::calificaParaTop10(int puntaje) const {
    if (cantidad < MAX_PUNTAJES_GUARDADOS) return true;
    return puntaje > registros[cantidad - 1].puntaje; 
}

void TablaPuntajes::ordenarInsercion() {//1
    for (int i = 1; i < cantidad; i++) {
        RegistroPuntaje clave = registros[i];
        int j = i - 1;
        while (j >= 0 && registros[j].puntaje < clave.puntaje) {
            registros[j + 1] = registros[j];
            j--;
        }
        registros[j + 1] = clave;
    }
}

void TablaPuntajes::insertar(const std::string& nombre, int puntaje) {
    if (cantidad < MAX_PUNTAJES_GUARDADOS) {
        registros[cantidad].nombre = nombre;
        registros[cantidad].puntaje = puntaje;
        cantidad++;
    }
    else {
        registros[cantidad - 1].nombre = nombre;
        registros[cantidad - 1].puntaje = puntaje;
    }

    ordenarInsercion();
    guardarEnArchivo();
}

int TablaPuntajes::getCantidad() const { return cantidad; }
const RegistroPuntaje& TablaPuntajes::getRegistro(int indice) const { return registros[indice]; }