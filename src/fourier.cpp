#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <complex>
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

			// si la cantidad de elementos del vector no es potencia de 2, agregamos
			// 0s hasta completar tamaño con proxima potencia de 2
			unsigned int tam = input_.tamano();			
			bool powerOfTwo = !(tam == 0) && !(tam & (tam - 1));
			if( !powerOfTwo ){				
				unsigned int v = tam;
				v--;
				v |= v >> 1;
				v |= v >> 2;
				v |= v >> 4;
				v |= v >> 8;
				v |= v >> 16;
				v++;		

				for(int i=0; i < (v-tam) ; i++){
					complejo aux(0.0,0.0);
					input_.insertar_despues(aux, it);
					it = input_.ultimo();					
				}
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
			is_ = &cin;
			os_ = &cout;
		}

		ft(istream *is) {			
			is_ = is;
			os_ = &cout;
		}

		ft(ostream *os) {			
			is_ = &cin;
			os_ = os;
		}

		ft(istream *is, ostream *os) {			
			is_ = is;
			os_ = os;
		}

		virtual ~ft() {			
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
				} while( !x.extremo() );

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
			is_ = &cin;
			os_ = &cout;
		}

		dft(istream *is) {			
			is_ = is;
			os_ = &cout;
		}

		dft(ostream *os) {			
			is_ = &cin;
			os_ = os;
		}

		dft(istream *is, ostream *os) {			
			is_ = is;
			os_ = os;
		}

		~dft() {			
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
			is_ = &cin;
			os_ = &cout;
		}

		idft(istream *is) {			
			is_ = is;
			os_ = &cout;
		}

		idft(ostream *os) {			
			is_ = &cin;
			os_ = os;
		}

		idft(istream *is, ostream *os) {			
			is_ = is;
			os_ = os;
		}

		~idft() {			
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
	
			double norm = get_norm();

			while(!it.extremo()){
				*os_ << it.dato() * norm << " ";
				it.avanzar();
			} 

			*os_ << endl;
		}

		lista<complejo> recursive_algorithm(lista<complejo> &v) {
			int N = v.tamano();

			if (N <= 1) {
				return v;
			}			

			lista<complejo> v_even_parts;
			lista<complejo> v_odd_parts;
			particion(v, v_even_parts, v_odd_parts);

			lista<complejo> G = recursive_algorithm(v_even_parts);
			lista<complejo> H = recursive_algorithm(v_odd_parts);

			return recompone(G, H, N);
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
			} while (!it.extremo());
		}

		lista<complejo> recompone(lista<complejo> &G, lista<complejo> &H, int N) {
			lista<complejo> X;

			lista<complejo>::iterador it_G = G.primero();
			lista<complejo>::iterador it_H = H.primero();
			lista<complejo>::iterador it_X = X.ultimo();

			double arg;
			complejo j = get_exp_complejo();
			complejo w;

			// combine
			//Para X[k] con 0 < k < N/2
			for (int k = 0; k < N/2; ++k)
			{
				arg = 2 * M_PI * k  / N;
				w = (cos(arg) + j.conjugado() * sin(arg));
			
				complejo t = w * it_H.dato();				
				X.insertar_despues(it_G.dato()+t,it_X);
				if(!it_G.extremo()) it_G.avanzar();
				if(!it_H.extremo()) it_H.avanzar();	
				it_X = X.ultimo();
			}	

			it_G = G.primero();
			it_H = H.primero();

			//Para X[k] con N/2 < k < N
			for (int k = 0; k < N/2; ++k)
			{
				arg = 2 * M_PI * k  / N;
				w = (cos(arg) + j.conjugado() * sin(arg));
			
				complejo t = w * it_H.dato();				
				X.insertar_despues(it_G.dato()-t,it_X);
				if(!it_G.extremo()) it_G.avanzar();
				if(!it_H.extremo()) it_H.avanzar();	
				it_X = X.ultimo();
			}	
			return X;
		}

	// public members
	public:
		fft() {			
			is_ = &cin;
			os_ = &cout;
		}

		fft(istream *is) {			
			is_ = is;
			os_ = &cout;
		}

		fft(ostream *os) {			
			is_ = &cin;
			os_ = os;
		}

		fft(istream *is, ostream *os) {			
			is_ = is;
			os_ = os;
		}

		~fft() {			
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
			is_ = &cin;
			os_ = &cout;
		}

		ifft(istream *is) {
			is_ = is;
			os_ = &cout;
		}

		ifft(ostream *os) {			
			is_ = &cin;
			os_ = os;
		}

		ifft(istream *is, ostream *os) {			
			is_ = is;
			os_ = os;
		}

		~ifft() {			
		}
};