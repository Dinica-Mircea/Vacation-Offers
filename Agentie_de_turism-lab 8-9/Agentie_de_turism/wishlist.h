#include <iostream>
#include <vector>
//#include "oferta.h"
#include "oferte_repo.h"
#include <string>
using std::vector;
class wishlist_oferte {
	vector<Oferta> toate_ofertele;
	Oferte_repo& repo;
public:
	wishlist_oferte(Oferte_repo& repo)noexcept : repo{repo} {}
	wishlist_oferte() = default;
	void adauga_Oferta(string denumire);
	void goleste() noexcept;
	void genereaza_cos(int numar_de_oferte);
	vector<Oferta> obtine_tot_wishlist_ul();
};

void test_wishlist();