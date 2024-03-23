#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class Fabrica{

};
class Alimento {
private:
    string nombre;
    double temperatura;
    double humedad;
    int cantidad;
    string ingreso;

public:
    Alimento(const string& nombre, double temperatura, double humedad, int cantidad, const string& ingreso)
        : nombre(nombre), temperatura(temperatura), humedad(humedad), cantidad(cantidad), ingreso(ingreso) {}

    void mostrarDetalles() const {
        cout << "Nombre: " << nombre << ", Cantidad: " << cantidad << ", Temperatura: " << temperatura
                  << ", Humedad: " << humedad << ", Ingreso: " << ingreso << endl;
    }

    string obtenerNombre() const {
        return nombre;
    }

    double obtenerTemperatura() const {
        return temperatura;
    }

    double obtenerHumedad() const {
        return humedad;
    }

    int obtenerCantidad() const {
        return cantidad;
    }

    string obtenerIngreso() const {
        return ingreso;
    }
};

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

    const vector<Alimento*>& obtenerAlimentos() const {
        return alimentos;
    }
};

// Funciones para leer y escribir desde/hacia archivos
void guardarCategoriaEnArchivo(const Categoria& categoria) {
    ofstream archivo("Categorias.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar categoría" << endl;
        return;
    }

    archivo << categoria.obtenerNombre() << "\n";
    for (const auto& alimento : categoria.obtenerAlimentos()) {
        archivo << alimento->obtenerNombre() << " " << alimento->obtenerCantidad() << " "
                << alimento->obtenerIngreso() << " " << alimento->obtenerTemperatura() << " "
                << alimento->obtenerHumedad() << "\n";
    }
    archivo << "#FIN#\n";
}

void cargarCategoriasDesdeArchivo(vector<Categoria>& categorias) {
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
            Alimento* alimento = new Alimento(nombreAlimento, temperatura, humedad, cantidad, ingreso);
            categoria.agregarAlimento(alimento);
        }
        categorias.push_back(categoria);
    }
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
    for (const auto& categoria : categorias) {
        guardarCategoriaEnArchivo(categoria);
    }

    return 0;
}
