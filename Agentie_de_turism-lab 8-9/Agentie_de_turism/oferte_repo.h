#pragma once
#include "oferta.h"

#include <vector>
#include "vector_dinamic.h"
#include <ostream>
#include <random>
#include <cstdlib>
#include <ctime>
//#include "undo.h" 

using std::vector;
using std::string;
using std::ostream;
using std::unique_ptr;

//typedef class Vector_dinamic vector;
//template <class ActiuneUndo>
class ActiuneUndo;
class Repo {
public:

	virtual void adauga_oferta(const Oferta& oferta_de_adaugat) = 0;

	virtual const Oferta& gaseste_oferta(string denumire)  = 0;// const;

	virtual const vector<Oferta>& obtine_toate_ofertele() =0;//const noexcept

	virtual void sterge_oferta(string denumire) = 0;//;

	virtual void modifica_destinatie_oferta(const string denumire_oferta, string destinatie_noua) = 0;//;

	virtual void modifica_tip_oferta(const string denumire_oferta, string tip_nou) = 0;//;

	virtual void modifica_pret_oferta(const string denumire_oferta, float pret_nou) = 0;//;

	virtual void distruge_toate_ofertele() = 0;// noexcept;

	virtual void undo() = 0;//;
};
class Oferte_repo:public Repo {
	vector<Oferta> toate_ofertele;
	vector<unique_ptr<ActiuneUndo>> ActiuniUndo;

public:
	Oferte_repo() = default ;

	void adauga_oferta(const Oferta& oferta_de_adaugat) override;

	const Oferta& gaseste_oferta(string denumire) override;

	const vector<Oferta>& obtine_toate_ofertele() override;

	void sterge_oferta(string denumire) override;

	void modifica_destinatie_oferta(const string denumire_oferta, string destinatie_noua) override;

	void modifica_tip_oferta(const string denumire_oferta, string tip_nou) override;

	void modifica_pret_oferta(const string denumire_oferta, float pret_nou) override;

	void distruge_toate_ofertele() override;

	void undo();

};





class Repo_probabilitate_random :public Repo {
	vector<Oferta> toate_ofertele;
	vector<unique_ptr<ActiuneUndo>> ActiuniUndo;
	float probabilitate_exceptie;
public:
	
	Repo_probabilitate_random() noexcept : probabilitate_exceptie{ 0.5}{}//static_cast <float> (rand()) / static_cast <float> (RAND_MAX) } {}
	void arunca_exceptie_cu_probabilitate();

	void adauga_oferta(const Oferta& oferta_de_adaugat) override;

	const Oferta& gaseste_oferta(string denumire); //override;

	const vector<Oferta>& obtine_toate_ofertele() override;

	void sterge_oferta(string denumire) override;

	void modifica_destinatie_oferta(const string denumire_oferta, string destinatie_noua) override;

	void modifica_tip_oferta(const string denumire_oferta, string tip_nou) override;

	void modifica_pret_oferta(const string denumire_oferta, float pret_nou) override;

	void distruge_toate_ofertele() override;

	void undo() override;

};


class Oferte_repo_exceptii {
	string mesaj_exceptie;

public:
	Oferte_repo_exceptii(string mesaj_exceptie): mesaj_exceptie{mesaj_exceptie}{}

	friend ostream& operator<<(ostream& out, const Oferte_repo_exceptii& exceptie);
};

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Oferta oferta_adaugata;
	Oferte_repo& repo;
public:
	UndoAdauga(Oferte_repo& repo, const Oferta& oferta_adaugata) : repo{ repo }, oferta_adaugata{ oferta_adaugata } {}
	void doUndo() override {
		repo.sterge_oferta(oferta_adaugata.obtine_denumire());
	}
};

class UndoSterge : public ActiuneUndo {
	Oferta oferta_stearsa;
	Oferte_repo& repo;
public:
	UndoSterge(Oferte_repo& repo, const Oferta& oferta_stearsa) : repo{ repo }, oferta_stearsa{ oferta_stearsa } {}
	void doUndo() override {
		repo.adauga_oferta(oferta_stearsa);
	}
};

class UndoModifica : public ActiuneUndo {
	Oferta oferta_modificata;
	Oferte_repo& repo;
public:
	UndoModifica(Oferte_repo& repo, const Oferta& oferta_modificata) :repo{ repo }, oferta_modificata{ oferta_modificata } {}
	void doUndo() override {
		repo.sterge_oferta(oferta_modificata.obtine_denumire());
		repo.adauga_oferta(oferta_modificata);
	}
};

class UndoAdauga_random : public ActiuneUndo {
	Oferta oferta_adaugata;
	Repo_probabilitate_random& repo;
public:
	UndoAdauga_random(Repo_probabilitate_random& repo, const Oferta& oferta_adaugata) : repo{repo}, oferta_adaugata{oferta_adaugata} {}
	void doUndo() override {
		repo.sterge_oferta(oferta_adaugata.obtine_denumire());
	}
};

class UndoSterge_random : public ActiuneUndo {
	Oferta oferta_stearsa;
	Repo_probabilitate_random& repo;
public:
	UndoSterge_random(Repo_probabilitate_random& repo, const Oferta& oferta_stearsa) : repo{ repo }, oferta_stearsa{ oferta_stearsa } {}
	void doUndo() override {
		repo.adauga_oferta(oferta_stearsa);
	}
};

class UndoModifica_random : public ActiuneUndo {
	Oferta oferta_modificata;
	Repo_probabilitate_random& repo;
public:
	UndoModifica_random(Repo_probabilitate_random& repo, const Oferta& oferta_modificata) :repo{ repo }, oferta_modificata{ oferta_modificata } {}
	void doUndo() override {
		repo.sterge_oferta(oferta_modificata.obtine_denumire());
		repo.adauga_oferta(oferta_modificata);
	}
};

void test_oferte_repo();

void test_repo_random();

void test_undo();