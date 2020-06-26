#include "Clases.h"
#include "Lista.h"
#include <conio.h>

using namespace std;

int main()
{
	Empresa *listaTrabajadores;
	string nombreEmpresa;
	int numeroEmpleados;
	int opcion;
	int filtro;

MENUPRINCIPAL:
	System::Console::Clear();
	cout << "*******************BIENVENIDO*******************" << endl;
	cout << "************************************************" << endl;
	cout << "1) REGISTRAR MI EMPRESA						 " << endl;
	cout << "2) MOSTRAR LISTA DE EMPLEADOS                   " << endl;
	cout << "3) SALIR                                        " << endl;
	cout << "************************************************" << endl;
	cout << "Escriba el numero de la opcion que desea realizar..." << endl;
	cin >> opcion;

	switch (opcion)
	{
	case 1:
		Console::Clear();
		cout << "Ingrese el nombre de su empresa: "; cin >> nombreEmpresa; cout << endl;
		do
		{
			Console::Clear();
			cout << "Ingrese el numero de empleados que desea mostrar: "; cin >> numeroEmpleados; cout << endl;
		} while (numeroEmpleados < 0 || numeroEmpleados >100);
		listaTrabajadores = new Empresa(nombreEmpresa, numeroEmpleados);
		listaTrabajadores->generarEmpleados(numeroEmpleados);
		goto MENUPRINCIPAL;
	case 2:
		Console::Clear();
		if (listaTrabajadores == NULL) {
			cout << "Aun no se ha registrado ninguna empresa...";
			_getch();
			goto MENUPRINCIPAL;
		}
		else
		{
			listaTrabajadores->mostrarLista();

			cout << endl << left << setw(10) << "PRESIONE CUALQUIER TECLA PARA VER OPCIONES ..." << endl;
			_getch();
			Console::Clear();
			cout << endl << left << setw(10) << "ORDENAR/FILTRAR LISTA SEGUN: " << endl;
			cout << "1. Ordenar Alfabeticamente" << endl;
			cout << "2. Buscar por columnas" << endl;
			cout << "3. Indexar (EN DESARROLLO)" << endl;
			cin >> filtro;

			switch (filtro)
			{
			case 1:
				listaTrabajadores->pasarArbol();
				listaTrabajadores->ordenarNombre();
				break;
			case 2:
				cout << "Columnas: " << endl;
				cout << "1: NOMBRE, 2: EDAD, 3: AREA, 4: SUELDOS, 5: MESES, 6: CTS, 7: INDIS" << endl;
				listaTrabajadores->pasarArbol();
				listaTrabajadores->buscar();
				break;
			case 3:
				listaTrabajadores->pasarArbol();
				break;
			}
		}

		_getch();
		goto MENUPRINCIPAL;
	case 3:
		cout << "Presione cualquier tecla";
		break;
	}


	_getch();
	return 0;
}