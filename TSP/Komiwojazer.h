#ifndef Komiwojazer_h
#define Komiwojazer_h

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include <vector>


#define M_E 2.718281828459045235360287	//przyblizona wartosc e

using namespace std;

class zakazane{
public:

	int pos_x;
	int pos_y;
	int kadencja;

	zakazane();
	zakazane(int x, int y, int kad);

};

class TSP {

private:
	double **_macierzKosztow;
	double *_wspolczynniki;

	//tablice dla problemu symetrycznego
	double *tabX, *tabY;

	//tabuSearch
	vector<zakazane> tabuList;
	int maxRozmiarTabu;


	double temperatura;
	int *minimalnaDroga, *nowaDroga;
	double minimalnyKoszt;
	double najlepszyAktualnieKoszt;

	double _optymalna;
	int _iloscMiast;

public:

	TSP();
	TSP(int iloscMiast, double optymalna);
	~TSP();

	//funkcje do wyswietlania
	void wyswietlMiasta(); //wyswietla macierz kosztow
	void wyswietlMiastaKoordynaty(); //wyswietla koordynaty dla przypadku symetrycznego
	void wyswietlWynik(); //wyswietla wynik algorytmu
	void najkrotszaDroga(); //wyswietla najkrotsza droge

	//funkcje do obliczen
	void obliczTemperature(); //oblicza minimalna temperature na podstawie sredniej z (_iloscmiast) rozwiazan
	void wstawKosztaDoMacierzy(); //dla przypadku symetrycznego, funkcja liczy i wstawia koszty do macierzy
	double obliczKoszt(int a, int b); //liczy koszt z podanych wspolrzednych dla przypadku symetrycznego
	void wstawOznaczenieDrogi(); //tworzy tablice zawietajace podstawowa droge, od 0 to (_iloscmiast-1)
	double koszt(int *droga); //oblicza koszt dla danej drogi
	double stosunekOptDoMin(); //wylicza stosunek optymalnego wyniku do minimalnego otrzymanego z algorytmu

	//funkcje dla tabuSearch
	void dodajDoTabu(int a, int b);
	bool czyJestNaLiscie(int a, int b);
	int * sprawdzSasiada(int *droga);
	void zmniejszKadencje();
	void generatorRozwiazania();

	//algorytm symulowanego wyzarzania
	void symulowaneWyzarzanie();
	void tabuSearch();

	//funkcje do wprowadzania danych z pliku
	void stworzZPlikuAsymetryczny(string fileName); //wprowadzanie danych dla przypadku asymetrycznego
	void stworzZPlikuSymetryczny(string fileName); //wprowadzanie danych dla przypadku symetrycznego
	void wczytajWspolczynniki(string fileName); //wczytywanie wspolczynnikow ochladzania
};



#endif