#include "interfata_utilizator.h"

//#include "oferta.h"
#include <iostream>
#include <string>
#include "validator.h"
using std::cout;
using std::cin;

void consola_UI::adauga_oferta_UI()
{
	string denumire, destinatie, tip;
	float pret;
	cout << "\nIntroduceti denumire: ";
	cin >> denumire;
	cout << "\nIntroduceti destinatie: ";
	cin >> destinatie;
	cout << "\nIntroduceti tip: ";
	cin >> tip;
	cout << "\nIntroduceti pret: ";
	cin >> pret;
	Oferta oferta_de_adaugat(denumire, destinatie, tip, pret);
	consola_UI::oferte_store.adauga_oferta(oferta_de_adaugat);
	consola_UI::afiseaza_toate_ofertele_UI();
}

void consola_UI::meniu_principal()
{
	cout << "Meniu:\n";
	cout << "1-adauga oferta\n";
	cout << "2-sterge oferta\n";
	cout << "3-afiseaza toate ofertele\n";
	cout << "4-cautare oferta\n";
	cout << "5-filtrare pret mai mic\n";
	cout << "6-filtrare dupa destinatie\n";
	cout << "7-modifica oferta\n";
	cout << "8-sortare oferte\n";
	cout << "9-adauga in wishlist\n";
	cout << "10-goleste wishlits\n";
	cout << "11-genereaza aleeator wishlist\n";
	cout << "12-undo\n";
	cout << "13-salvare in fisier CVS\n";
	cout << "99-oprire\n";
}

void consola_UI::sortare_oferte_UI() {
	cout << "1->denumire 2->destinatie 3->tip+pret\n";
	cout << "Introduceti cifra corespunzatoare campului dupa care doriti sa sortati: ";
	string camp_de_sortat;
	bool afisare_oferte_sortate = true;
	cin >> camp_de_sortat;
	vector<Oferta> oferte_sortate;
	if (camp_de_sortat == "1")
		oferte_sortate = consola_UI::oferte_store.sortare_dupa_denumire();
	else if (camp_de_sortat == "2")
		oferte_sortate = oferte_store.sortare_dupa_destinatie();
	else if (camp_de_sortat == "3")
		oferte_sortate = oferte_store.sortare_dupa_tip_si_pret();
	else {
		cout << "Nu ati introdus o cifra buna!\n"; afisare_oferte_sortate = false;
	}
	if (afisare_oferte_sortate == true)
	{
		cout << "Acestea sunt ofertele sortate: \n";
		for (auto i : oferte_sortate)
		{
			cout << i.obtine_denumire() << " " << i.obtine_destinatie() << " " << i.obtine_tip() << " " << i.obtine_pret() << '\n';
		}
	}
}

void consola_UI::sterge_oferta_UI()
{
	string denumirea_ofertei_de_sters;
	cout << "Introduceti denumirea ofertei de sters: ";
	cin >> denumirea_ofertei_de_sters;
	oferte_store.sterge_oferta(denumirea_ofertei_de_sters);
	consola_UI::afiseaza_toate_ofertele_UI();
}

void consola_UI::afiseaza_toate_ofertele_UI()
{
	if (oferte_store.obtine_toate_ofertele().size() == 0)
		cout << "Nu exista nici o oferta momentan!\n";
	else {
		cout << "Acestea sunt toate ofertele:\n";
		vector<Oferta> toate_ofertele = oferte_store.obtine_toate_ofertele();
		for (auto iterator : toate_ofertele)
		{
			cout << iterator.obtine_denumire() << " " << iterator.obtine_destinatie() << " " << iterator.obtine_tip() << " " << iterator.obtine_pret() << '\n';
		}
	}
}

void consola_UI::modifica_destinatie_UI()
{
	cout << "Introduceti denumirea ofertei de modificat:\n";
	string denumire;
	cin >> denumire;
	cout << "d->destinatie t->tip p->pret\n";
	cout << "Introduceti litera corespunzatoare campului pe care doriti sa il schimbati: ";
	string camp_de_schimbat;
	cin >> camp_de_schimbat;
	if (camp_de_schimbat == "d")
	{
		cout << "\nIntroduceti noua destinatie: ";
		string destinatie_noua;
		cin >> destinatie_noua;
		oferte_store.modifica_destinatie_oferta(denumire, destinatie_noua);
		afiseaza_toate_ofertele_UI();
	}
	else if (camp_de_schimbat == "t")
	{
		cout << "\nIntroduceti noul tip: ";
		string tip_nou;
		cin >> tip_nou;
		oferte_store.modifica_tip_oferta(denumire, tip_nou);
		afiseaza_toate_ofertele_UI();
	}
	else if (camp_de_schimbat == "p")
	{
		cout << "\nIntroduceti noul pret: ";
		float pret_nou;
		cin >> pret_nou;
		oferte_store.modifica_pret_oferta(denumire, pret_nou);
		afiseaza_toate_ofertele_UI();
	}
	else cout << "comanda gresita!\n";
}

void consola_UI::adauga_in_wishlist() {
	string denumirea_ofertei_de_adaugat;
	cout << "Introduceti denumirea ofertei de adaugat: ";
	cin >> denumirea_ofertei_de_adaugat;
	wishlist.adauga_Oferta(denumirea_ofertei_de_adaugat);
	for (auto i : wishlist.obtine_tot_wishlist_ul())
	{
		cout << i.obtine_denumire() << " " << i.obtine_destinatie() << " " << i.obtine_tip() << " " << i.obtine_pret() << '\n';
	}
}

void consola_UI::goleste_wishlist() {
	wishlist.goleste();
	cout << "Wishlist-ul a fost golit!\n";
}

void consola_UI::genereaza_wishlist() {
	cout << "Introduceti numarul de oferte pe care vreti sa il aiba wishlist-ul: ";
	int numar_de_oferte;
	cin >> numar_de_oferte;
	if (numar_de_oferte <= 0)
		cout << "Numarul de oferte trebuie sa fie mai mare ca 0!\n";
	else {
		wishlist.genereaza_cos(numar_de_oferte);
		for (auto i : wishlist.obtine_tot_wishlist_ul())
		{
			cout << i.obtine_denumire() << " " << i.obtine_destinatie() << " " << i.obtine_tip() << " " << i.obtine_pret() << '\n';
		}
	}
}

void consola_UI::incepe_UI()
{
	while (true)
	{
		consola_UI::meniu_principal();
		string comanda;
		cin >> comanda;
		try {
			if (comanda == "1")
				consola_UI::adauga_oferta_UI();
			else if (comanda == "2")
				consola_UI::sterge_oferta_UI();
			else if (comanda == "3")
				consola_UI::afiseaza_toate_ofertele_UI();
			else if (comanda == "4")
				consola_UI::gaseste_oferta_UI();
			else if (comanda == "5")
				consola_UI::filtrare_pret_mai_mic();
			else if (comanda == "6")
				consola_UI::filtrare_destinatie();
			else if (comanda == "7")
				consola_UI::modifica_destinatie_UI();
			else if (comanda == "8")
				consola_UI::sortare_oferte_UI();
			else if (comanda == "9")
				consola_UI::adauga_in_wishlist();
			else if (comanda == "10")
				consola_UI::goleste_wishlist();
			else if (comanda == "11")
				consola_UI::genereaza_wishlist();
			else if (comanda == "12")
				consola_UI::undo();
			else if (comanda == "13")
				consola_UI::salveaza_in_fisier_wishlist_ul();
			else if (comanda == "99")
				break;
			else cout << "comanda gresita\n";
		}
		catch (const Oferte_repo_exceptii& eroare)
		{
			cout << eroare;
		}
		catch (const validator_oferta_exceptii& eroare)
		{
			cout << eroare<<"\n";
		}
	}
}

void consola_UI::filtrare_pret_mai_mic()
{
	cout << "Introduceti pretul: ";
	float pret;
	cin >> pret;
	cout << "Acestea sunt ofertele cu pretul mai mic de " << pret << ":\n";
	vector<Oferta> oferte_filtrate = oferte_store.filtreaza_dupa_pret_mai_mic(pret);
	for (auto i : oferte_filtrate)
	{
		cout << i.obtine_denumire() << " " << i.obtine_destinatie() << " " << i.obtine_tip() << " " << i.obtine_pret() << '\n';
	}
}

void consola_UI::filtrare_destinatie() {
	cout << "Introduceti destinatie: ";
	string destinatie;
	cin >> destinatie;
	cout << "Acestea sunt ofertele care au ca destinatie " << destinatie << ":\n";
	vector<Oferta> oferte_filtrate = oferte_store.filtreaza_dupa_destinatie(destinatie);
	for (auto i : oferte_filtrate)
	{
		cout << i.obtine_denumire() << " " << i.obtine_destinatie() << " " << i.obtine_tip() << " " << i.obtine_pret() << '\n';
	}
}

void consola_UI::gaseste_oferta_UI() {
	cout << "Introduceti denumirea ofertei pe care o cautati: ";
	string denumirea_ofertei_de_cautat;
	cin >> denumirea_ofertei_de_cautat;
	Oferta oferta_gasita=consola_UI::oferte_store.gaseste_oferta(denumirea_ofertei_de_cautat);
	cout << "Oferta gasita este: "<<oferta_gasita.obtine_denumire() << " " << oferta_gasita.obtine_destinatie()<<" "<<oferta_gasita.obtine_tip()<<" " << oferta_gasita.obtine_pret()<<'\n';


	
}

void consola_UI :: undo() {
	oferte_store.undo();
	consola_UI::afiseaza_toate_ofertele_UI();
}

void consola_UI::salveaza_in_fisier_wishlist_ul() {
	cout << "Introduceti numele fisierului: ";
	string nume_fisier;
	cin >> nume_fisier;
	oferte_store.salveaza_wishlist_in_fisier(nume_fisier, wishlist.obtine_tot_wishlist_ul());
}
