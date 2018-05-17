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

#include <string>
#include <algorithm>

#include "vendor/cmdline.h"
#include "vendor/complejo.h"
#include "src/fourier.cpp"

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

enum Methods {DFT,IDFT,FFT,IFFT}; 

static Methods method;
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
		cerr << "cannot open " << arg << "." << endl;
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

	// Intentamos extraer el metodo de la linea de comandos (DFT, IDFT, FFT o IFFT). 
	// 
	if (arg == "DFT") { 
		// Establezco metodo como DFT 
		method = DFT; 
	} else if (arg == "IDFT") { 
		// Establezco metodo como IDFT 
		method = IDFT; 
	} else if (arg == "FFT") { 
		// Establezco metodo como IDFT 
		method = FFT; 
	} else if (arg == "IFFT") { 
		// Establezco metodo como IDFT 
		method = IFFT; 				
	} else { 
		cerr << "La opcion 'method' provista es invalida." 
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

int
main(int argc, char * const argv[]) {
	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver linea 51 main.cc
	// Metodo de parseo de la clase cmdline
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	ft *myft = 0;

	if (method == DFT) {
		myft = new dft(iss, oss);
	} else if (method == IDFT) {
		myft = new idft(iss, oss);
	} else if (method == IFFT) {
		myft = new ifft(iss, oss);
	} else {
		myft = new fft(iss, oss);
	}

	myft->compute();

	delete myft;
	ifs.close();
	ofs.close();
	return 0;
}
