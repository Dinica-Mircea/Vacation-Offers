#include "wishlist.h"
#include <assert.h>
#include <random>
#include <chrono>
#include <algorithm>
void wishlist_oferte::adauga_Oferta(string denumire) {
	Oferta oferta_de_adaugat_in_wishlist = repo.gaseste_oferta(denumire);
	toate_ofertele.push_back(oferta_de_adaugat_in_wishlist);
}

void wishlist_oferte::goleste() noexcept {
	toate_ofertele.clear();
}

vector<Oferta> wishlist_oferte::obtine_tot_wishlist_ul() {
	return toate_ofertele;
}

void wishlist_oferte::genereaza_cos(int numar_de_oferte) {
	if (numar_de_oferte > repo.obtine_toate_ofertele().size())
		numar_de_oferte = int(repo.obtine_toate_ofertele().size());
	vector<Oferta> repo_amestecat;
	for (auto oferta : repo.obtine_toate_ofertele())
	{
		repo_amestecat.push_back(oferta);
	}
	//auto seed = std::chrono::system_clock::now().time_since_epoch().count();

	//std::shuffle(repo_amestecat.begin(), repo_amestecat.end(), std::default_random_engine(seed));
	std::random_shuffle(repo_amestecat.begin(), repo_amestecat.end());
	int numar_de_oferte_adaugate = 0;
	for (auto oferta : repo.obtine_toate_ofertele())
	{
		if (numar_de_oferte_adaugate <= numar_de_oferte)
		{
			numar_de_oferte_adaugate++;
			toate_ofertele.push_back(oferta);
		}
	}

}
void test_wishlist() {
	Oferte_repo Oferte_repo_test;
	Oferta Oferta1{ "vac1","dest1","tip1",1 };
	Oferta Oferta2{ "vac2","dest2","tip2",2 };
	Oferta Oferta3{ "vac3","dest3","tip3",3 };
	Oferte_repo_test.adauga_oferta(Oferta1);
	Oferte_repo_test.adauga_oferta(Oferta2);
	Oferte_repo_test.adauga_oferta(Oferta3);
	wishlist_oferte wishlist(Oferte_repo_test);
	wishlist.adauga_Oferta("vac1");
	assert(wishlist.obtine_tot_wishlist_ul().size() == 1);
	wishlist.goleste();
	assert(wishlist.obtine_tot_wishlist_ul().size() == 0);
	wishlist.genereaza_cos(4);
	assert(wishlist.obtine_tot_wishlist_ul().size() == 3);
}