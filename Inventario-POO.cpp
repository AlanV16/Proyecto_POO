#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Materiales
{
private:
    string nombre;
    int cantidad;
    string ingreso;

public:
    Materiales(const string &nombre, int cantidad, const string &ingreso) : nombre(nombre), cantidad(cantidad), ingreso(ingreso) {}

    string obtenerNombre() const { return nombre; }
    int obtenerCantidad() const { return cantidad; }
    string obtenerIngreso() const { return ingreso; }
};

class Almacen
{
private:
    string nombre;
    vector<Materiales *> materiales;

public:
    Almacen(const string &nombre) : nombre(nombre) {} // Constructor declarado, pero no implementado

    ~Almacen()
    {
        for (auto material : materiales)
        {
            delete material;
        }
    }

    void agregarMaterial(Materiales *material)
    {
        materiales.push_back(material);
    }

    void mostrarMateriales() const
    {
        cout << "Materiales en " << nombre << ":" << endl;
        for (const auto &material : materiales)
        {
            cout << "Nombre: " << material->obtenerNombre() << ", Cantidad: " << material->obtenerCantidad() << ", Ingreso: " << material->obtenerIngreso() << endl;
        }
    }

    string obtenerNombre() const
    {
        return nombre;
    }

    const vector<Materiales *> &obtenerMateriales() const
    {
        return materiales;
    }
};

class Fabrica
{
private:
    string nombre;
    vector<Materiales *> material; // Relacion de composición
    Almacen *almacen;              // Relacion de agregación

public:
    Fabrica(const string &nombre) : nombre(nombre) {} // Constructor implementado

    ~Fabrica()
    {
        for (auto Materiales : material)
        {
            delete Materiales;
        }
    }

    void agregarMaterial(Materiales *materiales)
    {
        material.push_back(materiales);
    }

    string obtenerNombre() const
    {
        return nombre;
    }

    void AgregarMateriales(const string nombre, int cantidad, const string ingreso) {
    try {
        Materiales *nuevoMaterial = new Materiales(nombre, cantidad, ingreso);
        if (!nuevoMaterial) {
            throw bad_alloc();
        }
        material.push_back(nuevoMaterial);
    } catch(const bad_alloc& e) {
        cerr << "Error: No se pudo asignar memoria para el nuevo material" << endl;
    }
}

    const vector<Materiales *> &obtenerMateriales() const
    {
        return material;
    }

    friend class Categoria; // Declaración de amistad
};

class Alimento
{
private:
    string nombre;
    double temperatura;
    double humedad;
    int cantidad;
    string ingreso;

public:
    Alimento(const string &nombre, double temperatura, double humedad, int cantidad, const string &ingreso)
        : nombre(nombre), temperatura(temperatura), humedad(humedad), cantidad(cantidad), ingreso(ingreso) {}

    void mostrarDetalles() const
    {
        cout << "Nombre: " << nombre << "\t"
             << ", Cantidad: " << cantidad << "\t"
             << ", Temperatura: " << temperatura
             << "\t"
             << ", Humedad: " << humedad << "\t"
             << ", Ingreso: " << ingreso << endl;
    }

    void MostrarElNombre() const
    {
        cout << nombre << endl;
    }

    string obtenerNombre() const
    {
        return nombre;
    }

    double obtenerTemperatura() const
    {
        return temperatura;
    }

    double obtenerHumedad() const
    {
        return humedad;
    }

    int obtenerCantidad() const
    {
        return cantidad;
    }

    string obtenerIngreso() const
    {
        return ingreso;
    }
};

class Categoria
{
private:
    string nombre;
    vector<Alimento *> alimentos;

public:
    Categoria(const string &nombre) : nombre(nombre) {}

    ~Categoria()
    {
        for (auto alimento : alimentos)
        {
            delete alimento;
        }
    }

    void agregarAlimento(Alimento *alimento)
    {
        alimentos.push_back(alimento);
    }

    void AgregarAlimentoC(const string &nombre, double temperatura, double humedad, int cantidad, const string &ingreso)
    {
        Alimento *nuevoAlimento = new Alimento(nombre, temperatura, humedad, cantidad, ingreso);
        alimentos.push_back(nuevoAlimento);
    }

    void mostrarAlimentos() const
    {
        cout << "Categoria: " << nombre << endl;
        for (const auto &alimento : alimentos)
        {
            alimento->mostrarDetalles();
        }
    }

    string obtenerNombre() const
    {
        return nombre;
    }

    const vector<Alimento *> &obtenerAlimentos() const
    {
        return alimentos;
    }
    friend class Fabrica; // Declaración de amistad
};

// Funciones para leer y escribir desde/hacia archivos
void guardarCategoriaEnArchivo(const Categoria &categoria)
{
    ofstream archivo("Categorias.txt", ios::app);
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo para guardar categoria" << endl;
        return;
    }

    archivo << categoria.obtenerNombre() << "\n";
    for (const auto &alimento : categoria.obtenerAlimentos())
    {
        archivo << alimento->obtenerNombre() << " " << alimento->obtenerCantidad() << " "
                << alimento->obtenerIngreso() << " " << alimento->obtenerTemperatura() << " "
                << alimento->obtenerHumedad() << "\n";
    }
    archivo << "#FIN#\n";
}

void cargarCategoriasDesdeArchivo(vector<Categoria> &categorias)
{
    ifstream archivo("Categorias.txt");
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo para cargar categorias" << endl;
        return;
    }

    string nombreCategoria;
    while (getline(archivo, nombreCategoria))
    {
        if (nombreCategoria == "#FIN#")
            break;
        Categoria categoria(nombreCategoria);
        string nombreAlimento;
        int cantidad;
        string ingreso;
        double temperatura, humedad;
        while (archivo >> nombreAlimento >> cantidad >> ingreso >> temperatura >> humedad)
        {
            if (nombreAlimento == "#FIN#")
                break;
            Alimento *alimento = new Alimento(nombreAlimento, temperatura, humedad, cantidad, ingreso);
            categoria.agregarAlimento(alimento);
        }
        categorias.push_back(categoria);
    }
}

void guardarFabricaEnArchivo(const Fabrica &fabrica)
{
    ofstream archivo("Fabricas.txt", ios::app);
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo para guardar fabricas" << endl;
        return;
    }

    archivo << fabrica.obtenerNombre() << "\n";
    for (const auto &Materiales : fabrica.obtenerMateriales())
    {
        archivo << Materiales->obtenerNombre() << " " << Materiales->obtenerCantidad() << " "
                << Materiales->obtenerIngreso()<<"\n"; 
    }
    archivo << "#FIN#\n";
}

void cargarFabricaDesdeArchivo(vector<Fabrica> &fabricas)
{
    ifstream archivo("Fabricas.txt");
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo para cargar fabricas" << endl;
        return;
    }

    string nombreFabrica;
    while (getline(archivo, nombreFabrica))
    {
        if (nombreFabrica == "#FIN#")
            break;
        Fabrica fabrica(nombreFabrica);
        string nombreMaterial;
        int cantidad;
        string ingreso;
        while (archivo >> nombreMaterial >> cantidad >> ingreso)
        {
            if (nombreMaterial == "#FIN#")
                break;
            Materiales *material = new Materiales(nombreMaterial, cantidad, ingreso);
            fabrica.agregarMaterial(material);
        }
        fabricas.push_back(fabrica);
    }
}

//================================================================================================================================
void MostrarAlimentosCategoria(const Categoria &categoria);
void eliminarAlimentoCategoria(Categoria &categoria, int numAlimentoEliminar);

// Función para mostrar menú principal
void mostrarMenuPrincipal()
{
    cout << "================================================" << endl;
    cout << "====BIENVENIDO AL INVENTARIO DE INGREDIENTES====" << endl;
    cout << "================================================" << endl;
    cout << "1. Categorias" << endl;
    cout << "2. Agregar Categorias" << endl;
    cout << "3. Eliminar categorias" << endl;
    cout << "4. Fabrica" << endl;
    cout << "5. Almacenes" << endl;
    cout << "0. Salir del programa" << endl;
    cout << "Ingrese una opcion: ";
}
//===============================================================================================================================
void mostrarCategorias(vector<Categoria> &categoria)
{
    cout << "==============================" << endl;
    cout << "====Categorias disponibles====" << endl;
    cout << "==============================" << endl;
    for (size_t i = 0; i < categoria.size(); i++)
    {
        cout << i + 1 << "." << categoria[i].obtenerNombre() << endl;
    }

    if (categoria.empty())
    {
        cout << "No hay categorias disponibles" << endl;
        system("pause");
        system("cls");
        return;
    }

    int OpcionCategoria;
    cout << "Selencione el numero de una categoria: ";
    cin >> OpcionCategoria;
    if (OpcionCategoria >= 1 && OpcionCategoria <= categoria.size())
    {
        Categoria &categoriaSeleccion = categoria[OpcionCategoria - 1];
        int opcionCategoriaDetallado;
        string nombre;
        double temperatura, humedad;
        int cantidad, numAlimentoEliminar;
        string ingreso;
        system("cls");
        do
        {
            cout << "===================================================" << endl;
            cout << "===="
                 << "\t" << categoriaSeleccion.obtenerNombre() << "\t"
                 << "====" << endl;
            cout << "===================================================" << endl;
            cout << "1. Mostrar alimentos" << endl;
            cout << "2. Agregar alimentos" << endl;
            cout << "3. Eliminar alimento" << endl;
            cout << "0. regresar al inicio" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcionCategoriaDetallado;

            switch (opcionCategoriaDetallado)
            {
            case 1:
                system("cls");
                MostrarAlimentosCategoria(categoriaSeleccion);
                break;
            case 2:
                system("cls");
                cout << "Ingrese el nombre del alimento: ";
                cin >> nombre;
                cout << "Ingrese la temperatura del alimento: ";
                cin >> temperatura;
                cout << "Ingrese la humedad del alimento: ";
                cin >> humedad;
                cout << "Ingrese la cantidad del alimento: ";
                cin >> cantidad;
                cout << "Ingrese el ingreso del alimento: ";
                cin >> ingreso;
                categoriaSeleccion.AgregarAlimentoC(nombre, temperatura, humedad, cantidad, ingreso);
                break;
            case 3:
                system("cls");
                cout << "Lista de alimentos:" << endl;
                for (size_t i = 0; i < categoriaSeleccion.obtenerAlimentos().size(); ++i)
                {
                    cout << i + 1 << ". ";
                    categoriaSeleccion.obtenerAlimentos()[i]->MostrarElNombre();
                }
                cout << "Ingrese el numero del alimento que desea eliminar: ";
                cin >> numAlimentoEliminar;
                eliminarAlimentoCategoria(categoriaSeleccion, numAlimentoEliminar);
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << "Opcion invalida" << endl;
            }
        } while (opcionCategoriaDetallado != 0);
    }
    else if (OpcionCategoria == 0)
    {
        return;
    }
    else
    {
        cout << "Opcion invalida" << endl;
    }
}
//=================================================================================================================

void MostrarAlimentosCategoria(const Categoria &categoria)
{
    int i = 0;
    cout << "=======================================================" << endl;
    cout << "====Alimentos en "
         << "\t" << categoria.obtenerNombre() << "\t"
         << "====" << endl;
    cout << "=======================================================" << endl;
    for (const Alimento *alimento : categoria.obtenerAlimentos())
    {
        cout << i + 1 << ". ";
        alimento->MostrarElNombre();
        i++;
    }
    system("pause");
    system("cls");
}

//=================================================================================================================

void eliminarAlimentoCategoria(Categoria &categoria, int numAlimentoEliminar)
{
    if (numAlimentoEliminar >= 1 && numAlimentoEliminar <= categoria.obtenerAlimentos().size())
    {
        vector<Alimento *> alimentos = categoria.obtenerAlimentos();
        delete alimentos[numAlimentoEliminar - 1];
        alimentos.erase(alimentos.begin() + numAlimentoEliminar - 1);
        categoria = Categoria(categoria.obtenerNombre());
        for (auto alimento : alimentos)
        {
            categoria.agregarAlimento(alimento);
        }
        cout << "El alimento ha sido eliminado correctamente." << endl;
    }
    else
    {
        cerr << "Numero de alimento invalido." << endl;
    }
}

//================================================================================================

void AgregarCategoria(vector<Categoria> &categoria)
{
    string nombre;
    cout << "Ingrese el nombre de la nueva categoria: ";
    cin >> nombre;
    Categoria NuevaCategoria(nombre);
    categoria.push_back(NuevaCategoria);
    cout << "La categoria ha sido agregado con exito" << endl;
    system("pause");
    system("cls");
}

//====================================================================================================

void EliminarCategoria(vector<Categoria> &categoria)
{
    if (categoria.empty())
    {
        cout << "No hay categorias para eliminar" << endl;
        system("pause");
        system("cls");
        return;
    }
    system("cls");
    cout << "================================" << endl;
    cout << "==== Categorias disponibles ====" << endl;
    cout << "================================" << endl;
    for (size_t i = 0; i < categoria.size(); i++)
    {
        cout << i + 1 << ". " << categoria[i].obtenerNombre() << endl;
    }

    int opcionEliminar;
    cout << "Seleccione el numero de la categoria a eliminar (0 para cancelar la accion): ";
    cin >> opcionEliminar;

    if (opcionEliminar >= 1 && opcionEliminar <= categoria.size())
    {
        categoria.erase(categoria.begin() + opcionEliminar - 1);
        cout << "Categoria eliminada con exito" << endl;
        system("pause");
        system("cls");
    }
    else if (opcionEliminar == 0)
    {
        return;
    }
    else
    {
        cout << "Opcion invalida" << endl;
    }
}

//================================================================================================

void MostrarMaterialesFabrica(const Fabrica &fabrica)
{
    int i = 0;
    cout << "=======================================================" << endl;
    cout << "====Materiales en "
         << "\t" << fabrica.obtenerNombre() << "\t"
         << "====" << endl;
    cout << "=======================================================" << endl;
    for (const Materiales *material : fabrica.obtenerMateriales())
    {
        cout << i + 1 << ". " << material->obtenerNombre() << " : " << material->obtenerCantidad() << " unidades" << endl;
        i++;
    }
    system("pause");
    system("cls");
}

//================================================================================================

void eliminarMateriales(Fabrica &fabrica, int numMaterialEliminar)
{
    if (numMaterialEliminar >= 1 && numMaterialEliminar <= fabrica.obtenerMateriales().size())
    {
        vector<Materiales *> material = fabrica.obtenerMateriales();
        delete material[numMaterialEliminar - 1];
        material.erase(material.begin() + numMaterialEliminar - 1);
        fabrica = Fabrica(fabrica.obtenerNombre());
        for (auto materiales : material)
        {
            fabrica.agregarMaterial(materiales);
        }
        cout << "El alimento ha sido eliminado correctamente." << endl;
    }
    else
    {
        cout << "Numero de alimento invalido." << endl;
    }
}

//================================================================================================

void AgregarFabrica(vector<Fabrica> &fabrica)
{
    string nombre;
    cout << "Ingrese el nombre de la nueva Fabrica: ";
    cin >> nombre;
    Fabrica NuevaFabrica(nombre);
    fabrica.push_back(NuevaFabrica);
    cout << "La fabrica ha sido agregado con exito" << endl;
    system("pause");
    system("cls");
}

//================================================================================================

void MenuFabrica(vector<Fabrica> &fabrica)
{
    system("cls");
    cout << "==============================" << endl;
    cout << "=====Fabricas disponibles=====" << endl;
    cout << "==============================" << endl;
    for (size_t i = 0; i < fabrica.size(); i++)
    {
        cout << i + 1 << ". " << fabrica[i].obtenerNombre() << endl;
    }

    if (fabrica.empty())
    {
        cout << "No hay fabricas disponibles" << endl;
        system("pause");
        system("cls");
        return;
    }

    int OpcionFabrica;
    cout << "Selencione el numero de una fabrica: ";
    cin >> OpcionFabrica;
    if (OpcionFabrica >= 1 && OpcionFabrica <= fabrica.size())
    {
        Fabrica &FabricaSeleccion = fabrica[OpcionFabrica - 1];
        int opcionFabricaDetallado, cantidad, numMaterialEliminar;
        string nombre, ingreso;
        system("cls");
        do
        {
            cout << "===================================================" << endl;
            cout << "===="
                 << "\t" << FabricaSeleccion.obtenerNombre() << "\t"
                 << "====" << endl;
            cout << "===================================================" << endl;
            cout << "1. Mostrar materiales" << endl;
            cout << "2. Agregar materiales" << endl;
            cout << "3. Eliminar materiales" << endl;
            cout << "0. regresar al inicio" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcionFabricaDetallado;

            switch (opcionFabricaDetallado)
            {
            case 1:
                system("cls");
                MostrarMaterialesFabrica(FabricaSeleccion);
                break;
            case 2:
                system("cls");
                cout << "Ingrese el nombre del material: ";
                cin >> nombre;
                cout << "Ingrese la cantidad del material: ";
                cin >> cantidad;
                cout << "ingrese la fecha de ingreso: ";
                cin >> ingreso;
                FabricaSeleccion.AgregarMateriales(nombre, cantidad, ingreso);
                break;
            case 3:
                system("cls");
                cout << "Lista de alimentos:" << endl;
                for (size_t i = 0; i < FabricaSeleccion.obtenerMateriales().size(); ++i)
                {
                    cout << i + 1 << ". ";
                    FabricaSeleccion.obtenerMateriales()[i]->obtenerNombre();
                }
                cout << "Ingrese el numero del alimento que desea eliminar: ";
                cin >> numMaterialEliminar;
                eliminarMateriales(FabricaSeleccion, numMaterialEliminar);
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << "Opcion invalida" << endl;
            }
        } while (opcionFabricaDetallado != 0);
    }
    else if (OpcionFabrica == 0)
    {
        return;
    }
    else
    {
        cout << "Opcion invalida" << endl;
    }
}

//=========================================================================================================================

void EliminarFabrica(vector<Fabrica> &fabrica)
{
    if (fabrica.empty())
    {
        cout << "No hay fabricas para eliminar" << endl;
        system("pause");
        system("cls");
        return;
    }
    system("cls");
    cout << "================================" << endl;
    cout << "===== Fabricas disponibles =====" << endl;
    cout << "================================" << endl;
    for (size_t i = 0; i < fabrica.size(); i++)
    {
        cout << i + 1 << ". " << fabrica[i].obtenerNombre() << endl;
    }

    int opcionEliminarFabrica;
    cout << "Seleccione el numero de la fabrica a eliminar (0 para cancelar la accion): ";
    cin >> opcionEliminarFabrica;

    if (opcionEliminarFabrica >= 1 && opcionEliminarFabrica <= fabrica.size())
    {
        fabrica.erase(fabrica.begin() + opcionEliminarFabrica - 1);
        cout << "Fabrica eliminada con exito" << endl;
        system("pause");
        system("cls");
    }
    else if (opcionEliminarFabrica == 0)
    {
        return;
    }
    else
    {
        cout << "Opcion invalida" << endl;
    }
}

//=========================================================================================================================

void AlmacenAlimentos(vector<Categoria>& categoria){
    cout<<"=============================="<<endl;
    cout<<"==== Almacen de Alimentos ===="<<endl;
    cout<<"=============================="<<endl;

    if(categoria.empty()){
        cout<<"El Almacen esta vacio"<<endl;
        system("pause");
        system("cls");
        return;
    }
    cout<<"Categorias disponibles en almacen: "<<endl;
    for(size_t i=0; i<categoria.size(); i++){
        cout<<i+1<<". "<<categoria[i].obtenerNombre()<<endl;
    }

    int opcionCategoria;
    cout<<"Ingrese la opcion de una categoria (0 para volver al menu principal): ";
    cin>> opcionCategoria;
     if(opcionCategoria>=1 && opcionCategoria<=categoria.size()){
        const Categoria& categoriaSeleccion = categoria[opcionCategoria-1];
        system("cls");
        cout<<"====Alimentos en la categoria "<<categoriaSeleccion.obtenerNombre()<<"===="<<endl;
        cout<<"\n";
        cout<<"Nombre\tCantidad\tFecha Ingreso\tTemperatura\tHumedad"<<endl;
        cout<<"------------------------------------------------------------------------------------------------"<<endl;
        for(const Alimento* alimento: categoriaSeleccion.obtenerAlimentos()){
            cout<<alimento->obtenerNombre()<<"\t"<<alimento->obtenerCantidad()<<" unidades\t"<<alimento->obtenerIngreso()<<"\t"<<alimento->obtenerTemperatura()<<"\t"<<"\t"<<alimento->obtenerHumedad()<<endl;
            cout<<"------------------------------------------------------------------------------------------------"<<endl;
        }
        system("pause");
        system("cls");
     }
     else if(opcionCategoria == 0){
        return;
     }
     else{
        cout<<"Opncion Invalida"<<endl;
     }
}

//=========================================================================================================================

void AlmacenFabrica(vector<Fabrica>& fabrica){
    cout<<"==============================="<<endl;
    cout<<"==== Almacen de la fabrica ===="<<endl;
    cout<<"==============================="<<endl;

    if(fabrica.empty()){
        cout<<"El Almacen esta vacio"<<endl;
        system("pause");
        system("cls");
        return;
    }
    cout<<"Fabricas disponibles: "<<endl;
    for(size_t i=0; i<fabrica.size(); i++){
        cout<<i+1<<". "<<fabrica[i].obtenerNombre()<<endl;
    }

    int opcionFabrica;
    cout<<"Ingrese la opcion de una fabrica (0 para volver al menu principal): ";
    cin>> opcionFabrica;
     if(opcionFabrica>=1 && opcionFabrica<=fabrica.size()){
        const Fabrica& fabricaSeleccion = fabrica[opcionFabrica-1];
        system("cls");
        cout<<"====Materiales en la fabrica de "<<fabricaSeleccion.obtenerNombre()<<"===="<<endl;
        cout<<"\n";
        cout<<"Nombre\t\tCantidad\t\tIngreso"<<endl;
        cout<<"------------------------------------------------------------------------------------------------"<<endl;
        for(const Materiales* material: fabricaSeleccion.obtenerMateriales()){
        cout<<material->obtenerNombre()<<"\t"<<material->obtenerCantidad()<<" unidades"<<"\t"<<material->obtenerIngreso()<<endl;
            cout<<"------------------------------------------------------------------------------------------------"<<endl;
        }
        system("pause");
        system("cls");
     }
     else if(opcionFabrica == 0){
        return;
     }
     else{
        cout<<"Opncion Invalida"<<endl;
     }
}

//=========================================================================================================================

int main()
{
    vector<Categoria> categorias;
    vector<Fabrica> fabrica;
    bool salirFabrica = false;
    bool salirAlmacen = false;
    int opcion, opcionFabrica, opcionAlmacen;
    cargarCategoriasDesdeArchivo(categorias);
    cargarFabricaDesdeArchivo(fabrica);
    do
    {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            system("cls");
            mostrarCategorias(categorias);
            break;
        }
        case 2:
        {
            system("cls");
            AgregarCategoria(categorias);
            break;
        }
        case 3:
        {
            system("cls");
            EliminarCategoria(categorias);
            break;
        }
        case 4:
        {
            system("cls");
            salirFabrica = false;
            do
            {
                cout << "================================================" << endl;
                cout << "============BIENVENIDO A LA FABRICA============" << endl;
                cout << "================================================" << endl;
                cout << "1. Fabrica" << endl;
                cout << "2. Agregar Fabrica" << endl;
                cout << "3. Eliminar Fabrica" << endl;
                cout << "0. Regresar al menu principal" << endl;
                cout << "Ingrese una opcion: ";
                cin >> opcionFabrica;
                switch (opcionFabrica)
                {
                case 1:
                    MenuFabrica(fabrica);
                    break;
                case 2:
                    system("cls");
                    AgregarFabrica(fabrica);
                    break;
                case 3:
                    system("cls");
                    EliminarFabrica(fabrica);
                    break;

                case 0:
                    cout << "Regresando al menu principal...." << endl;
                    system("pause");
                    system("cls");
                    salirFabrica = true;
                    break;
                default:
                    cout << "Opcion invalida" << endl;
                    break;
                }
            } while (!salirFabrica);
            break;
        }
        case 5:
        {
            system("cls");
            salirAlmacen=false;
            do
            {
                cout << "================================================" << endl;
                cout << "==========BIENVENIDO AL ALMACEN GENERAL=========" << endl;
                cout << "================================================" << endl;
                cout << "1. Alimentos" << endl;
                cout << "2. Materiales" << endl;
                cout << "0. Regresar al menu principal" << endl;
                cout << "Ingrese una opcion: ";
                cin >> opcionAlmacen;

                switch (opcionAlmacen)
                {
                case 1:
                    system("cls");
                    AlmacenAlimentos(categorias);
                    break;
                case 2:
                    system("cls");
                    AlmacenFabrica(fabrica);
                    break;
                case 0:
                    cout << "Regresando al menu principal...." << endl;
                    system("pause");
                    system("cls");
                    salirAlmacen = true;
                    break;
                default:
                    cout << "Opcion invalida" << endl;
                    break;
                }

            }while(!salirAlmacen);
            break;
        }
        case 0:
        {
            for (const auto &categoria : categorias)
            {
                guardarCategoriaEnArchivo(categoria);
            }
            for (const auto &fabricas : fabrica)
            {
                guardarFabricaEnArchivo(fabricas);
            }
            break;
        }
        default:
        {
            cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
            break;
        }
        }
    } while (opcion != 0);
    return 0;
}
