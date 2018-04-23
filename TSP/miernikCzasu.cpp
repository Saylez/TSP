#include "miernikCzasu.h"

Miernik::Miernik() {
	double PCFreq = 0.0;
	double calkowityCzas = 0;
	double czasOperacji = 0;
	int iloscPomiarow = 0;
	__int64 licznik = 0;
}

void Miernik::czasStart()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "Blad!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	licznik = li.QuadPart;
}
void Miernik::pobierzCzas()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	czasOperacji = (li.QuadPart - licznik) / PCFreq;
	calkowityCzas = calkowityCzas + (li.QuadPart - licznik) / PCFreq;
	iloscPomiarow++;
}

void Miernik::wyswietlCzas() {

	cout << endl;
	cout << "Operacja zajela: " << czasOperacji / 1000 << " sekund" << endl;
}
void Miernik::wyswietlSredniCzas() {
	cout << "Sredni czas wszystkich wykonanych operacji to " << (calkowityCzas / iloscPomiarow) / 1000 << "sekund" << endl;
	cout << " Ilosc wykonanych pomiarow : " << iloscPomiarow << endl;
}
void Miernik::zerujCzas() {
	iloscPomiarow = 0;
	calkowityCzas = 0;
}
