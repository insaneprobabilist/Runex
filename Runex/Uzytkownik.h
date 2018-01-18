#pragma once
#include <iostream>
#include <string>
#include <conio.h>

typedef unsigned long long ulong;

using namespace std;

class Uzytkownik
{
public:
	string login;
	string haslo;
	string imie;
	string nazwisko;
	string dataUrodzenia;
	ulong nrKarty;
	int uprawnienia;
	Uzytkownik();
	~Uzytkownik();
	Uzytkownik(string imie, string nazwisko, string dataUrodzenia, ulong nrKarty, string login, string haslo);
	//Zamowienie zamowienie;
	ulong generujID(int uprawnienia, ulong max);

	void opisz();


	//gettery i settery
	string getLogin() { return login; };

	void setLogin(string s) { login = s; };

	void setHaslo(string s) { haslo = s; };

	void setNazwisko(string s) { nazwisko = s; };

	void setImie(string s) { imie = s; };

	void setDataUrodzenia(string s) { dataUrodzenia = s; };

	void setNrKarty(ulong s) { nrKarty = s; };
	ulong getNrKarty() { return nrKarty; };



	int getUprawnienia() { return uprawnienia; };
};

