#include "TablaPuntajes.h"
#include <fstream>

TablaPuntajes::TablaPuntajes() : cantidad(0), algoritmoActual(AlgoritmoOrdenamiento::INSERCION) {
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

void TablaPuntajes::setAlgoritmo(AlgoritmoOrdenamiento algo) {
    algoritmoActual = algo;
}

std::string TablaPuntajes::nombreAlgoritmoActual() const {
    switch (algoritmoActual) {
    case AlgoritmoOrdenamiento::INSERCION: return "Insercion";
    case AlgoritmoOrdenamiento::MERGE: return "Merge";
    }
    return "";
}

void TablaPuntajes::ordenar() {
    switch (algoritmoActual) {
    case AlgoritmoOrdenamiento::INSERCION: ordenarInsercion(); break;
    case AlgoritmoOrdenamiento::MERGE: ordenarMerge(); break;
    }
}

void TablaPuntajes::ordenarInsercion() {
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


void TablaPuntajes::mezclar(int inicio, int medio, int fin) {
    RegistroPuntaje temp[MAX_PUNTAJES_GUARDADOS];
    int i = inicio, j = medio + 1, k = inicio;

    while (i <= medio && j <= fin) {
        if (registros[i].puntaje >= registros[j].puntaje) {
            temp[k++] = registros[i++];
        }
        else {
            temp[k++] = registros[j++];
        }
    }
    while (i <= medio) temp[k++] = registros[i++];
    while (j <= fin) temp[k++] = registros[j++];

    for (int x = inicio; x <= fin; x++) {
        registros[x] = temp[x];
    }
}

void TablaPuntajes::mergeSortRango(int inicio, int fin) {
    if (inicio >= fin) return;
    int medio = (inicio + fin) / 2;
    mergeSortRango(inicio, medio);
    mergeSortRango(medio + 1, fin);
    mezclar(inicio, medio, fin);
}

void TablaPuntajes::ordenarMerge() {
    mergeSortRango(0, cantidad - 1);
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

    ordenar();
    guardarEnArchivo();
}

void TablaPuntajes::reordenar() {
    ordenar();
    guardarEnArchivo();
}

int TablaPuntajes::getCantidad() const { return cantidad; }
const RegistroPuntaje& TablaPuntajes::getRegistro(int indice) const { return registros[indice]; }