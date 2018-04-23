//##########################################################################################################################//
//Autor: Damian Kleska
//Nr indeksu: 218380
//Algorytm komiwojazera
//Wersja programu z dnia: 16.11.2016
//##########################################################################################################################//

//dorzucic rozne temperatury i wspolczynnik ochladzania, uwzglednic w sprawozdaniu
//temperatury i wspolczynniki chlodzenia z pliku
//plik startowy programu, pliki testowe, kod zrodlowy na plycie

#include "Komiwojazer.h"

#include <windows.h>

int decyzja; // zmienna decyzyjna - na przyszlosc
int n; // wczytanie liczby miast
int opt;
string fileName;
double temperatura1, ochladzanie;

//-------------------------------------------------------------------------------------wczytywanie
// wczytywanie rozmiaru
void wszytajRozmiarKomi(string fileName) {
	fileName = fileName + ".txt";
	ifstream fileLoad(fileName);

	fileLoad >> n;
	fileLoad >> opt;

	fileLoad.close();
}
//-------------------------------------------------------------------------------------wczytywanie


int main() {

	srand(time(NULL));

	fstream fileLoad;

	TSP *miasta;

	int decyzja = 0;
	bool d = true, b = true;

	do {
		cout << "#################################################################\n";
		cout << "#############      Problem komiwojazera        ##################\n";
		cout << "#############      Autor: Damian Kleska        ##################\n";
		cout << "#############      Indeks: 218380              ##################\n";
		cout << "#################################################################\n\n";
		cout << "Program zawiera rozne algorytmy  do realizacji problemu komiwojazera:\nKtory algorytm chcesz zrealizowac?\n";
		cout << "1. Symulowane wyzarzanie \n";
		cout << "2. TabuSearch \n";
		cout << "3. Koniec programi.\n";
		do {
			cin >> decyzja;
			if (decyzja <= 0 || decyzja > 3) cout << "Wprowadzono zla opcje.\nSprobuj poraz kolejny.\n";
		} while (decyzja <= 0 || decyzja > 3);

		// switch glowny
		switch (decyzja) {
			// case 1 switcha glownego
		case 1:
			cout << "1. Symetryczny\n2. Asymetryczny\n";
			do {
				cin >> decyzja;
				if (decyzja <= 0 || decyzja > 2) cout << "Wprowadzono zla opcje.\nSprobuj poraz kolejny.\n";
			} while (decyzja <= 0 || decyzja > 2);
			//switch dla symulowanego wyzarzania
			switch (decyzja) {
			case 1:

				d = true;

				cout << "Dostepne pliki z danymi: eil51, berlin52, st70, rat99, bier127, eil101, rat195.\nPodaj nazwe pliku z ktorego chcesz wczytac dane.\nWybieram plik: ";
				do {
					cin >> fileName;
				} while (fileName != "berlin52" && fileName != "eil51" && fileName != "eil101" && fileName != "st70" && fileName != "rat99" && fileName != "rat195" && fileName != "bier127");
				cout << endl;

				wszytajRozmiarKomi(fileName);
				miasta = new TSP(n, opt);


				miasta->stworzZPlikuSymetryczny(fileName);
				miasta->wczytajWspolczynniki("dane");

				do {
					cout << "\nCo chcesz zrobic?\n1.Wyswietl macierz kosztow.\n2.Wyswietl koordynaty\n3.Wykonaj algorytm.\n4.Wroc do menu.\n";
					do {
						cin >> decyzja;
						if (decyzja <= 0 || decyzja > 4) cout << "Wprowadzono zla opcje.\nSprobuj poraz kolejny.\n";
					} while (decyzja <= 0 || decyzja > 4);


					//switch dla symetrycznego wprowadzania
					switch (decyzja) {

					case 1:
						miasta->wyswietlMiasta();
						cout << endl;
						break;
					case 2:
						miasta->wyswietlMiastaKoordynaty();
						cout << endl;
						break;
					case 3:
						miasta->symulowaneWyzarzanie();
						cout << endl;
						break;
					case 4:
						d = false;
						miasta->~TSP();
						break;
					}
				} while (d == true);
				//koniec switcha dla symetrycznego wprowadzania

				break; //case 1 break dla symulowanego wyzarzania

			case 2:

				d = true;

				cout << "Dostepne pliki z danymi: ftv33, p43, ry48p, ft53, rbg323, rbg443.\nPodaj nazwe pliku z ktorego chcesz wczytac dane.\nWybieram plik: ";
				do {
					cin >> fileName;
				} while (fileName != "ftv33" && fileName != "ft53" && fileName != "p43" && fileName != "ry48p" && fileName != "rbg323" && fileName != "rbg443");
				cout << endl;

				wszytajRozmiarKomi(fileName);
				miasta = new TSP(n, opt);

				miasta->stworzZPlikuAsymetryczny(fileName);
				miasta->wczytajWspolczynniki("dane");

				do {

					cout << "\nCo chcesz zrobic?\n1.Wyswietl macierz kosztow.\n2.Wykonaj algorytm.\n3.Wroc do menu.\n";
					do {
						cin >> decyzja;
						if (decyzja <= 0 || decyzja > 3) cout << "Wprowadzono zla opcje.\nSprobuj poraz kolejny.\n";
					} while (decyzja <= 0 || decyzja > 3);

					//switch dla asymetrycznego wprowadzania
					switch (decyzja) {

					case 1:
						miasta->wyswietlMiasta();
						cout << endl;
						break;
					case 2:
						miasta->symulowaneWyzarzanie();
						cout << endl;
						break;
					case 3:
						d = false;
						miasta->~TSP();
						break;
					}
				} while (d == true);
				//koniec switcha dla asymetrycznego wprowadzania	

				break;
			}
			break;
			// koniec case 1 switcha glownego

		case 2:
			cout << "1. Symetryczny\n2. Asymetryczny\n";
			do {
				cin >> decyzja;
				if (decyzja <= 0 || decyzja > 2) cout << "Wprowadzono zla opcje.\nSprobuj poraz kolejny.\n";
			} while (decyzja <= 0 || decyzja > 2);
			//switch dla symulowanego wyzarzania
			switch (decyzja) {
			case 1:

				d = true;

				cout << "Dostepne pliki z danymi: eil51, berlin52, st70, rat99, bier127, eil101, rat195.\nPodaj nazwe pliku z ktorego chcesz wczytac dane.\nWybieram plik: ";
				do {
					cin >> fileName;
				} while (fileName != "berlin52" && fileName != "eil51" && fileName != "eil101" && fileName != "st70" && fileName != "rat99" && fileName != "rat195" && fileName != "bier127");
				cout << endl;

				wszytajRozmiarKomi(fileName);
				miasta = new TSP(n, opt);


				miasta->stworzZPlikuSymetryczny(fileName);
				miasta->wczytajWspolczynniki("dane");

				do {
					cout << "\nCo chcesz zrobic?\n1.Wyswietl macierz kosztow.\n2.Wyswietl koordynaty\n3.Wykonaj algorytm.\n4.Wroc do menu.\n";
					do {
						cin >> decyzja;
						if (decyzja <= 0 || decyzja > 4) cout << "Wprowadzono zla opcje.\nSprobuj poraz kolejny.\n";
					} while (decyzja <= 0 || decyzja > 4);


					//switch dla symetrycznego wprowadzania
					switch (decyzja) {

					case 1:
						miasta->wyswietlMiasta();
						cout << endl;
						break;
					case 2:
						miasta->wyswietlMiastaKoordynaty();
						cout << endl;
						break;
					case 3:
						miasta->tabuSearch();
						cout << endl;
						break;
					case 4:
						d = false;
						miasta->~TSP();
						break;
					}
				} while (d == true);
				//koniec switcha dla symetrycznego wprowadzania

				break; //case 1 break dla symulowanego wyzarzania

			case 2:

				d = true;

				cout << "Dostepne pliki z danymi: ftv33, p43, ry48p, ft53, rbg323, rbg443.\nPodaj nazwe pliku z ktorego chcesz wczytac dane.\nWybieram plik: ";
				do {
					cin >> fileName;
				} while (fileName != "ftv33" && fileName != "ft53" && fileName != "p43" && fileName != "ry48p" && fileName != "rbg323" && fileName != "rbg443");
				cout << endl;

				wszytajRozmiarKomi(fileName);
				miasta = new TSP(n, opt);

				miasta->stworzZPlikuAsymetryczny(fileName);
				miasta->wczytajWspolczynniki("dane");

				do {
					cout << "\nCo chcesz zrobic?\n1.Wyswietl macierz kosztow.\n2.Wykonaj algorytm.\n3.Wroc do menu.\n";
					do {
						cin >> decyzja;
						if (decyzja <= 0 || decyzja > 3) cout << "Wprowadzono zla opcje.\nSprobuj poraz kolejny.\n";
					} while (decyzja <= 0 || decyzja > 3);

					//switch dla asymetrycznego wprowadzania
					switch (decyzja) {

					case 1:
						miasta->wyswietlMiasta();
						cout << endl;
						break;
					case 2:
						miasta->tabuSearch();
						cout << endl;
						break;
					case 3:
						d = false;
						miasta->~TSP();
						break;
					}
				} while (d == true);
				//koniec switcha dla asymetrycznego wprowadzania	

				break;
			}
			break;
		case 3:
			b = false;
			break;
		}
		//koniec glownego switcha
	} while (b == true);


	cout << "\n\n<Kliknij ENTER, aby zakonczyc program>";

	cin.get();
	cin.get();
	return 0;
}