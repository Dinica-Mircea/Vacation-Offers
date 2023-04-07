//class Oferta;
//class Oferte_repo;
//class ActiuneUndo {
//public:
//	virtual void doUndo() = 0;
//	virtual ~ActiuneUndo() = default;
//};
//
//class UndoAdauga : public ActiuneUndo {
//	Oferta oferta_adaugata;
//	Oferte_repo& repo;
//public:
//	UndoAdauga(Oferte_repo& repo,const Oferta& oferta_adaugata): repo{repo},oferta_adaugata{oferta_adaugata} {}
//	void doUndo() override {
//		repo.sterge_oferta(oferta_adaugata.obtine_denumire());
//	}
//};
//
//class UndoSterge : public ActiuneUndo {
//	Oferta oferta_stearsa;
//	Oferte_repo &repo;
//public:
//	UndoSterge(Oferte_repo& repo,const Oferta& oferta_stearsa) : repo{repo},oferta_stearsa{oferta_stearsa} {}
//	void doUndo() override {
//		repo.adauga_oferta(oferta_stearsa);
//	}
//};
//
//class UndoModifica : public ActiuneUndo {
//	Oferta oferta_modificata;
//	Oferte_repo& repo;
//public:
//	UndoModifica(Oferte_repo& repo,const Oferta& oferta_modificata) :repo{repo}, oferta_modificata{oferta_modificata} {}
//	void doUndo() override {
//		repo.sterge_oferta(oferta_modificata.obtine_denumire());
//		repo.adauga_oferta(oferta_modificata);
//	}
//};