#ifndef ALMACEN_H
#define ALMACEN_H

#include <string>
#include <vector>
#include "material.h"
using namespace std;
class Almacen {
private:
    string nombre;
    vector<Material*> materiales;

public:
    Almacen(const string& nombre);
    ~Almacen();
    void agregarMaterial(Material* material);
    void mostrarMateriales() const;
    std::string obtenerNombre() const;
    const std::vector<Material*>& obtenerMateriales() const;
};

#endif ALMACEN_H

