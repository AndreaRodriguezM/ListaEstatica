#include <iostream>
#include <cstring>
#include <locale>

using namespace std;

const int TAM = 5;

class Empleado
{
private:
    int ClaveEmpleado;
    std::string Nombre;
    float Sueldo;
    std::string ReportaA;
    std::string Domicilio;

public:
    Empleado() : ClaveEmpleado(0), Nombre(""), Sueldo(0), ReportaA(""), Domicilio("") {}

    Empleado(int clave, const std::string &nombre, float sueldo, const std::string &reportaA, const std::string &domicilio)
        : ClaveEmpleado(clave), Nombre(nombre), Sueldo(sueldo), ReportaA(reportaA), Domicilio(domicilio) {}

    void operator=(const Empleado &x)
    {
        ClaveEmpleado = x.ClaveEmpleado;
        Nombre = x.Nombre;
        Domicilio = x.Domicilio;
        Sueldo = x.Sueldo;
        ReportaA = x.ReportaA;
    }

    bool operator==(const Empleado &x) const
    {
        return ClaveEmpleado == x.ClaveEmpleado;
    }

    friend std::ostream &operator<<(std::ostream &o, const Empleado &p)
    {
        o << "\tClave empleado: " << p.ClaveEmpleado << "\t Nombre: " << p.Nombre << std::endl;
        o << "\tDomicilio: " << p.Domicilio << std::endl;
        o << "\tSueldo: " << p.Sueldo << "\t\t Reporta a: " << p.ReportaA << std::endl;
        std::cout << "\n" << std::endl;
        return o;
    }
};

class Lista
{
private:
    Empleado datos[TAM];
    int ult;

public:
    Lista() : ult(-1) {}

    bool vacia() const
    {
        return ult == -1;
    }

    bool llena() const
    {
        return ult == TAM - 1;
    }

    bool inserta(const Empleado &elem, int pos)
    {
        if (llena() || pos < 0 || pos > ult + 1)
        {
            //std::cout << "\nError de insercion" << std::endl;
            return false;
        }
        int i = ult + 1;
        while (i > pos)
        {
            datos[i] = datos[i - 1];
            i--;
        }
        datos[pos] = elem;
        ult++;
        return true;
    }

    bool elimina(int pos)
    {
        if (vacia() || pos < 0 || pos > ult)
        {
            cout << "\n\tError de eliminaci�n" << endl;
            return false;
        }
        int i = pos;
        while (i < ult)
        {
            datos[i] = datos[i + 1];
            i++;
        }
        ult--;
        return true;
    }

    int ultimo() const
    {
        return ult;
    }

    int busca(const Empleado &elem) const
    {
        for (int i = 0; i <= ult; i++)
        {
            if (datos[i] == elem)
            {
                return i;
            }
        }
        return -1; // No se encontr� el empleado
    }

    void muestra() const
    {
        if (vacia())
        {
            cout << "\n\tLa lista est� vac�a.\n" << endl;
        }
        else
        {
            for (int i = 0; i <= ult; i++)
            {
                std::cout << datos[i];
            }
        }
    }
};

int main()
{
    Lista MiLista;
    int opc;

    do
    {
        setlocale(LC_ALL,"");
        cout << "\t------------MEN� - LISTA EST�TICA (EMPLEADO)------------\n" << endl;
        cout << "\t1. Agregar" << endl;
        cout << "\t2. Buscar" << endl;
        cout << "\t3. Eliminar" << endl;
        cout << "\t4. Insertar" << endl;
        cout << "\t5. Mostrar" << endl;
        cout << "\t6. Salir" << endl;
        cout << "\n\tElija una opci�n: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
        {
            int clave;
            std::string nombre;
            float sueldo;
            std::string reportaA;
            std::string domicilio;

            cout << "\tIngrese la clave del empleado: ";
            cin >> clave;
            cout << "\tIngrese el nombre del empleado: ";
            cin.ignore(); // Ignorar el salto de l�nea anterior
            getline(cin, nombre);
            cout << "\tIngrese el domicilio del empleado: ";
            //std::cin.ignore(); // Ignorar el salto de l�nea anterior
            getline(cin, domicilio);
            cout << "\tIngrese el sueldo del empleado: ";
            cin >> sueldo;
            cout << "\tIngrese a qui�n reporta el empleado: ";
            cin.ignore(); // Ignorar el salto de l�nea anterior
            getline(cin, reportaA);

            Empleado nuevoEmpleado(clave, nombre, sueldo, reportaA, domicilio);
            if (MiLista.inserta(nuevoEmpleado, MiLista.ultimo() + 1))
            {
                cout << "\n\t�Se agreg� el empleado con �xito!.\n" << endl;
            }
            else
            {
                cout << "\n\tNo se pudo agregar el empleado porque la lista est� llena." << endl;
            }
            break;
        }
        case 2:
        {
            int clave;
            cout << "\tIngrese la clave del empleado a buscar: ";
            cin >> clave;
            Empleado empleadoBuscado(clave, "", 0, "", "");
            int posicion = MiLista.busca(empleadoBuscado);
            if (posicion != -1)
            {
                cout << "\n\tEmpleado encontrado en la posici�n " << posicion << ".\n" << endl;
            }
            else
            {
                cout << "\n\tNo se encontr� el empleado.\n" << endl;
            }
            break;
        }
        case 3:
        {
            int posicion;
            cout << "\tDame la posici�n del empleado a eliminar: ";
            cin >> posicion;
            if (MiLista.elimina(posicion))
            {
                cout << "\n\t�Se elimin� el empleado con �xito!.\n" << endl;
            }
            else
            {
                cout << "\tNo se pudo eliminar el empleado porque la lista est� vac�a o la posici�n es inv�lida.\n" << endl;
            }
            break;
        }
        case 4:
        {
            Empleado nuevoEmpleado;
            int posicion;
            cout << "\tDame la posici�n donde insertar el empleado: ";
            cin >> posicion;
            if (MiLista.inserta(nuevoEmpleado, posicion))
            {
                cout << "\n\t�Se insert� el empleado con �xito!." << endl;
            }
            else
            {
                cout << "\n\tNo se pudo insertar el empleado porque la lista est� llena o la posici�n es inv�lida.\n" << endl;
            }
            break;
        }
        case 5:
        {
            cout << "\n\t------------LISTA DE EMPLEADOS------------" << endl;
            MiLista.muestra();
            break;
        }
        case 6:
        {
            cout << "\n\tSaliendo de la ejecuci�n del programa.\n" << endl;
            break;
        }
        default:
        {
            cout << "\n\tOpci�n no v�lida. Intentelo de nuevo.\n" << endl;
        }
        }
    }
    while (opc != 6);
    return 0;
}
