#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Oferta {
	std::string denumire;
	std::string destinatie;
	std::string tip;
	float pret=-1;

public:
	Oferta(const string denumire, const string destinatie, const string tip, const float pret) :
		denumire{ denumire }, destinatie{ destinatie }, tip{ tip }, pret{ pret }{};
	Oferta() = default;
	string obtine_denumire() const {
		return denumire;
	}
	string obtine_destinatie() const {
		return destinatie;
	}
	
	string obtine_tip() const {
		return tip;
	}
	
	float obtine_pret() const noexcept{
		return pret;
	}

	void modifica_destinatie(string destinatie_noua)
	{
		Oferta::destinatie = destinatie_noua;
	}
	void modifica_tip(string tip_nou)
	{
		Oferta::tip = tip_nou;
	}
	void modifica_pret(float pret_nou) noexcept
	{
		Oferta::pret = pret_nou;
	}
};

void test_oferta();