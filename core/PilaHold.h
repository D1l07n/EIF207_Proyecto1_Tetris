#pragma once
#include "TipoPieza.h"

class PilaHold {
public:
    PilaHold();
    ~PilaHold();

    bool isEmpty() const;

   
    bool push(TipoPieza v);

    TipoPieza pop();

    TipoPieza top() const;

private:
    struct Nodo {
        TipoPieza dato;
        Nodo* sig;
        Nodo(TipoPieza d) : dato(d), sig(nullptr) {}
    };

    Nodo* tope;
};
