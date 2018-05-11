#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include <string>
#include <vector>

#include "../vendor/complejo.cpp"

using namespace std;

class ft {
	// private members

	// protected members
	protected:
		vector<complejo> input_;
		istream *is_;
		ostream *os_;

		void read_input_line() {
			complejo aux;
			string line;

			getline(*is_, line);

			stringstream linestream(line);

			// nos aseguramos que el input_ vector
			// este siempre vacío antes de empezar.
			input_.clear();

			// leemos cada valor
			while(linestream >> aux) {
				input_.push_back(aux);
			}

			// Error de formato en input stream.
			// Detenemos la ejecución del programa.
			if (linestream.bad()) {
				cerr << "cannot read from input stream." << endl;
				exit(1);
			}
		}

		double get_norm () {
			double N = input_.size();
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

		~ft() {
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
			if (input_.size() == 0) { return; }

			double k, n, N = input_.size();
			double arg, norm = get_norm();
			complejo acum, j = get_exp_complejo();
			vector<complejo>::iterator x;

			for (k = 0 ; k < N; ++k) {
				// arranco en el primer elemento
				x = input_.begin();
				acum = 0;
				n = 0;

				// repito hasta el ultimo elemento de entrada
				// la sumatoria de los x[n] * W(kn, N)
				do {
					arg = 2 * M_PI * k * n / N;
					acum += (*x) * (cos(arg) + j.conjugado() * sin(arg));
					n += 1;
					x +=1;
				} while(x != input_.end());

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

class fft : public dft {
	// private members

	// protected members
	protected:
		virtual bool inverse() {
			return false;
		}

		virtual void run_algorithm() {
			dft::run_algorithm();
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