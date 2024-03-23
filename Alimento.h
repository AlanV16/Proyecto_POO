#ifndef ALIMENTO_H
#define ALIMENTO_H
#include <iostream>
#include <string>
#include <vector>
#include "Funciones.h"
using namespace std;

class Alimento: public Funciones{
private:
    string nombre;
    double temperatura;
    double humedad;
    int cantidad;
    string ingreso;

public:
    Alimento(const string& nombre, double temperatura, double humedad, int cantidad, const string& ingreso)
        : nombre(nombre), temperatura(temperatura), humedad(humedad), cantidad(cantidad), ingreso(ingreso) {}

    void mostrarDetalles() override {
        cout<< "Nombre: " << nombre << ", Cantidad: " << cantidad << ", Temperatura: " << temperatura
            << ", Humedad: " << humedad << ", Ingreso: " << ingreso <<endl;
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

#endif //ALIMENTO_H
