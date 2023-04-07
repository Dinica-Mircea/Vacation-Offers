#include "oferte_repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <sstream>
#include <set>
#include <tuple>
#include "validator.h"
#include <algorithm>
#include <iterator>
//#include <bits/stdc++.h>
using std::ostream;
using std::stringstream;
using std::vector;
using std::find_if;

void Oferte_repo::adauga_oferta(const Oferta& oferta_de_adaugat)
{
	validator_oferta validator;
	validator.validare(oferta_de_adaugat);
	auto rezultat_cautare=find_if(toate_ofertele.begin(), toate_ofertele.end(), [oferta_de_adaugat](Oferta oferta) {return oferta.obtine_denumire() == oferta_de_adaugat.obtine_denumire(); });
	if(rezultat_cautare != toate_ofertele.end())
		throw Oferte_repo_exceptii("Exista deja oferta cu denumrea: " + oferta_de_adaugat.obtine_denumire() + "\n");
	/*for (auto oferta:toate_ofertele)
		if (oferta.obtine_denumire() == oferta_de_adaugat.obtine_denumire())*/
		
	Oferte_repo::toate_ofertele.push_back(oferta_de_adaugat);
	ActiuniUndo.push_back(std::make_unique<UndoAdauga>(*this, oferta_de_adaugat));
}

const Oferta& Oferte_repo::gaseste_oferta(string denumire) {
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire)
		{
			return Oferte_repo::toate_ofertele.at(i); //a_fost_gasita_oferta = true;
		}
		i++;
	}
	throw Oferte_repo_exceptii("Nu exista oferta cu denumirea: " + denumire + "\n");

}	

const vector<Oferta>& Oferte_repo::obtine_toate_ofertele() {
	return Oferte_repo::toate_ofertele;
}

void Oferte_repo::sterge_oferta(string denumire) {
	bool a_fost_stearsa_oferta = false;
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire)
		{
			ActiuniUndo.push_back(std::make_unique<UndoSterge>(*this, gaseste_oferta(denumire)));
			Oferte_repo::toate_ofertele.erase(toate_ofertele.begin() + i); a_fost_stearsa_oferta = true;
			//ActiuniUndo.push_back(UndoSterge(this, oferta));
			
		}
		i++;
	}
	
	if (a_fost_stearsa_oferta == false)
		throw Oferte_repo_exceptii("Nu exista oferta de sters cu denumirea: " + denumire);
	
}

void Oferte_repo::distruge_toate_ofertele()
{
	toate_ofertele.~vector();
}
void test_oferte_repo() {
	Oferte_repo Oferte_repo_test;
	Oferta Oferta1{ "vac1","dest1","tip1",1 };
	Oferta Oferta2{ "vac2","dest2","tip2",2 };
	Oferta Oferta3{ "vac3","dest3","tip3",3 };
	Oferte_repo_test.adauga_oferta(Oferta1);
	Oferte_repo_test.adauga_oferta(Oferta2);
	Oferte_repo_test.adauga_oferta(Oferta3);
	assert(Oferte_repo_test.gaseste_oferta("vac1").obtine_destinatie() == Oferta1.obtine_destinatie());
	vector<Oferta> copie_repo = Oferte_repo_test.obtine_toate_ofertele();
	assert(copie_repo.size() == 3);
	try {
		Oferte_repo_test.gaseste_oferta("vac4");
	}
	catch (Oferte_repo_exceptii&) {
		assert(true);
	}
	Oferte_repo_test.sterge_oferta(Oferta1.obtine_denumire());
	try {
		Oferte_repo_test.gaseste_oferta("vac1");
	}
	catch (Oferte_repo_exceptii&) {
		assert(true);
	}
	assert(Oferte_repo_test.obtine_toate_ofertele().size() == 2);
	assert(Oferte_repo_test.gaseste_oferta("vac2").obtine_destinatie() == "dest2");
	Oferte_repo_test.modifica_destinatie_oferta("vac2", "bali");
	Oferte_repo_test.modifica_pret_oferta("vac2", 10.1f);
	Oferte_repo_test.modifica_tip_oferta("vac2", "cu bizu");
	//cout << Oferte_repo_test.gaseste_oferta("vac2").obtine_destinatie();
	assert(Oferte_repo_test.gaseste_oferta("vac2").obtine_destinatie() == "bali");
	assert(Oferte_repo_test.gaseste_oferta("vac2").obtine_pret() == 10.1f);
	assert(Oferte_repo_test.gaseste_oferta("vac2").obtine_tip() == "cu bizu");
	
	Oferta Oferta2_aceeasi_denumire{ "vac2","dest10","tip10",10 };
	try {
		Oferte_repo_test.adauga_oferta(Oferta2_aceeasi_denumire);
	}
	catch (Oferte_repo_exceptii&) {
		assert(true);
	}
	try {
		Oferte_repo_test.sterge_oferta("vac1");
		//assert(false);
	}
	catch (Oferte_repo_exceptii&) {
		assert(true);
	}
	Oferte_repo_test.distruge_toate_ofertele();

}

void test_repo_random() {
	Repo_probabilitate_random Oferte_repo_test;
	Oferta Oferta1{ "vac1","dest1","tip1",1 };
	Oferta Oferta2{ "vac2","dest2","tip2",2 };
	Oferta Oferta3{ "vac3","dest3","tip3",3 };
	try {
		Oferte_repo_test.adauga_oferta(Oferta1);
		Oferte_repo_test.adauga_oferta(Oferta2);
		Oferte_repo_test.adauga_oferta(Oferta3);
		assert(Oferte_repo_test.gaseste_oferta("vac1").obtine_destinatie() == Oferta1.obtine_destinatie());
		vector<Oferta> copie_repo = Oferte_repo_test.obtine_toate_ofertele();
		assert(copie_repo.size() == 3);
		try {
			Oferte_repo_test.gaseste_oferta("vac4");
		}
		catch (Oferte_repo_exceptii&) {
			assert(true);
		}
		Oferte_repo_test.sterge_oferta(Oferta1.obtine_denumire());
		try {
			Oferte_repo_test.gaseste_oferta("vac1");
		}
		catch (Oferte_repo_exceptii&) {
			assert(true);
		}
		assert(Oferte_repo_test.obtine_toate_ofertele().size() == 2);
		assert(Oferte_repo_test.gaseste_oferta("vac2").obtine_destinatie() == "dest2");
		Oferte_repo_test.modifica_destinatie_oferta("vac2", "bali");
		Oferte_repo_test.modifica_pret_oferta("vac2", 10.1f);
		Oferte_repo_test.modifica_tip_oferta("vac2", "cu bizu");
		//cout << Oferte_repo_test.gaseste_oferta("vac2").obtine_destinatie();
		assert(Oferte_repo_test.gaseste_oferta("vac2").obtine_destinatie() == "bali");
		assert(Oferte_repo_test.gaseste_oferta("vac2").obtine_pret() == 10.1f);
		assert(Oferte_repo_test.gaseste_oferta("vac2").obtine_tip() == "cu bizu");

		Oferta Oferta2_aceeasi_denumire{ "vac2","dest10","tip10",10 };
		try {
			Oferte_repo_test.adauga_oferta(Oferta2_aceeasi_denumire);
		}
		catch (Oferte_repo_exceptii&) {
			assert(true);
		}
		try {
			Oferte_repo_test.sterge_oferta("vac1");
			//assert(false);
		}
		catch (Oferte_repo_exceptii&) {
			assert(true);
		}
		Oferte_repo_test.distruge_toate_ofertele();
	}
	catch (Oferte_repo_exceptii&) {
		assert(true);
	}
}

void Oferte_repo::undo() {
	if (ActiuniUndo.empty()) {
		throw Oferte_repo_exceptii("Nu a fost facuta nici o operatie!\n");
	}
	ActiuniUndo.back()->doUndo();
	ActiuniUndo.pop_back();
	ActiuniUndo.pop_back();
}

void test_undo() {
	Oferte_repo Oferte_repo_test;
	Oferta Oferta1{ "vac1","dest1","tip1",1 };
	Oferta Oferta2{ "vac2","dest2","tip2",2 };
	Oferta Oferta3{ "vac3","dest3","tip3",3 };
	try {
		Oferte_repo_test.undo();
	}
	catch (Oferte_repo_exceptii&)
	{
		assert(true);
	}
	Oferte_repo_test.adauga_oferta(Oferta1);
	Oferte_repo_test.undo();
	assert(Oferte_repo_test.obtine_toate_ofertele().size() == 0);
	Oferte_repo_test.adauga_oferta(Oferta1);
	Oferte_repo_test.adauga_oferta(Oferta2);
	Oferte_repo_test.adauga_oferta(Oferta3);
	Oferte_repo_test.sterge_oferta(Oferta3.obtine_denumire());
	Oferte_repo_test.undo();
	Oferte_repo_test.undo();
	assert(Oferte_repo_test.obtine_toate_ofertele().size() == 2);
	Oferte_repo_test.modifica_pret_oferta("vac1", 10.4f);
	Oferte_repo_test.undo();
	assert(Oferte_repo_test.gaseste_oferta("vac1").obtine_pret() == 1);
	
}
void Oferte_repo::modifica_destinatie_oferta(const string denumire_oferta, string destinatie_noua)
{
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire_oferta)
		{
			//Oferta oferta_de_modificat = gaseste_oferta(denumire_oferta);
			//assert(false);
			//oferta_de_modificat.modifica_destinatie(destinatie_noua);
			//assert(oferta_de_modificat.obtine_destinatie() == destinatie_noua);
			toate_ofertele.at(i).modifica_destinatie(destinatie_noua);
			ActiuniUndo.push_back(std::make_unique<UndoModifica>(*this, oferta));
		}
		i++;
	}
}
void Oferte_repo::modifica_tip_oferta(const string denumire_oferta, string tip_nou)
{
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire_oferta)
		{
			//Oferta oferta_de_modificat = gaseste_oferta(denumire_oferta);
			//assert(false);
			//oferta_de_modificat.modifica_destinatie(destinatie_noua);
			//assert(oferta_de_modificat.obtine_destinatie() == destinatie_noua);
			toate_ofertele.at(i).modifica_tip(tip_nou);
			ActiuniUndo.push_back(std::make_unique<UndoModifica>(*this, oferta));
		}
		i++;
	}
}

void Oferte_repo::modifica_pret_oferta(const string denumire_oferta, float pret_nou)
{
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire_oferta)
		{
			//Oferta oferta_de_modificat = gaseste_oferta(denumire_oferta);
			//assert(false);
			//oferta_de_modificat.modifica_destinatie(destinatie_noua);
			//assert(oferta_de_modificat.obtine_destinatie() == destinatie_noua);
			toate_ofertele.at(i).modifica_pret(pret_nou);
			ActiuniUndo.push_back(std::make_unique<UndoModifica>(*this, oferta));
		}
		i++;
	}
}
ostream& operator<<(ostream& afisare, const Oferte_repo_exceptii& exceptie) {
	afisare << exceptie.mesaj_exceptie;
	return afisare;
}

void Repo_probabilitate_random::arunca_exceptie_cu_probabilitate() {
	
	float const probabilitate = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/1);
	//cout << probabilitate_exceptie<<" "<<probabilitate  << std::endl;
	float const probabilitate_mesaj = probabilitate_exceptie * 100;
	string mesaj(std::to_string(probabilitate_mesaj));
	if (probabilitate < probabilitate_exceptie)
		throw Oferte_repo_exceptii("Ghinion, ai o sansa de " + mesaj + "% esec! \n");
}

void Repo_probabilitate_random::undo() {
	arunca_exceptie_cu_probabilitate();
	//oferte_repo.undo();
	if (ActiuniUndo.empty()) {
		throw Oferte_repo_exceptii("Nu a fost facuta nici o operatie!\n");
	}
	ActiuniUndo.back()->doUndo();
	ActiuniUndo.pop_back();
}

void Repo_probabilitate_random::adauga_oferta(const Oferta& oferta_de_adaugat)
{
	arunca_exceptie_cu_probabilitate();
	//oferte_repo.adauga_oferta(oferta_de_adaugat);
	validator_oferta validator;
	validator.validare(oferta_de_adaugat);
	auto rezultat_cautare = find_if(toate_ofertele.begin(), toate_ofertele.end(), [oferta_de_adaugat](Oferta oferta) {return oferta.obtine_denumire() == oferta_de_adaugat.obtine_denumire(); });
	if (rezultat_cautare != toate_ofertele.end())
		throw Oferte_repo_exceptii("Exista deja oferta cu denumrea: " + oferta_de_adaugat.obtine_denumire() + "\n");
	/*for (auto oferta:toate_ofertele)
		if (oferta.obtine_denumire() == oferta_de_adaugat.obtine_denumire())*/

	Repo_probabilitate_random::toate_ofertele.push_back(oferta_de_adaugat);
	ActiuniUndo.push_back(std::make_unique<UndoAdauga_random>(*this, oferta_de_adaugat));
}

const Oferta& Repo_probabilitate_random::gaseste_oferta(string denumire){ //override  {
	arunca_exceptie_cu_probabilitate();

	//return oferte_repo.gaseste_oferta(denumire);
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire)
		{
			return toate_ofertele.at(i); //a_fost_gasita_oferta = true;
		}
		i++;
	}
	throw Oferte_repo_exceptii("Nu exista oferta cu denumirea: " + denumire + "\n");

}

const vector<Oferta>& Repo_probabilitate_random::obtine_toate_ofertele() {
	//arunca_exceptie_cu_probabilitate();
	//return oferte_repo.obtine_toate_ofertele();
	return toate_ofertele;
}

void Repo_probabilitate_random::sterge_oferta(string denumire) {
	arunca_exceptie_cu_probabilitate();
	//oferte_repo.sterge_oferta(denumire);
	bool a_fost_stearsa_oferta = false;
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire)
		{
			ActiuniUndo.push_back(std::make_unique<UndoSterge_random>(*this, gaseste_oferta(denumire)));
			toate_ofertele.erase(toate_ofertele.begin() + i); a_fost_stearsa_oferta = true;
			//ActiuniUndo.push_back(UndoSterge(this, oferta));

		}
		i++;
	}

	if (a_fost_stearsa_oferta == false)
		throw Oferte_repo_exceptii("Nu exista oferta de sters cu denumirea: " + denumire);

}

void Repo_probabilitate_random::distruge_toate_ofertele()
{
	arunca_exceptie_cu_probabilitate();
	//oferte_repo.distruge_toate_ofertele();
	toate_ofertele.~vector();
}

void Repo_probabilitate_random::modifica_destinatie_oferta(const string denumire_oferta, string destinatie_noua)
{
	arunca_exceptie_cu_probabilitate();
	//oferte_repo.modifica_destinatie_oferta(denumire_oferta, destinatie_noua);
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire_oferta)
		{
			//Oferta oferta_de_modificat = gaseste_oferta(denumire_oferta);
			//assert(false);
			//oferta_de_modificat.modifica_destinatie(destinatie_noua);
			//assert(oferta_de_modificat.obtine_destinatie() == destinatie_noua);
			toate_ofertele.at(i).modifica_destinatie(destinatie_noua);
			ActiuniUndo.push_back(std::make_unique<UndoModifica_random>(*this, oferta));
		}
		i++;
	}
}
void Repo_probabilitate_random::modifica_tip_oferta(const string denumire_oferta, string tip_nou)
{
	arunca_exceptie_cu_probabilitate();
	//oferte_repo.modifica_tip_oferta(denumire_oferta, tip_nou);
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire_oferta)
		{
			//Oferta oferta_de_modificat = gaseste_oferta(denumire_oferta);
			//assert(false);
			//oferta_de_modificat.modifica_destinatie(destinatie_noua);
			//assert(oferta_de_modificat.obtine_destinatie() == destinatie_noua);
			toate_ofertele.at(i).modifica_tip(tip_nou);
			ActiuniUndo.push_back(std::make_unique<UndoModifica_random>(*this, oferta));
		}
		i++;
	}
}

void Repo_probabilitate_random::modifica_pret_oferta(const string denumire_oferta, float pret_nou)
{
	arunca_exceptie_cu_probabilitate();
	//oferte_repo.modifica_pret_oferta(denumire_oferta, pret_nou);
	int i = 0;
	for (auto oferta : toate_ofertele)
	{
		if (oferta.obtine_denumire() == denumire_oferta)
		{
			//Oferta oferta_de_modificat = gaseste_oferta(denumire_oferta);
			//assert(false);
			//oferta_de_modificat.modifica_destinatie(destinatie_noua);
			//assert(oferta_de_modificat.obtine_destinatie() == destinatie_noua);
			toate_ofertele.at(i).modifica_pret(pret_nou);
			ActiuniUndo.push_back(std::make_unique<UndoModifica_random>(*this, oferta));
		}
		i++;
	}
}