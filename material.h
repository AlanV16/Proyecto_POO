
#include <string>
using namespace std;
class Material {
private:
    string nombre;
    int cantidad;

public:
    Material(const string& nombre, int cantidad);
    string obtenerNombre() const;
    int obtenerCantidad() const;
};

