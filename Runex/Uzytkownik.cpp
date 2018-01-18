#include "stdafx.h"
#include "Uzytkownik.h"

Uzytkownik::Uzytkownik()
{
}


Uzytkownik::~Uzytkownik()
{
}

Uzytkownik::Uzytkownik(string imie, string nazwisko, string dataUrodzenia, ulong nrKarty, string mail, string haslo)
{
	this->imie = imie;
	this->nazwisko = nazwisko;
	this->dataUrodzenia = dataUrodzenia;
	this->nrKarty = nrKarty;
	this->login = login;
	this->haslo = haslo;
	//licznikKsiazek=0;
	uprawnienia = nrKarty % 10;
}



ulong Uzytkownik::generujID(int upraw, ulong max)
{
	return (max + 1) * 10 + upraw;
}


void Uzytkownik::opisz()
{
	cout << "PROFIL" << endl << endl;
	cout << "NR KARTY: " << nrKarty << endl;
	cout << "IMIE: " << imie << endl;
	cout << "NAZWISKO: " << nazwisko << endl;
	cout << "DATA URODZENIA: " << dataUrodzenia << endl;
	cout << "TRYB: ";
	if (uprawnienia == 1)cout << "uzytkownik" << endl;
	else cout << "admin" << endl;
}

