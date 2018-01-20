#include "stdafx.h"
#include "Bieg.h"


Bieg::Bieg()
{
}


Bieg::~Bieg()
{
}

Bieg::Bieg(string idBiegu, string data, int dystans, string idBiegacza, string wynik, int pozycja)
{
	this->idBiegu = idBiegu;
	this->dystans = dystans;
	this->data = data;
	this->idBiegacza = idBiegacza;
	this->wynik = wynik;
	this->pozycja = pozycja;
}

void Bieg::opisz()
{
	cout << "DYSTANS: " << dystans << endl;
	cout << "DATA: " << data << endl;
	cout << "CZAS: " << wynik << endl;
	cout << "POZYCJA: " << pozycja << endl;
}