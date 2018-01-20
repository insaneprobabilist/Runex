#pragma once

#include <iostream>
#include <string>

using namespace std;

class Bieg
{


public:
	string idBiegu;
	string idBiegacza;
	string data;
	int dystans;
	string wynik;
	int pozycja;
	Bieg();
	~Bieg();
	Bieg(string idBiegu, string data, int dystans, string idBiegacza, string wynik, int pozycja);

	void opisz();
};
