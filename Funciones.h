
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Alimento.h"
#include "Categoria.h"

using namespace std;

// Declaraciones de funciones globales
void guardarCategoriaEnArchivo(const Categoria &categoria);
void cargarCategoriasDesdeArchivo(vector<Categoria> &categorias);

// Declaración de la clase Funciones
class Funciones {
public:
    virtual void mostrarDetalles() = 0;
};

#endif FUNCIONES_H
