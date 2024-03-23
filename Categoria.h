#ifndef CATEGORIA_H
#define CATEGORIA_H
#include <iostream>
#include <vector>
#include "Alimento.h"
using namespace std;

class Categoria {
private:
    string nombre;
    vector<Alimento*> alimentos;

public:
    Categoria(const string& nombre) : nombre(nombre) {}

    ~Categoria() {
        for (auto alimento : alimentos) {
            delete alimento;
        }
    }

    void agregarAlimento(Alimento* alimento) {
        alimentos.push_back(alimento);
    }

    void mostrarAlimentos() const {
        cout << "Categoria: " << nombre << endl;
        for (const auto& alimento : alimentos) {
            alimento->mostrarDetalles();
        }
    }

    string obtenerNombre() const {
        return nombre;
    }

    vector<Alimento*>::const_iterator obtenerAlimentosBegin() const {
        return alimentos.begin();
    }
    vector<Alimento*>::const_iterator obtenerAlimentosEnd() const {
        return alimentos.end();
    }
};

#endif //CATEGORIA_H