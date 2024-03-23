#ifndef FABRICA_H
#define FABRICA_H

#include <string>
#include <vector>
#include "material.h"
using namespace std;
class Fabrica {
private:
    string nombre;
    vector<Material*> materiales;

public:
    Fabrica(const std::string& nombre);
    ~Fabrica();
    void agregarMaterial(Material* material);
    void mostrarMateriales() const;
    string obtenerNombre() const;
    const vector<Material*>& obtenerMateriales() const;
};

#endif FABRICA_H

