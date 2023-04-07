#include "validator.h"
#include <assert.h>
void  validator_oferta::validare(Oferta oferta_de_validat) {
	if (oferta_de_validat.obtine_denumire().size()==0)
		mesaj_validare += " Denumire invalida! ";
	if (oferta_de_validat.obtine_destinatie().size()==0)
		mesaj_validare += " Destinatie invalida! ";
	if (oferta_de_validat.obtine_tip().size()==0)
		mesaj_validare += " Tip invalid! ";
	if (oferta_de_validat.obtine_pret() < 0)
		mesaj_validare += " Pret invalid! ";
	if (mesaj_validare.size() != 0)
		throw validator_oferta_exceptii(mesaj_validare);
}

ostream& operator<<(ostream& afisare, const validator_oferta_exceptii& mesaj_exceptie)
{
	afisare << mesaj_exceptie.mesaj_exceptie;
	return afisare;
}

void test_validator() {
	Oferta oferta_invalida("", "", "", -1);
	validator_oferta validator;
	try {
		validator.validare(oferta_invalida);
		//assert(false);
	}
	catch (validator_oferta_exceptii&)
	{
		assert(true);
	}
}