#ifndef miernikCzasu_h
#define miernikCzasu_h

#include <windows.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;


class Miernik {
private:
	double PCFreq;
	
	double czasOperacji;
	int iloscPomiarow;
	__int64 licznik;

public:
	double calkowityCzas;
	Miernik();

	void czasStart();
	void pobierzCzas();
	void wyswietlCzas();
	void wyswietlSredniCzas();
	void zerujCzas();

};



#endif