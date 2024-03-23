#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Alimento.h"
#include "Fabrica.h"
#include "Funciones.h"
#include "Categoria.h"

using namespace std;

void guardarCategoriaEnArchivo(const Categoria &categoria) {
    ofstream archivo("Categorias.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar categoría" << endl;
        return;
    }

    archivo << categoria.obtenerNombre() << "\n";
    for (auto it = categoria.obtenerAlimentosBegin(); it != categoria.obtenerAlimentosEnd(); ++it) {
        archivo << alimentos->obtenerNombre() << " " << alimentos->obtenerCantidad() << " "
                << alimentos->obtenerIngreso() << " " << alimentos->obtenerTemperatura() << " "
                << alimentos->obtenerHumedad() << "\n";
    }
    archivo << "#FIN#\n";
    archivo.close(); // Cerrar el archivo después de escribir
}

void cargarCategoriasDesdeArchivo(vector<Categoria> &categorias) {
    ifstream archivo("Categorias.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para cargar categorías" << endl;
        return;
    }

    string nombreCategoria;
    while (archivo >> nombreCategoria) {
        Categoria categoria(nombreCategoria);
        while (true) {
            string nombreAlimento;
            int cantidad;
            string ingreso;
            double temperatura;
            double humedad;
            archivo >> nombreAlimento;
            if (nombreAlimento == "#FIN#") break;
            archivo >> cantidad >> ingreso >> temperatura >> humedad;
            Alimento *alimento = new Alimento(nombreAlimento, temperatura, humedad, cantidad, ingreso);
            categoria.agregarAlimento(alimento);
        }
        categorias.push_back(categoria);
    }
    archivo.close(); // Cerrar el archivo después de leer
}

// Función para mostrar menú principal
void mostrarMenuPrincipal() {
    cout << "================================================" << endl;
    cout << "====BIENVENIDO AL INVENTARIO DE INGREDIENTES====" << endl;
    cout << "================================================" << endl;
    cout << "1. Categorias" << endl;
    cout << "2. Fabrica" << endl;
    cout << "0. Salir del programa" << endl;
    cout << "Ingrese una opcion: ";
}

int main() {
    vector<Categoria> categorias;
    vector<Fabrica> fabricas;

    cargarCategoriasDesdeArchivo(categorias);

    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // Lógica para manejar categorías
                break;
            }
            case 2: {
                // Lógica para manejar fábricas
                break;
            }
            case 0: {
                // Salir del programa
                break;
            }
            default: {
                cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
                break;
            }
        }
    } while (opcion != 0);

    // Guardar categorías en archivo antes de salir
    for (const auto &categoria : categorias) {
        guardarCategoriaEnArchivo(categoria);
    }

    return 0;
}
