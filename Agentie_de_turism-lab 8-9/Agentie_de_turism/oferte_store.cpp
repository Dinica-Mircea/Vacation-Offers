#include "oferte_store.h"
#include <assert.h>
using std::copy_if;
//using std::vector;
//void Oferte_store::sterge_oferta(const string denumire) {
//	for (int i = 0; i < oferte_repo.obtine_toate_ofertele().size(); i++)
//	{
//		try {
//			Oferta oferta_de_sters = oferte_repo.gaseste_oferta(denumire);
//
//		}
//		catch (Oferte_repo_exceptii&)
//		{
//			throw Oferte_repo_exceptii()
//		}
//	}
//}

vector<Oferta> Oferte_store::sortare_generala(bool(*functie_de_comparare)(const Oferta&, const Oferta&))
{
	vector<Oferta> copie_oferte = obtine_toate_ofertele();
	for (int i = 0; i < copie_oferte.size() - 1; i++)
	{
		for (int j = i + 1; j < copie_oferte.size(); j++)
		{
			if(functie_de_comparare!=nullptr)
			if (functie_de_comparare(copie_oferte.at(i), copie_oferte.at(j))) {
				Oferta auxiliar = copie_oferte.at(i);
				copie_oferte.at(i) = copie_oferte.at(j);
				copie_oferte.at(j) = auxiliar;
			}
		}
	}
	return copie_oferte;
}

vector<Oferta> Oferte_store::sortare_dupa_denumire()
{
	return sortare_generala([](const Oferta& oferta1, const Oferta& oferta2) {
		return oferta1.obtine_denumire() >= oferta2.obtine_denumire();
		});
}

vector<Oferta> Oferte_store::sortare_dupa_destinatie()
{
	return sortare_generala([](const Oferta& oferta1, const Oferta& oferta2) {
		return oferta1.obtine_destinatie() >= oferta2.obtine_destinatie();
		});
}

vector<Oferta> Oferte_store::sortare_dupa_tip_si_pret()
{
	return sortare_generala([](const Oferta& oferta1, const Oferta& oferta2) {
		if (oferta1.obtine_tip() == oferta2.obtine_tip())
			return oferta1.obtine_pret() >= oferta2.obtine_pret();
		else return oferta1.obtine_tip() >= oferta2.obtine_tip();
		});

}

vector<Oferta> Oferte_store::filtreaza(function<bool(const Oferta&)> functie_de_comnparare)
{
	vector<Oferta> ofertele_filtrate;
	auto repo = obtine_toate_ofertele();
	//for (const auto& oferta : Oferte_store::obtine_toate_ofertele()) {
	copy_if(repo.begin(), repo.end(), std::back_inserter(ofertele_filtrate), functie_de_comnparare);
	/*for(auto oferta:obtine_toate_ofertele()) {
		if (functie_de_comnparare(oferta))
		{
			ofertele_filtrate.push_back(oferta);
		}
	}*/
	return ofertele_filtrate;
}
vector<Oferta> Oferte_store::filtreaza_dupa_pret_mai_mic(float pret)
{
	return filtreaza([pret](const Oferta& oferta) {
		return oferta.obtine_pret() <= pret;
		});
}

void test_oferte_store()
{
	Oferte_repo repo;
	//Repo_probabilitate_random repo;
	Oferte_store store(repo);
	Oferta Oferta1{ "vac1","dest1","tip2",1 };
	Oferta Oferta2{ "vac2","dest2","tip2",2 };
	Oferta Oferta3{ "vac3","dest3","tip3",3};
	store.adauga_oferta(Oferta1);
	store.adauga_oferta(Oferta2);
	store.adauga_oferta(Oferta3);
	store.sterge_oferta(Oferta1.obtine_denumire());
	assert(store.obtine_toate_ofertele().size() == 2);
	assert(store.gaseste_oferta("vac2").obtine_denumire() == Oferta2.obtine_denumire());
	store.modifica_destinatie_oferta("vac2", "bali");
	store.modifica_pret_oferta("vac2", 10.1f);
	store.modifica_tip_oferta("vac2", "cu bizu");
	assert(store.gaseste_oferta("vac2").obtine_destinatie() == "bali");
	assert(store.gaseste_oferta("vac2").obtine_pret() == 10.1f);
	assert(store.gaseste_oferta("vac2").obtine_tip() == "cu bizu");
	repo.distruge_toate_ofertele();
}

void test_filtrare_store()
{
	Oferte_repo repo;
	//Repo_probabilitate_random repo;
	Oferte_store store(repo);
	Oferta Oferta1{ "vac1","dest1","tip1",1 };
	Oferta Oferta2{ "vac2","dest2","tip2",2 };
	Oferta Oferta3{ "vac3","dest3","tip3",3 };
	store.adauga_oferta(Oferta1);
	store.adauga_oferta(Oferta2);
	store.adauga_oferta(Oferta3);
	vector<Oferta> oferte_filtrare_pret;
	oferte_filtrare_pret = store.filtreaza_dupa_pret_mai_mic(2);
	assert(oferte_filtrare_pret.size() == 2);
	Oferta Oferta4{ "vac4","dest2","tip4",4 };
	store.adauga_oferta(Oferta4);
	vector<Oferta> oferte_filtrare_destinatie=store.filtreaza_dupa_destinatie("dest2");
	assert(oferte_filtrare_destinatie.size() == 2);


}

void test_sortare_store()
{
	Oferte_repo repo;
	//Repo_probabilitate_random repo;
	Oferte_store store(repo);
	Oferta Oferta1{ "vac3","dest3","tip2",2 };
	Oferta Oferta2{ "vac2","dest2","tip2",1 };
	Oferta Oferta3{ "vac1","dest1","tip3",3 };
	store.adauga_oferta(Oferta1);
	store.adauga_oferta(Oferta2);
	store.adauga_oferta(Oferta3);
	vector<Oferta> oferte_sortate_dupa_denumire = store.sortare_dupa_denumire();
	assert(oferte_sortate_dupa_denumire.at(0).obtine_denumire() == "vac1");
	assert(oferte_sortate_dupa_denumire.at(1).obtine_denumire() == "vac2");
	assert(oferte_sortate_dupa_denumire.at(2).obtine_denumire() == "vac3");
	vector<Oferta> oferte_sortate_dupa_destinatie = store.sortare_dupa_destinatie();
	assert(oferte_sortate_dupa_denumire.at(0).obtine_destinatie() == "dest1");
	assert(oferte_sortate_dupa_denumire.at(1).obtine_destinatie() == "dest2");
	assert(oferte_sortate_dupa_denumire.at(2).obtine_destinatie() == "dest3");
	vector<Oferta> oferte_sortate_dupa_tip_si_pret = store.sortare_dupa_tip_si_pret();
	assert(oferte_sortate_dupa_tip_si_pret.at(0).obtine_denumire() == "vac2");
	assert(oferte_sortate_dupa_tip_si_pret.at(1).obtine_denumire() == "vac3");
	assert(oferte_sortate_dupa_tip_si_pret.at(2).obtine_denumire() == "vac1");
	store.undo();
	assert(store.obtine_toate_ofertele().size() == 2);
}

vector<Oferta> Oferte_store::filtreaza_dupa_destinatie(string destinatie) {
	vector<Oferta> ofertele_filtrare_dupa_destinatie;
	//for (auto i : oferte_repo.obtine_toate_ofertele())
	for(auto oferta:obtine_toate_ofertele())
	{
		if (oferta.obtine_destinatie() == destinatie)
			ofertele_filtrare_dupa_destinatie.push_back(oferta);
	}
	return ofertele_filtrare_dupa_destinatie;
}

void Oferte_store::salveaza_wishlist_in_fisier(const string& nume_fisier, vector<Oferta> oferte) {
	std::ofstream afisare(nume_fisier, std::ios::trunc);
	if (!afisare.is_open()) {
		throw Oferte_repo_exceptii("Fisierul nu a putut fi creat!");
	}
	for (auto oferta : oferte)
	{
		afisare << oferta.obtine_denumire() << ";";
		afisare << oferta.obtine_destinatie() << ";";
		afisare << oferta.obtine_tip() << ";";
		afisare << oferta.obtine_pret() << "\n";
	}
	afisare.close();
}

void test_salvare_in_fisier() {
	Oferte_repo Oferte_repo_test;
	//Repo_probabilitate_random Oferte_repo_test;
	Oferta Oferta1{ "vac1","dest1","tip1",1 };
	Oferta Oferta2{ "vac2","dest2","tip2",2 };
	Oferta Oferta3{ "vac3","dest3","tip3",3 };
	Oferte_store Oferte_store_test(Oferte_repo_test);
	
	Oferte_repo_test.adauga_oferta(Oferta1);
	Oferte_repo_test.adauga_oferta(Oferta2);
	Oferte_repo_test.adauga_oferta(Oferta3);
	/*wishlist_oferte wishlist(Oferte_repo_test);
	wishlist.adauga_Oferta(Oferta1.obtine_denumire());
	wishlist.adauga_Oferta(Oferta2.obtine_denumire());
	wishlist.adauga_Oferta(Oferta3.obtine_denumire());*/
	Oferte_store_test.salveaza_wishlist_in_fisier("test_salvare.cvs",Oferte_repo_test.obtine_toate_ofertele());
	std::ifstream in("test_salvare.cvs");
	assert(in.is_open());
	int numar_de_linii = 0;
	while (!in.eof())
	{
		string line;
		in >> line;
		numar_de_linii++;
	}
	//cout << numar_de_linii;
	assert(numar_de_linii == 4);
	in.close();
}