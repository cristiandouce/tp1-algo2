/**
 * Name        : main.cpp
 * Authors     : Dreiling, Augusto <augusto.dreiling@gmail.com>
 *             : Douce Suarez, Cristian G. <cristiandouce@yahoo.com.ar>
 * Version     : 1.0.0
 * License     : MIT
 * Description : Linea de comando que implementa DFT/IDFT sobre senales
 *               de entrada de variable real o compleja.
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include <vector>
#include <string>
#include <algorithm>

#include "vendor/complejo.cpp"
#include "vendor/cmdline.cpp"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_method(string const &);
static void opt_help(string const &);

/**
 * Tabla de opciones de linea de comando. El formato de la tabla
 * consta de un elemento por cada opcion a definir. A su vez, en
 * cada entrada de la tabla tendremos:
 *
 * o La primera columna indica si la opcion lleva (1) o no (0) un
 *   argumento adicional.
 *
 * o La segunda columna representa el nombre corto de la opcion.
 *
 * o La tercera columna determina el nombre largo de la opcion.
 *
 * o La cuarta columna contiene el valor por defecto a asignarle
 *   a esta opcion en caso que no esta explicitamente presente
 *   en la linea de comandos del programa. Si la opcion no tiene
 *   argumento (primera columna nula), todo esto no tiene efecto.
 *
 * o La quinta columna apunta al metodo de parseo de la opcion,
 *   cuyo prototipo debe ser siempre void (*m)(string const &arg);
 *
 * o La ultima columna sirve para especificar el comportamiento a
 *   adoptar en el momento de procesar esta opcion: cuando la
 *   opcion es obligatoria, debera activarse OPT_MANDATORY.
 *
 * Ademas, la ultima entrada de la tabla debe contener todos sus
 * elementos nulos, para indicar el final de la misma.
 */

/**************** Elementos globales ******************/
static option_t options[] = {
	{ 1, "i", "input", "-", opt_input, OPT_DEFAULT },
	{ 1, "o", "output", "-", opt_output, OPT_DEFAULT },
	{ 1, "m", "method", "DFT", opt_method, OPT_DEFAULT },
	{ 0, "h", "help", NULL, opt_help, OPT_DEFAULT },
	{ 0, },
};

static string metodo;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		  // Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		    // Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)



/*****************************************************/

static void
opt_input(string const &arg) {
	// Si el nombre del archivos es "-", usaremos la entrada
	// estandar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	if (arg == "-") {
		// Establezco la entrada estandar cin como flujo de entrada
		iss = &cin;
	} else {
		// c_str(): Returns a pointer to an array that contains a null-terminated
		// sequence of characters (i.e., a C-string) representing
		// the current value of the string object.
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		// EXIT: Terminacion del programa en su totalidad
		exit(1);
	}
}

static void
opt_output(string const &arg) {
	// Si el nombre del archivos es "-", usaremos la salida
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		// Establezco la salida estandar cout como flujo de salida
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		// EXIT: Terminacion del programa en su totalidad
		exit(1);
	}
}

static void
opt_method(string const &arg) {
	// Intentamos extraer el metodo de la linea de comandos (DFT o IDFT).
	//
	if (arg == "DFT") {
		// Establezco metodo como DFT
		metodo = "dft";
	} else if (arg == "IDFT") {
		// Establezco metodo como IDFT
		metodo = "idft";
	} else {
		cerr << "cannot read method."
		     << endl;
		// EXIT: Terminacion del programa en su totalidad
		exit(1);
	}
}

static void
opt_help(string const &arg) {
	cout << "tp1 [-m method] [-i file] [-o file]"
	     << endl;
	exit(0);
}

/**
 * @brief Escribe linea de de salida desde el vector procesado
 *
 * @param p_os
 * @param vector
 * @return int
 */
int
write_signal_line(ostream *p_os, vector<complejo> & salida) {
	int ret = 0;
	vector<complejo>::iterator it = salida.begin();

	do {
		*p_os << *it << " ";
		it += 1;
	} while (it != salida.end());

	*p_os << endl;

	return ret;
}

/**
 * @brief Lee linea de entrada y agrega valores complejos al vector
 *
 * @param p_is puntero a input stream
 * @param vector vector de complejos
 * @return int
 */
int
parse_signal_line(istream *p_is, vector<complejo> & vector) {
	complejo a;
	string line;

	getline(*p_is, line);

	stringstream linestream(line);

	while ( linestream >> a ) {
		vector.push_back(a);
	}

	// Error de formato en input
	if (linestream.bad()) {
		cerr << "cannot read from input stream."
		     << endl;
		exit(1);
	}

	// Chequeo fin de archivo
	if( p_is->eof() ){
		return 0;
	}

	return 0;
}

void
DFT(vector<complejo> &entrada, vector<complejo> &salida, int inverse = 0) {
	// NOTE: retorno rapido si no hay nada que procesar
	//       en el arreglo de entrada.
	if (entrada.size() == 0) { return; }

	double k, n, N = entrada.size();
	double arg, norm = inverse ? 1/N : 1;
	complejo acum, j = inverse ? complejo(0, -1) : complejo(0, 1);
	vector<complejo>::iterator x;

	for (k = 0 ; k < N; ++k) {
		// arranco en el primer elemento
		x = entrada.begin();
		acum = 0;
		n = 0;

		// repito hasta el ultimo elemento de entrada
		// la sumatoria de los x[n] * W(kn, N)
		do {
			arg = 2 * M_PI * k * n / N;
			acum += (*x) * (cos(arg) + j.conjugado() * sin(arg));
			n += 1;
			x +=1;
		} while(x != entrada.end());

		// multiplicamos por el normalizador que
		// corresponda segun el modo
		acum *= norm;

		// agrego el acumulado a la salida
		salida.push_back(acum);
	}
}

int
process(istream *p_is, ostream *p_os) {
	int inputReturn = -1;
	int outputReturn = -1;

	vector<complejo> vectorEntrada;
	vector<complejo> vectorSalida;

	if(NULL == p_is) {
		cerr << "Error: Puntero NULL" << endl;
		return 1;
	}

	while(!p_is->eof()) {
		// NOTE: Vaciamos los vectores de ayuda antes de
		//			 usarlos para procesar las senales.
		vectorEntrada.clear();
		vectorSalida.clear();

		// Proceso el stream de entrada y escribo en
		// vectorEntrada
		inputReturn = parse_signal_line(p_is, vectorEntrada);

		// TODO: Cuando hay un error de formato de 1 linea leida
		//		     1. Se continua con la siguiente?
		//			   2. Se termina el programa?
		//			 Actualmente se termina la ejecucion ya que no hay
		//			 forma de volver del archivo de salida al original.
		if (inputReturn == 1) {
			return 1;
		}

		// NOTE: Si la lectura fue exitosa, escribimos la salida
		//			 en el ostream seleccionado.
		// TODO: Determinar qué hacer con el resultado de la
		//			 escritura a ostream. Manejo de errores?
		if (inputReturn == 0 && vectorEntrada.size() != 0) {
			DFT(vectorEntrada, vectorSalida, metodo == "dft" ? 0 : 1);
			write_signal_line(p_os, vectorSalida);
		}
	}

	return 0;
}

int
main(int argc, char * const argv[]) {
	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver linea 51 main.cc
	// Metodo de parseo de la clase cmdline
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	if (process(iss, oss)) {
		ifs.close();
		ofs.close();
		return 1;
	}

	ifs.close();
	ofs.close();
	return 0;
}
