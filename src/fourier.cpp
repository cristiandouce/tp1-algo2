#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "../vendor/lista.h"
#include "../vendor/complejo.h"

using namespace std;

class ft {
	// private members

	// protected members
	protected:
		lista<complejo> input_;
		istream *is_;
		ostream *os_;

		void read_input_line() {
			complejo aux;
			string line;

			getline(*is_, line);

			stringstream linestream(line);

			// nos aseguramos que el input_ lista
			// este siempre vacío antes de empezar.
			input_.clear();

			lista<complejo>::iterador it;
			it = input_.ultimo();

			// leemos cada valor
			while(linestream >> aux) {
				input_.insertar_despues(aux, it);
				it = input_.ultimo();
			}

			// Error de formato en input stream.
			// Detenemos la ejecución del programa.
			if (linestream.bad()) {
				cerr << "cannot read from input stream." << endl;
				exit(1);
			}
		}

		double get_norm () {
			double N = input_.tamano();
			return inverse() && (N > 0) ? 1/N : 1;
		}

		complejo get_exp_complejo() {
			return inverse() ? complejo(0, -1) : complejo(0, 1);
		}

		virtual bool inverse() = 0;

		virtual void run_algorithm() = 0;

	// public members
	public:
		ft() {
			cout << "ft::ft()" << endl;
			is_ = &cin;
			os_ = &cout;
		}

		ft(istream *is) {
			cout << "ft::ft(istream)" << endl;
			is_ = is;
			os_ = &cout;
		}

		ft(ostream *os) {
			cout << "ft::ft(ostream)" << endl;
			is_ = &cin;
			os_ = os;
		}

		ft(istream *is, ostream *os) {
			cout << "ft::ft(istream, ostream)" << endl;
			is_ = is;
			os_ = os;
		}

		virtual ~ft() {
			cout << "ft::~ft()" << endl;
		}

		void compute() {
			while(!is_->eof()) {
				read_input_line();
				run_algorithm();
			}
		}
};

class dft : public ft {
	// private members

	// protected members
	protected:
		virtual bool inverse() {
			return false;
		}

		virtual void run_algorithm() {
			// NOTE: retorno rapido si no hay nada que procesar
			//       en el arreglo de input_.
			if (input_.tamano() == 0) { return; }

			double k, n, N = input_.tamano();
			double arg, norm = get_norm();
			complejo acum, j = get_exp_complejo();
			lista<complejo>::iterador x;

			for (k = 0 ; k < N; ++k) {
				// arranco en el primer elemento
				x = input_.primero();
				acum = 0;
				n = 0;

				// repito hasta el ultimo elemento de entrada
				// la sumatoria de los x[n] * W(kn, N)
				do {
					arg = 2 * M_PI * k * n / N;
					acum += (x.dato()) * (cos(arg) + j.conjugado() * sin(arg));
					n += 1;
					x.avanzar();
				} while(x != input_.ultimo());

				// multiplicamos por el normalizador que
				// corresponda segun el modo
				acum *= norm;

				// escribo el acumulado a la salida una vez
				// terminado de procesar el k-esimo elemento
				// de la DFT/IDFT
				*os_ << acum << " ";
			}

			// termino de escribir al stream de salida
			*os_ << endl;
		}

	// public members
	public:
		dft() {
			cout << "dft::dft()" << endl;
			is_ = &cin;
			os_ = &cout;
		}

		dft(istream *is) {
			cout << "dft::dft(istream)" << endl;
			is_ = is;
			os_ = &cout;
		}

		dft(ostream *os) {
			cout << "dft::dft(ostream)" << endl;
			is_ = &cin;
			os_ = os;
		}

		dft(istream *is, ostream *os) {
			cout << "dft::dft(istream, ostream)" << endl;
			is_ = is;
			os_ = os;
		}

		~dft() {
			cout << "dft::~dft()" << endl;
		}
};

class idft : public dft {
	// private members

	// protected members
	protected:
		virtual bool inverse() {
			return true;
		}

		virtual void run_algorithm() {
			dft::run_algorithm();
		}

	// public members
	public:
		idft() {
			cout << "idft::idft()" << endl;
			is_ = &cin;
			os_ = &cout;
		}

		idft(istream *is) {
			cout << "idft::idft(istream)" << endl;
			is_ = is;
			os_ = &cout;
		}

		idft(ostream *os) {
			cout << "idft::idft(ostream)" << endl;
			is_ = &cin;
			os_ = os;
		}

		idft(istream *is, ostream *os) {
			cout << "idft::idft(istream, ostream)" << endl;
			is_ = is;
			os_ = os;
		}

		~idft() {
			cout << "idft::~idft()" << endl;
		}
};

class fft : public ft {
	// private members

	// protected members
	protected:
		virtual bool inverse() {
			return false;
		}

		virtual void run_algorithm() {
			lista<complejo> X = recursive_algorithm(input_);
			lista<complejo>::iterador it = X.primero();

			do {
				*os_ << it.dato() << " ";
				it.avanzar();
			} while(it != X.ultimo());

			*os_ << endl;
		}

		lista<complejo> recursive_algorithm(lista<complejo> &v) {
			double N = v.tamano();

			if (N == 1) {
				return v;
			}

			int m = N/2;

			lista<complejo> v_even_parts;
			lista<complejo> v_odd_parts;
			particion(v, v_even_parts, v_odd_parts);

			lista<complejo> G = recursive_algorithm(v_even_parts);
			lista<complejo> H = recursive_algorithm(v_odd_parts);

			// TODO: La estructura actual es la esperada para la descomposicion
			//			 division y recursion (DyV) del algoritmo. Los elementos restantes
			//			 se listan en la siguiente lista:
			//				- Implementar el conjugado segun inverso o directo
			//  			- Implementar el normalizador 1/N o 1 segun inverso o directo
			//  			- Implementar recomposicion ordenada de las partes par/impar
			return recompone(G, H, m);
		}

		void particion(lista<complejo> &v, lista<complejo> &even, lista<complejo> &odd) {
			int N = v.tamano();
			int i = 0;
			lista<complejo>::iterador it = v.primero();
			lista<complejo>::iterador itOdd;
			lista<complejo>::iterador itEven;

			do {
				if (i % 2) {
					itOdd = odd.ultimo();
					odd.insertar_despues(it.dato(),itOdd);
				} else {
					itEven = even.ultimo();
					even.insertar_despues(it.dato(),itEven);
				}

				i++;
				it.avanzar();
			} while (it != v.ultimo());
		}

		lista<complejo> recompone(lista<complejo> &G, lista<complejo> &H, int m) {
			lista<complejo> X;
			//X.insert(X.end(), G.begin(), G.end());
			//X.insert(X.end(), H.begin(), H.end());
			return X;
		}

	// public members
	public:
		fft() {
			cout << "fft::fft()" << endl;
			is_ = &cin;
			os_ = &cout;
		}

		fft(istream *is) {
			cout << "fft::fft(istream)" << endl;
			is_ = is;
			os_ = &cout;
		}

		fft(ostream *os) {
			cout << "fft::fft(ostream)" << endl;
			is_ = &cin;
			os_ = os;
		}

		fft(istream *is, ostream *os) {
			cout << "fft::fft(istream, ostream)" << endl;
			is_ = is;
			os_ = os;
		}

		~fft() {
			cout << "fft::~fft()" << endl;
		}
};

class ifft : public fft {
	// private members

	// protected members
	protected:
		virtual bool inverse() {
			return true;
		}

		virtual void run_algorithm() {
			fft::run_algorithm();
		}

	// public members
	public:
		ifft() {
			cout << "ifft::ifft()" << endl;
			is_ = &cin;
			os_ = &cout;
		}

		ifft(istream *is) {
			cout << "ifft::ifft(istream)" << endl;
			is_ = is;
			os_ = &cout;
		}

		ifft(ostream *os) {
			cout << "ifft::ifft(ostream)" << endl;
			is_ = &cin;
			os_ = os;
		}

		ifft(istream *is, ostream *os) {
			cout << "ifft::ifft(istream, ostream)" << endl;
			is_ = is;
			os_ = os;
		}

		~ifft() {
			cout << "ifft::~ifft()" << endl;
		}
};