#include "Komiwojazer.h"
#include "miernikCzasu.h"

zakazane::zakazane() {
}

zakazane::zakazane(int x, int y, int kad) {
	pos_x = x;
	pos_y = y;
	kadencja = kad;
}


TSP::TSP() {
	_iloscMiast = 0;
}

TSP::TSP(int iloscMiast, double optymalna) {

	_iloscMiast = iloscMiast;
	_optymalna = optymalna;

	_macierzKosztow = new double *[iloscMiast];

	for (int i = 0; i < iloscMiast; i++) _macierzKosztow[i] = new double[iloscMiast];

	for (int i = 0; i < iloscMiast; i++)
		for (int j = 0; j < iloscMiast; j++) {
			_macierzKosztow[i][j] = 0;
		}

}

TSP::~TSP() {

	for (int i = 0; i < _iloscMiast; i++) {
		delete[] _macierzKosztow[i];
	}
	delete[] _macierzKosztow;
	_macierzKosztow = NULL;

	delete[] minimalnaDroga;
	minimalnaDroga = NULL;

	delete[] nowaDroga;
	nowaDroga = NULL;

	delete[] tabX;
	tabX = NULL;

	delete[] tabY;
	tabY = NULL;
}

//------------------------------------------------------------------------------------------------ funkcje do wyswietlania

void TSP::wyswietlMiasta() {

	for (int i = 0; i < _iloscMiast; i++) {
		for (int j = 0; j < _iloscMiast; j++) {
			cout << std::setw(6) << _macierzKosztow[i][j] << " ";
		}
		cout << endl;
	}

}

void TSP::wyswietlMiastaKoordynaty() {

	for (int i = 0; i < _iloscMiast; i++) {

		cout << std::setw(6) << i << " " << tabX[i] << " " << tabY[i] << endl;

	}
}

void TSP::wyswietlWynik() {

	//cout << "Temperatura: " << temperatura << endl;
	cout << "Optymalna droga: " << _optymalna << endl;
	cout << "Koszt dla minimalnej drogi z algorytmu: " << koszt(minimalnaDroga) << endl;
	cout << "Stosunek otrzymanego wyniku do optymalnego: " << stosunekOptDoMin() << "%" << endl;

}

void TSP::najkrotszaDroga() {
	cout << "Najktorsza uzyskana droga " << koszt(minimalnaDroga) << endl;
	//for (int i = 0; i< _iloscMiast ; i++)
	//	cout << minimalnaDroga[i] << " ";
	cout << endl;
}

//------------------------------------------------------------------------------------------------ funkcje do wyswietlania

//------------------------------------------------------------------------------------------------ funkcje do obliczen

void TSP::obliczTemperature() {

	double srednia = 0.0;
	int r1, r2;
	int temp;
	int *przejsciowaDroga;
	przejsciowaDroga = new int[_iloscMiast];

	for (int i = 0; i < _iloscMiast; i++) {
		przejsciowaDroga[i] = i;
	}

	for (int i = 0; i < _iloscMiast; i++) {
		for (int i = 0; i < _iloscMiast / 2; i++) {
			r1 = rand() % _iloscMiast;
			r2 = rand() % _iloscMiast;

			if (r1 != r2) {
				temp = przejsciowaDroga[r1];
				przejsciowaDroga[r1] = przejsciowaDroga[r2];
				przejsciowaDroga[r2] = temp;
			}
		}

		srednia += koszt(przejsciowaDroga);
	}

	temperatura = srednia / _iloscMiast;

	delete[] przejsciowaDroga;
	przejsciowaDroga = NULL;

}

void TSP::wstawKosztaDoMacierzy() {

	for (int i = 0; i < _iloscMiast; i++) {
		for (int j = 0; j < _iloscMiast; j++) {
			if (i != j) {
				_macierzKosztow[i][j] = obliczKoszt(i, j);
			}
		}
	}

}

double TSP::obliczKoszt(int a, int b) {

	return sqrt(pow(tabX[b] - tabX[a], 2.0) + pow(tabY[b] - tabY[a], 2.0));

}

void TSP::wstawOznaczenieDrogi() {

	delete[] minimalnaDroga;

	delete[] nowaDroga;


	minimalnaDroga = new int[_iloscMiast];
	//minimalnaDroga[_iloscMiast] = 0;
	for (int i = 0; i < _iloscMiast; i++)
		minimalnaDroga[i] = i;

	nowaDroga = new int[_iloscMiast];
	//nowaDroga[_iloscMiast] = 0;
	for (int i = 0; i < _iloscMiast; i++)
		nowaDroga[i] = i;


}

double TSP::koszt(int *droga) {

	double koszta = 0;
	for (int i = 0; i < _iloscMiast; i++)
		if (i == _iloscMiast - 1) {
			koszta += _macierzKosztow[droga[i]][droga[0]];
		}
		else koszta += _macierzKosztow[droga[i]][droga[i + 1]];
		return koszta;

}

double TSP::stosunekOptDoMin() {
	double result = (minimalnyKoszt / _optymalna) * 100;
	return result;
}
//------------------------------------------------------------------------------------------------ funkcje do obliczen

//------------------------------------------------------------------------------------------------ funkcje dla tabuSearch



void TSP::dodajDoTabu(int a, int b) {

	int k = _iloscMiast;

	//if (tabuList.size() < maxRozmiarTabu) {
	//	tabuList.push_back(zakazane(a, b, k));
	//}
	//else {
	//	tabuList.at(0).pos_x = a;
	//	tabuList.at(0).pos_y = b;
	//	tabuList.at(0).kadencja = k;
	//}
	if ((a != 0 && b == 0) || (a == 0 && b != 0) || (a != 0 && b != 0)) {
		if (tabuList.size() < maxRozmiarTabu) {
			tabuList.push_back(zakazane(a, b, k));
		}
		else {
			tabuList.at(0) = zakazane(a, b, k);
		}
	}
}


bool TSP::czyJestNaLiscie(int a, int b) {

	for (int i = 0; i < tabuList.size(); i++) {
		if ((tabuList.at(i).pos_x == a && tabuList.at(i).pos_y == b || tabuList.at(i).pos_y == a && tabuList.at(i).pos_x == b) && tabuList.at(i).kadencja > 0) {
			return true;
		}
	}

	return false;
}

int * TSP::sprawdzSasiada(int *droga) {

	int r1, r2, temp; //zmienne losowe
	double  kosztTemp;
	int *tempDroga = new int[_iloscMiast];
	int *tempDroga2 = new int[_iloscMiast];
	int licznik = 0;
	int bestR1 = 0, bestR2 = 0;


	kosztTemp = koszt(droga);
	
	for (int i = 0; i < _iloscMiast; i++) {
		tempDroga[i] = droga[i];
		tempDroga2[i] = droga[i];
	}

	double kosztTemp2 = koszt(tempDroga);

	bool JestNaLiscie = true;
	for (int asd = 0; asd < _iloscMiast/2; asd++) {

		//bestR1 = 0; bestR2 = 0;

		for (int lel = 0; lel < _iloscMiast; lel++) {
			do {
				r1 = rand() % _iloscMiast;
				r2 = rand() % _iloscMiast;
			} while (r1 == r2);

			JestNaLiscie = czyJestNaLiscie(r1, r2);


			if (JestNaLiscie == false) {

				temp = tempDroga[r1];
				tempDroga[r1] = tempDroga[r2];
				tempDroga[r2] = temp;


				if (((koszt(tempDroga) < kosztTemp)) || (koszt(tempDroga) < koszt(minimalnaDroga))) { //sprawdza czy jest an liscie, uwzgledniajac kryterium aspiracji


					for (int j = 0; j < _iloscMiast; j++) {
						droga[j] = tempDroga[j];
					}

					kosztTemp = koszt(droga);
					bestR1 = r1;
					bestR2 = r2;

				}


			}

			if ((kosztTemp2 > koszt(tempDroga))) {
				bestR1 = r1;
				bestR2 = r2;
				kosztTemp2 = koszt(tempDroga);
			}



			temp = tempDroga[r1];
			tempDroga[r1] = tempDroga[r2];
			tempDroga[r2] = temp;
			//cout << "dodano " << r1 << " " << r2 << endl << "rozmiar tablicy " << tabuList.size() << endl;
		}
		dodajDoTabu(bestR1, bestR2);
		//if (tabuList.size() > 20) cout << tabuList.size() << endl;
		zmniejszKadencje();
	}
	
	delete []tempDroga;
	delete[]tempDroga2;
	return droga;
}

void TSP::zmniejszKadencje() {
	for (int i = 0; i < tabuList.size(); i++) {
		tabuList.at(i).kadencja--;
		if (tabuList.at(i).kadencja == 0) {
			if (i == tabuList.size() - 1) {
				tabuList.pop_back();
				break;
			}
			else {
				swap(tabuList.at(i), tabuList.at(tabuList.size() - 1));
				tabuList.pop_back();
			}
		}
	}
}

void TSP::generatorRozwiazania() {
	int r1, r2; //zmienne losowe
	int temp;
	for (int i = 0; i < _iloscMiast; i++)
		minimalnaDroga[i] = i;

	for (int i = 0; i < _iloscMiast; i++)
		nowaDroga[i] = i;

	for (int i = 0; i < _iloscMiast; i++) {
		r1 = rand() % _iloscMiast;
		r2 = rand() % _iloscMiast;

		if (r1 != r2) {
			temp = minimalnaDroga[r1];
			minimalnaDroga[r1] = minimalnaDroga[r2];
			minimalnaDroga[r2] = temp;
		}
	}

	for (int i = 0; i < _iloscMiast; i++) {
		nowaDroga[i] = minimalnaDroga[i];
	}
}
//------------------------------------------------------------------------------------------------ funkcje dla tabuSearch

//------------------------------------------------------------------------------------------------ sumulowane wyzarzanie
void TSP::symulowaneWyzarzanie() {
	int inkrementacja = 0;
	int r1, r2; //zmienne losowe
	int temp;
	double zysk;
	double p, pt;
	bool petla = true;
	double temperatura2;

	Miernik *czas;
	czas = new Miernik();

	wstawOznaczenieDrogi();
	obliczTemperature();

	for (int i = 0; i < 5; i++) {
		petla = true;
		czas->czasStart();
		temperatura2 = temperatura;

		for (int i = 0; i < _iloscMiast; i++)
			minimalnaDroga[i] = i;

		for (int i = 0; i < _iloscMiast; i++)
			nowaDroga[i] = i;

		for (int i = 0; i < _iloscMiast; i++) {
			r1 = rand() % _iloscMiast;
			r2 = rand() % _iloscMiast;

			if (r1 != r2) {
				temp = minimalnaDroga[r1];
				minimalnaDroga[r1] = minimalnaDroga[r2];
				minimalnaDroga[r2] = temp;
			}
		}

		for (int i = 0; i < _iloscMiast; i++) {
			nowaDroga[i] = minimalnaDroga[i];
		}

		while (petla) {
			//while (temperatura > 0.3) {

			for (int i = 0; i < _iloscMiast; i++) {
				nowaDroga[i] = minimalnaDroga[i];
			}

			do {
				r1 = rand() % _iloscMiast;
				r2 = rand() % _iloscMiast;

				if (r1 != r2) {
					temp = nowaDroga[r1];
					nowaDroga[r1] = nowaDroga[r2];
					nowaDroga[r2] = temp;
				}
			} while (r1 == r2);

			zysk = koszt(nowaDroga) - koszt(minimalnaDroga);

			//p = 1 / (pow(M_E, (zysk / temperatura)));
			p = -(zysk / temperatura2);
			pt = pow(M_E, p);

			double losowa2 = (double)(rand() / (double)RAND_MAX);
			//cout << p;


			if ((koszt(nowaDroga) < koszt(minimalnaDroga)) || pt > losowa2) {
				for (int i = 0; i < _iloscMiast; i++) {
					minimalnaDroga[i] = nowaDroga[i];

				}
				//najkrotszaDroga();
				minimalnyKoszt = koszt(minimalnaDroga);
			}

			temperatura2 *= _wspolczynniki[inkrementacja];

			if (temperatura2 < 0.0001) {
				petla = false;
			}
		}
		czas->pobierzCzas();
		cout << "Wspolczynnik: " << _wspolczynniki[inkrementacja] << endl;
		wyswietlWynik();
		czas->wyswietlCzas();
		cout << "-------------------------------------------------------\n";
		czas->zerujCzas();
		inkrementacja++;
	}
}

void TSP::tabuSearch() {

	maxRozmiarTabu = _iloscMiast;

	int zleiteracje = 0;

	Miernik *czas;
	czas = new Miernik();


	wstawOznaczenieDrogi();
	generatorRozwiazania();

	czas->czasStart();

	int sad = 0;
	while (zleiteracje <= 50 * _iloscMiast && sad < 100000) {

		nowaDroga = sprawdzSasiada(nowaDroga);

		if (koszt(nowaDroga) < koszt(minimalnaDroga)) {

			for (int i = 0; i < _iloscMiast; i++) {
				minimalnaDroga[i] = nowaDroga[i];
			}

			minimalnyKoszt = koszt(minimalnaDroga);
			zleiteracje = 0;
		}
		else {
			zleiteracje++;

			//for (int i = 0; i < _iloscMiast; i++) {
			//	nowaDroga[i] = minimalnaDroga[i];
			//}
		}

		//zmniejszKadencje();
		sad++;
		//cout << zleiteracje << endl;
		if (sad == 100000) cout << "\n\nkurwa mac\n\n";

	}


	czas->pobierzCzas();
	wyswietlWynik();
	czas->wyswietlCzas();
	cout << "-------------------------------------------------------\n";
	czas->zerujCzas();
}


//------------------------------------------------------------------------------------------------ symulowane wyzarzanie


//------------------------------------------------------------------------------------------------ funkcje do wprowadzania danych z pliku
void TSP::stworzZPlikuAsymetryczny(string fileName) {
	int i = 0;

	fileName = fileName + ".txt";
	ifstream fileLoad(fileName);


	if (!fileLoad) {
		cout << "Nie mozna otworzyc pliku" << endl;
	}
	else {
		int l;
		fileLoad >> l;
		fileLoad >> l;
		while (!fileLoad.eof()) {
			if (i < _iloscMiast) {

				for (int i = 0; i < _iloscMiast; i++) {
					for (int j = 0; j < _iloscMiast; j++) {
						fileLoad >> _macierzKosztow[i][j];
					}
				}
			}
			else break;
		}
	}
	fileLoad.close();
}

void TSP::stworzZPlikuSymetryczny(string fileName) {
	int i = 0;

	fileName = fileName + ".txt";
	ifstream fileLoad(fileName);

	tabX = new double[_iloscMiast];
	tabY = new double[_iloscMiast];

	if (!fileLoad) {
		cout << "Nie mozna otworzyc pliku" << endl;
	}
	else {
		int l;
		int numeracja;
		fileLoad >> l;
		fileLoad >> l;
		while (!fileLoad.eof()) {
			if (i < _iloscMiast) {

				for (int i = 0; i < _iloscMiast; i++) {
					fileLoad >> numeracja;
					fileLoad >> tabX[i];
					fileLoad >> tabY[i];
				}
			}
			else break;
		}
	}
	fileLoad.close();

	wstawKosztaDoMacierzy();
}

void TSP::wczytajWspolczynniki(string fileName) {

	fileName = fileName + ".txt";
	ifstream fileLoad(fileName);

	int temp = 0;

	fileLoad >> temp;

	_wspolczynniki = new double[temp];

	for (int i = 0; i < temp; i++) {

		fileLoad >> _wspolczynniki[i];

	}

}

//------------------------------------------------------------------------------------------------ funkcje do wprowadzania danych z pliku