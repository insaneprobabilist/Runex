// Runex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <vector>
#include <algorithm> 
#include <ctime>
#include "md5.h"
#include "Uzytkownik.h"
#include "Bieg.h"

#pragma warning(disable : 4996)


using namespace std;


int iterPlik;

typedef unsigned long long int ulong;



bool walidujUrodz(string uro)
{
	int dl, ml, rl;
	string d = "";
	string m = "";
	string r = "";
	if (uro.length() != 10)return false;
	if ((int)uro[0] < 48 || (int)uro[0]>57) return false;
	if ((int)uro[1] < 48 || (int)uro[1]>57) return false;
	if ((int)uro[3] < 48 || (int)uro[3]>57) return false;
	if ((int)uro[4] < 48 || (int)uro[4]>57) return false;
	if ((int)uro[6] < 48 || (int)uro[6]>57) return false;
	if ((int)uro[7] < 48 || (int)uro[7]>57) return false;
	if ((int)uro[8] < 48 || (int)uro[8]>57) return false;
	if ((int)uro[9] < 48 || (int)uro[9]>57) return false;
	m = m + uro[3] + uro[4];
	ml = atoi(m.c_str());
	d = d + uro[0] + uro[1];
	dl = atoi(d.c_str());

	if (ml < 1 || ml >12)return false;
	if (dl == 0 || dl > 31)return false;
	if (dl == 31)
	{
		if (ml == 2 || ml == 4 || ml == 6 || ml == 9 || ml == 11)return false;
	}
	if (dl == 30 && ml == 2)return false;
	for (int i = 6;i <= 9;i++)
		r = r + uro[i];

	rl = atoi(d.c_str());
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);


	if (timePtr->tm_year + 1900 < rl)return false;

	return true;
}


void kasuj_wiersz(const std::string sciezka, const size_t wiersz)
{
	std::vector < std::string > vec;
	std::ifstream in(sciezka.c_str());
	std::string tmp;
	while (getline(in, tmp)) vec.push_back(tmp);

	in.close();
	std::ofstream out(sciezka.c_str());
	for (size_t i = 0; i < vec.size() - 1; ++i) {
		if (i + 1 != wiersz) out << vec[i] << std::endl;

	}
	if (vec.size() != wiersz)out << vec[vec.size() - 1];
	out.close();
}

void zamien_wiersz(const std::string sciezka, const std::string nowaLinia, const size_t wiersz)
{
	std::vector < std::string > vec;
	std::ifstream in(sciezka.c_str());
	std::string tmp;
	while (getline(in, tmp)) vec.push_back(tmp);

	in.close();
	std::ofstream out(sciezka.c_str());
	for (size_t i = 0; i < vec.size() - 1; ++i) {
		if (i + 1 != wiersz) out << vec[i] << std::endl;
		else out << nowaLinia << std::endl;

	}

	if (vec.size() != wiersz) out << vec[vec.size() - 1];
	else out << nowaLinia;

	out.close();
}







Uzytkownik logowanie()
{

	iterPlik = -5;
	string odczytUser;
	string odczytHaslo;
	string odczytNrKarty;
	string odczytImie, odczytNazwisko, odczytPesel;
	fstream plik;
	int proby = 3;
	bool dostep = false;
	int iter = 0;
	string user;
	string haslo;
	char znakHasla;
	cout << "Logowanie" << endl;
	while (proby--)
	{
		haslo = "";
		dostep = false;
		iter = 0;

		cout << "USER:  ";
		cin >> user;
		user = md5(user);
		cout << "HASLO: ";
		do
		{
			znakHasla = _getch();

			if (znakHasla != 13 && znakHasla != 8)
			{
				cout << "*";
				haslo += (char)znakHasla;
			}
		} while (znakHasla != 13);
		//cout << haslo << endl;
		haslo = md5(haslo);
		plik.open("Uzytkownicy.txt", ios::in);
		if (plik.good() == true)
		{
			iterPlik = -5;
			while (!plik.eof())
			{
				//cout << iterPlik << endl;
				iterPlik = iterPlik + 6;
				getline(plik, odczytNrKarty);
				getline(plik, odczytImie);
				getline(plik, odczytNazwisko);
				getline(plik, odczytPesel);


				getline(plik, odczytUser);
				getline(plik, odczytHaslo);
				if (odczytUser == user)
				{
					if (odczytHaslo == haslo)
					{
						dostep = true;
						break;
					}
				}


			}
			plik.close();
		}

		system("cls");
		if (dostep == true)break;

		else	cout << "Bledne haslo! Pozostale proby: " << proby << endl;

	}
	//Zalogowano
	if (!dostep)
	{
		exit(0);
	}
	cout << "Przyznano dostep! ";
	ulong nrKarty = atoi(odczytNrKarty.c_str());
	Uzytkownik uzytkownik(odczytImie, odczytNazwisko, odczytPesel, nrKarty, odczytUser, odczytHaslo);
	return uzytkownik;
}


void rejestracja()
{
	string odczytUser;
	string odczytHaslo;
	string odczytNrKarty;
	ulong nrKartyMax;
	string imie, nazwisko;
	string dataUrodzenia;
	string login, haslo, haslo1;
	ulong id;
	cout << "REJESTRACJA" << endl;
	cout << "IMIE: ";
	while (!(cin >> imie))
	{
		cin.clear();
		cin.sync();
		cout << "Bledne dane!\n";
		cout << "IMIE: ";
	}
	cout << "NAZWISKO: ";
	while (!(cin >> nazwisko))
	{
		cin.clear();
		cin.sync();
		cout << "Bledne dane!\n";
		cout << "NAZWISKO: ";
	}
	cout << "DATA URODZENIA (DD.MM.RRRR): ";
	while (!(cin >> dataUrodzenia) || (walidujUrodz(dataUrodzenia) == false))
	{
		cin.clear();
		cin.sync();
		cout << "Bledne dane!\n";
		cout << "DATA URODZENIA (DD.MM.RRRR): ";
	}
	cout << "LOGIN: ";
	cin >> login;
	char znakHasla;
	while (1)
	{
		haslo = "";
		haslo1 = "";
		cout << "HASLO: ";
		do
		{
			znakHasla = _getch();
			if (znakHasla != 13 && znakHasla != 8)
			{
				cout << "*";
				haslo += (char)znakHasla;
			}
		} while (znakHasla != 13);
		cout << endl;
		cout << "POWTORZ HASLO: ";
		do
		{
			znakHasla = _getch();
			if (znakHasla != 13 && znakHasla != 8)
			{
				cout << "*";
				haslo1 += (char)znakHasla;
			}
		} while (znakHasla != 13);
		cout << endl;
		if (haslo == haslo1)break;
		cout << "Hasla rozne, sprobuj ponownie" << endl;
	}


	
	_getch();
	string pom;
	fstream plikHasla;
	plikHasla.open("Uzytkownicy.txt", ios::in | ios::out);
	if (plikHasla.good() == true)
	{
		while (!plikHasla.eof())
		{
			getline(plikHasla, odczytNrKarty);
			getline(plikHasla, pom);
			getline(plikHasla, pom);
			getline(plikHasla, pom);
			getline(plikHasla, odczytUser);
			getline(plikHasla, odczytHaslo);
			//cout << deszyfruj(odczytUser, klucz) << endl;
			if (md5(login) == odczytUser)
			{
				plikHasla.close();
				cout << "Login zajety! Wcinsij dowolny klawisz..." << endl;
				_getch();
				system("cls");
				cout << "LOGIN: ";
				cin >> login;
				char znakHasla;
				while (1)
				{
					haslo = "";
					haslo1 = "";
					cout << "HASLO: ";
					do
					{
						znakHasla = _getch();

						if (znakHasla != 13 && znakHasla != 8)
						{
							cout << "*";
							haslo += (char)znakHasla;
						}


					} while (znakHasla != 13);
					cout << endl;
					cout << "POWTORZ HASLO: ";
					do
					{
						znakHasla = _getch();

						if (znakHasla != 13 && znakHasla != 8)
						{
							cout << "*";
							haslo1 += (char)znakHasla;
						}
					} while (znakHasla != 13);
					cout << endl;
					if (haslo == haslo1)break;
					cout << "Hasla rozne, sprobuj ponownie" << endl;
				}


				plikHasla.open("Uzytkownicy.txt", ios::in | ios::out);
			}
		}
		plikHasla.close();





		Uzytkownik nowy(imie, nazwisko, dataUrodzenia, 0, login, haslo);
		int l = odczytNrKarty.length();
		odczytNrKarty = odczytNrKarty.substr(0, l - 1);
		nrKartyMax = atoi(odczytNrKarty.c_str());;
		nrKartyMax = nowy.generujID(1, nrKartyMax);
		nowy.setNrKarty(nrKartyMax);
		ofstream plikHasla("Uzytkownicy.txt", ios::app);
		string pes, nrk, zero = "0";
		nrk = to_string(nrKartyMax);
		plikHasla << endl << nrk << endl;
		plikHasla << imie << endl;
		plikHasla << nazwisko << endl;
		plikHasla << dataUrodzenia << endl;
		plikHasla << md5(login) << endl;
		plikHasla << md5(haslo);
		plikHasla.close();
		cout << "Utworzono konto" << endl;
	}
}































void akcje(double x)
{
	cout << "1 - DODAJ ZAWODNIKA" << endl;
	cout << "2 - EDYTUJ ZAWODNIKA" << endl;
	cout << "3 - USUN ZAWODNIKA" << endl;
	cout << "4 - DODAJ BIEG" << endl;
	cout << "INNY ZNAK - POWROT" << endl;
}

void akcje(int x)
{
	cout << "1 - MOJE ZAWODY" << endl;
	cout << "2 - REKORDY" << endl;
	cout << "3 - SREDNIA ZAWODNIKOW" << endl;
	cout << "INNY ZNAK - POWROT" << endl;
}

int main()
{
	






		Uzytkownik uzytkownik;
		uzytkownik = logowanie();




















		while (1)
		{





			cout << "Nacisnij dowolny klawisz..." << endl;
			_getch();
			system("cls");
			cout << "1 - MOJ PROFIL" << endl;
			cout << "2 - DOPUSZCZALNE AKCJE" << endl;
			cout << "INNY ZNAK - WYLOGOWANIE" << endl;
			char znak;
			znak = _getch();
			system("cls");









			////////////////////////////////////////////////////
			////////////////USER - OPIS PROFILU/////////////////
			////////////////////////////////////////////////////






			if (znak == 49)
			{
				uzytkownik.opisz();
			}





			//////////////////////////////////////////////////////
			///////////////////USER - EDYCJA PROFILU//////////////
			//////////////////////////////////////////////////////









			/*

			else if (znak == 50)
			{
				cout << "1 - IMIE" << endl;
				cout << "2 - NAZWISKO" << endl;
				cout << "3 - DATA URODZENIA" << endl;
				cout << "INNY ZNAK - POWROT" << endl << endl;
				znak = _getch();
				if (znak == 49)
				{
					string imie;
					cout << "IMIE: ";
					while (!(cin >> imie))
					{

						cin.clear();
						cin.sync();
						cout << "Bledne dane!\n";
						cout << "IMIE: ";
					}
					//cout << iterPlik<<endl;
					zamien_wiersz("Uzytkownicy.txt", imie, iterPlik + 1);
					uzytkownik.setImie(imie);
				}
				else if (znak == 50)
				{
					string nazw;
					cout << "NAZWISKO: ";
					while (!(cin >> nazw))
					{

						cin.clear();
						cin.sync();
						cout << "Bledne dane!\n";
						cout << "NAZWISKO: ";
					}
					//cout << iterPlik<<endl;
					zamien_wiersz("Uzytkownicy.txt", nazw, iterPlik + 2);
					uzytkownik.setNazwisko(nazw);
				}
				else if (znak == 51)
				{
					string dataUrodz;
					cout << "DATA URODZENIA: ";
					while (!(cin >> dataUrodz) || (walidujUrodz(dataUrodz) == false))
					{

						cin.clear();
						cin.sync();
						cout << "Bledne dane!\n";
						cout << "PESEL: ";

					}

					zamien_wiersz("Uzytkownicy.txt", dataUrodz, iterPlik + 3);
					uzytkownik.setDataUrodzenia(dataUrodz);
				}
			}





*/










/////////////////////////////////////////////////
/////////PACJENT - USUN KONTO////////////////////
/////////////////////////////////////////////////




/*

else if (znak == 51)
{
	cout << "Czy na pewno chcesz usunac konto? Y/N  ";
	char z;
	cin >> z;
	if (z == 'Y' || z == 'y')
	{
		uzytkownik.~Uzytkownik();
		kasuj_wiersz("Uzytkownicy.txt", iterPlik);
		kasuj_wiersz("Uzytkownicy.txt", iterPlik);
		kasuj_wiersz("Uzytkownicy.txt", iterPlik);
		kasuj_wiersz("Uzytkownicy.txt", iterPlik);
		kasuj_wiersz("Uzytkownicy.txt", iterPlik);
		kasuj_wiersz("Uzytkownicy.txt", iterPlik);
		return 0;
	}

}

*/







////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// DOPUSZCZALNE AKCJE//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////









			else if (znak == 50)
			{



				////////////////////////////////////////////////////////////////////////////////////
				/////////////////////USER - DOPUSZCZALNE AKCJE//////////////////////////////////////
				////////////////////////////////////////////////////////////////////////////////////





				if (uzytkownik.getUprawnienia() == 1)
				{
					system("cls");
					akcje(1);
					char znak1;
					znak1 = _getch();
					system("cls");







					if (znak1 == 49)
					{
						iterPlik = -5;
						string pom;

						string odczytID,odczytDystans,odczytIDB,odczytData,odczytWynik,odczytPozycja;
						int licznik = 0;
						fstream plikHasla;
						plikHasla.open("Biegi.txt", ios::in | ios::out);
						if (plikHasla.good() == true)
						{
							while (!plikHasla.eof())
							{
								iterPlik = iterPlik + 6;
								getline(plikHasla, odczytIDB);
								getline(plikHasla, odczytData);
								getline(plikHasla, odczytDystans);
								getline(plikHasla, odczytID);
								getline(plikHasla, odczytWynik);
								getline(plikHasla, odczytPozycja);
								//cout << odczytLogin << endl;
								if (odczytID == to_string(uzytkownik.getNrKarty()))
								{
									//licznik++;
									cout << "DYSTANS: " << odczytDystans << endl;
									cout << "DATA: " << odczytData << endl;
									cout << "CZAS: " << odczytWynik << endl;
									cout << "POZYCJA: " << odczytPozycja << endl;
									_getch();
									system("cls");
								}
							}
						}
						plikHasla.close();
						//cout << licznik << endl;
					}











					else if (znak1 == 50)
					{
						int dystans;
						cout << "DYSTANS: ";
						while (!(cin >> dystans) || [](int a)
						{
							bool x = true;
							if (a == 100 || a == 200 || a == 500 || a == 1000 || a == 2000 || a == 5000 || a == 10000)x = false;
							return x;
						}(dystans))
						{
							cin.clear();
							cin.sync();
							cout << "Bledne dane!\n";
							cout << "PODAJ POPRAWNY DYSTANS: ";
						}

















						iterPlik = -5;
						string pom;

						string odczytID, odczytDystans, odczytIDB, odczytData, odczytWynik, odczytPozycja;
						int licznik = 0;
						fstream plikHasla;
						string min;
						plikHasla.open("Biegi.txt", ios::in | ios::out);
						if (plikHasla.good() == true)
						{
							while (!plikHasla.eof())
							{
								iterPlik = iterPlik + 6;
								getline(plikHasla, odczytIDB);
								getline(plikHasla, odczytData);
								getline(plikHasla, odczytDystans);
								getline(plikHasla, odczytID);
								getline(plikHasla, odczytWynik);
								getline(plikHasla, odczytPozycja);
								//cout << odczytLogin << endl;
								if (odczytDystans == to_string(dystans))
								{
									if (licznik == 0)
									{
										min = odczytWynik;
									}
									else
									{
										if (min > odczytWynik)min = odczytWynik;
									}
									licznik++;
									
									
								}
							}
						}

						cout << "REKORD NA "<<dystans<<" M: " << min << endl;
						
						_getch();

						plikHasla.close();








					}




					else if (znak1 == 51)
					{
						



						iterPlik = -5;
						string pom;

						string odczytID, odczytDystans, odczytIDB, odczytData, odczytWynik, odczytPozycja;
						double licznik = 0;
						fstream plikHasla;
						string min;
						plikHasla.open("Biegi.txt", ios::in | ios::out);
						if (plikHasla.good() == true)
						{
							while (!plikHasla.eof())
							{
								iterPlik = iterPlik + 6;
								getline(plikHasla, odczytIDB);
								getline(plikHasla, odczytData);
								getline(plikHasla, odczytDystans);
								getline(plikHasla, odczytID);
								getline(plikHasla, odczytWynik);
								getline(plikHasla, odczytPozycja);
								//cout << odczytLogin << endl;
								licznik++;
							}
						}

						if(licznik>0)cout << "SREDNIA ZAWODNIKOW: " << double(licznik/atoi(odczytIDB.c_str())) << endl;
						else cout << "SREDNIA ZAWODNIKOW: BRAK ZAWODOW"<< endl;
						_getch();

						plikHasla.close();















					}

				}



				/////////////////////////////////////////////////////////////////////////////
				////////////////// USER - DOPUSZCZALNE AKCJE (KONIEC) ///////////////////////
				/////////////////////////////////////////////////////////////////////////////
































				////////////////////////////////////////////////////////////////////////////////////
				/////////////////// ADMIN - DOPUSZCZALNE AKCJE /////////////////////////////////////
				////////////////////////////////////////////////////////////////////////////////////





				else if (uzytkownik.getUprawnienia() == 2)
				{
					
					system("cls");
					akcje(0.5);
					char znak1;
					znak1 = _getch();
					system("cls");

					if (znak1 == 49)
					{
						rejestracja();
					}





					else if (znak1 == 50)
					{
						system("cls");
						string login;
						cout << "LOGIN: ";
						while (!(cin >> login))
						{

							cin.clear();
							cin.sync();
							cout << "Bledne dane!\n";
							cout << "LOGIN: ";
						}
						cout << md5(login)<<endl;
						iterPlik = -5;
						string pom;

						string odczytLogin;
						int licznik = 0;
						fstream plikHasla;
						plikHasla.open("Uzytkownicy.txt", ios::in | ios::out);
						if (plikHasla.good() == true)
						{
							while (!plikHasla.eof())
							{
								iterPlik = iterPlik + 6;
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, odczytLogin);
								getline(plikHasla, pom);
								//cout << odczytLogin << endl;
								if (odczytLogin == md5(login))
								{
									licznik++;
									break;
								}
							}
						}
						if (licznik == 0)cout << "BRAK DANYCH O TAKIM ZAWODNIKU" << endl;
						else
						{
							system("cls");
							char znak2;
							cout << "1 - IMIE" << endl;
							cout << "2 - NAZWISKO" << endl;
							cout << "3 - DATA URODZENIA" << endl;
							cout << "INNY ZNAK - POWROT" << endl << endl;
							znak2 = _getch();
							if (znak2 == 49)
							{
								string imie;
								cout << "IMIE: ";
								while (!(cin >> imie))
								{

									cin.clear();
									cin.sync();
									cout << "Bledne dane!\n";
									cout << "IMIE: ";
								}
								//cout << iterPlik<<endl;
								zamien_wiersz("Uzytkownicy.txt", imie, iterPlik + 1);
							}
							else if (znak2 == 50)
							{
								string nazw;
								cout << "NAZWISKO: ";
								while (!(cin >> nazw))
								{

									cin.clear();
									cin.sync();
									cout << "Bledne dane!\n";
									cout << "NAZWISKO: ";
								}
								//cout << iterPlik<<endl;
								zamien_wiersz("Uzytkownicy.txt", nazw, iterPlik + 2);
							}
							else if (znak2 == 51)
							{
								string dataUrodz;
								cout << "DATA URODZENIA: ";
								while (!(cin >> dataUrodz) || (walidujUrodz(dataUrodz) == false))
								{

									cin.clear();
									cin.sync();
									cout << "Bledne dane!\n";
									cout << "DATA URODZENIA: ";

								}

								zamien_wiersz("Uzytkownicy.txt", dataUrodz, iterPlik + 3);
							}
						}
						plikHasla.close();
					}










					else if (znak1 == 51)
					{
						system("cls");
						string login;
						cout << "LOGIN: ";
						while (!(cin >> login))
						{

							cin.clear();
							cin.sync();
							cout << "Bledne dane!\n";
							cout << "LOGIN: ";
						}
						iterPlik = -5;
						string pom;

						string odczytLogin;
						int licznik = 0;
						fstream plikHasla;
						plikHasla.open("Uzytkownicy.txt", ios::in | ios::out);
						if (plikHasla.good() == true)
						{
							while (!plikHasla.eof())
							{
								iterPlik = iterPlik + 6;
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, odczytLogin);
								getline(plikHasla, pom);
								if (odczytLogin == md5(login))
								{
									licznik++;
									break;
								}
							}
						}
						if (licznik == 0)cout << "BRAK DANYCH O TAKIM ZAWODNIKU" << endl;
						else
						{
							cout << "Czy na pewno chcesz usunac konto? Y/N  ";
							char z;
							cin >> z;
							if (z == 'Y' || z == 'y')
							{
								kasuj_wiersz("Uzytkownicy.txt", iterPlik);
								kasuj_wiersz("Uzytkownicy.txt", iterPlik);
								kasuj_wiersz("Uzytkownicy.txt", iterPlik);
								kasuj_wiersz("Uzytkownicy.txt", iterPlik);
								kasuj_wiersz("Uzytkownicy.txt", iterPlik);
								kasuj_wiersz("Uzytkownicy.txt", iterPlik);
								return 0;
							}

						}
					}



					else if (znak1 == 52)
					{




						iterPlik = -5;
						string pom;

						string idBiegu;
						string odczytIdBiegu;
						int licznik = 0;
						fstream plikHasla;
						plikHasla.open("Biegi.txt", ios::in | ios::out);
						if (plikHasla.good() == true)
						{
							while (!plikHasla.eof())
							{
								iterPlik = iterPlik + 6;
								getline(plikHasla, odczytIdBiegu);
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								getline(plikHasla, pom);
								licznik=1;								
							}
						if (licznik == 0)idBiegu = 1;
						else
						{
							ulong maxID;
							maxID = atoi(odczytIdBiegu.c_str());
							maxID++;
							idBiegu = to_string(maxID);
						}
						}
						plikHasla.close();
						int dystans;
						cout << "DYSTANS: ";
						while (!(cin >> dystans) || [](int a)
						{
							bool x = true;
							if (a == 100 || a == 200 || a == 500 || a == 1000 || a == 2000 || a == 5000 || a == 10000)x = false ;
							return x;
						}(dystans))
						{
							cin.clear();
							cin.sync();
							cout << "Bledne dane!\n";
							cout << "PODAJ POPRAWNY DYSTANS: ";
						}
						
						string data;
						cout << "DATA: ";
						while (!(cin >> data) || (walidujUrodz(data) == false))
						{

							cin.clear();
							cin.sync();
							cout << "Bledne dane!\n";
							cout << "DATA: ";

						}
						vector<Bieg>rezultaty;
						cout << "LICZBA ZAWODNIKOW: ";
						int l;
						string idBiegacza, wynik;
						cin >> l;
						for(int i=1;i<=l;i++)
						{
							system("cls");
							cout << "ID ZAWODNIKA: ";
							cin >> idBiegacza;







							iterPlik = -5;
							string pom;

							string odczytID;
							int licznik = 0;
							fstream plikHasla;
							plikHasla.open("Uzytkownicy.txt", ios::in | ios::out);
							if (plikHasla.good() == true)
							{
								while (!plikHasla.eof())
								{
									iterPlik = iterPlik + 6;
									getline(plikHasla, odczytID);
									getline(plikHasla, pom);
									getline(plikHasla, pom);
									getline(plikHasla, pom);
									getline(plikHasla, pom);
									getline(plikHasla, pom);
									//cout << odczytLogin << endl;
									if (odczytID == idBiegacza)
									{
										licznik++;
										break;
									}
								}
							}
							if (licznik == 0)
							{
								cout << "BRAK DANYCH O TAKIM ZAWODNIKU" << endl;
								i--;
								_getch();
							}
							else
							{



								if (dystans >= 1000)
								{
									cout << "WYNIK(MM:SS,TT): ";
									cin >> wynik;
								}
								else
								{
									cout << "WYNIK(SS,TT): ";
									cin >> wynik;
								}

								Bieg nowy(idBiegu,data,dystans,idBiegacza,wynik,0);
								rezultaty.push_back(nowy);
								nowy.~Bieg();

							}
							
							
						}




						sort(rezultaty.begin(),rezultaty.end(),
							[](const Bieg & a, const Bieg & b) -> bool
						{
							return a.wynik < b.wynik;
						});





















					

						





						
							ofstream plik("Biegi.txt", ios::app);




							
							
							
						




















						for (int i = 0;i < rezultaty.size();i++)
						{
							rezultaty[i].setPozycja(i + 1);

							


							plik << endl << rezultaty[i].idBiegu << endl;
							plik << rezultaty[i].data << endl;
							plik << to_string(rezultaty[i].dystans) << endl;
							plik << rezultaty[i].idBiegacza << endl;
							plik << rezultaty[i].wynik << endl;
							plik << to_string(rezultaty[i].pozycja);


						}

						plik.close();


						
						
					}









				}



				/////////////////////////////////////////////////////////////////////////////
				////////////////// ADMIN - DOPUSZCZALNE AKCJE (KONIEC) //////////////////////
				/////////////////////////////////////////////////////////////////////////////




				/////////////////////////////////////////////////////
				///////////////// USER - WYLOGOWANIE ////////////////
				/////////////////////////////////////////////////////

				else continue;



			}















			////////////////////////////////////////////////////////////
			////////////PACJENT - LOGOWANIE (KONIEC)////////////////////
			////////////////////////////////////////////////////////////


























			////////////////////////////////////////////////////////////
			///////////////////PACJENT - REJESTRACJA////////////////////
			////////////////////////////////////////////////////////////










			//////////////////////////////////////////////////////////////////
			/////////////////PACJENT - WYJSCIE////////////////////////////////
			//////////////////////////////////////////////////////////////////

			else return 0;

		}

    return 0;
}

	