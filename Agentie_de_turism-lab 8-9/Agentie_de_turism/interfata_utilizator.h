#pragma once
//#include "oferta.h"
#include "oferte_store.h"
#include "wishlist.h"
class consola_UI {
	Oferte_store& oferte_store;
	wishlist_oferte wishlist;

public:
	consola_UI(Oferte_store& oferte_store, wishlist_oferte wishlist) noexcept :oferte_store{ oferte_store }, wishlist{ wishlist }{}

	void adauga_oferta_UI();

	void meniu_principal();

	void sterge_oferta_UI();

	void afiseaza_toate_ofertele_UI();

	void gaseste_oferta_UI();
	
	void incepe_UI();

	void filtrare_pret_mai_mic();

	void filtrare_destinatie();

	void modifica_destinatie_UI();

	void sortare_oferte_UI();

	void adauga_in_wishlist();

	void goleste_wishlist();

	void genereaza_wishlist();

	void undo();

	void salveaza_in_fisier_wishlist_ul();
};