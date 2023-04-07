#pragma once
#include "oferta.h"
#include "oferte_repo.h"
#include <functional>
#include <algorithm>
//#include "undo.h"
#include <fstream>
//#include "wishlist.h"
//using std::vector;
using std::function;
//class wishlist_oferte;
class Oferte_store {
	//Repo_probabilitate_random& oferte_repo;

	Repo& oferte_repo;

	vector<Oferta> filtreaza(function<bool(const Oferta&)> functie_de_comnparare);

	vector<Oferta> sortare_generala(bool(*functie_de_comparare)(const Oferta&, const Oferta&));

	

public:
	Oferte_store(Repo& oferte_repo) noexcept :oferte_repo{ oferte_repo }{}

	//Oferte_store(Repo_probabilitate_random& repo_random) : oferte_repo{repo_random} {}

	const vector<Oferta>& obtine_toate_ofertele() noexcept {
		return oferte_repo.obtine_toate_ofertele();
	}

	void adauga_oferta(const Oferta& oferta_de_adaugat) {
		oferte_repo.adauga_oferta(oferta_de_adaugat);
	}

	void sterge_oferta(string denumire) {
		oferte_repo.sterge_oferta(denumire);
	}

	const Oferta& gaseste_oferta(string denumire)
	{
		return oferte_repo.gaseste_oferta(denumire);
		/*if (oferte_repo.gaseste_oferta(denumire) != nullptr)
			return oferte_repo.gaseste_oferta(denumire);
		else throw std::exception();*/
	}
	void modifica_destinatie_oferta(string denumire, string destinatie_noua)
	{
		oferte_repo.modifica_destinatie_oferta(denumire, destinatie_noua);
	}
	void modifica_tip_oferta(string denumire, string tip_nou)
	{
		oferte_repo.modifica_tip_oferta(denumire, tip_nou);
	}
	void modifica_pret_oferta(string denumire, float pret_nou)
	{
		oferte_repo.modifica_pret_oferta(denumire, pret_nou);
	}
	vector<Oferta> filtreaza_dupa_pret_mai_mic(float pret) ;

	vector<Oferta> filtreaza_dupa_destinatie(string destinatie);
	
	vector<Oferta> sortare_dupa_denumire();

	vector<Oferta> sortare_dupa_destinatie();

	vector<Oferta> sortare_dupa_tip_si_pret();

	void undo() {
		oferte_repo.undo();
	}

	void salveaza_wishlist_in_fisier(const string& nume_fisier, vector<Oferta> oferte);
	
};
void test_sortare_store();
void test_oferte_store();
void test_filtrare_store();
void test_salvare_in_fisier();