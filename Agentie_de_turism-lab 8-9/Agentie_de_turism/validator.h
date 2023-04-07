#include <iostream>
#include "oferta.h"
#include <string>
#include <sstream>
using std::ostream;
class validator_oferta {
	string mesaj_validare="";
public:
	void validare(Oferta oferta_de_validat);
};

class validator_oferta_exceptii {
	
public:
	string mesaj_exceptie;
	validator_oferta_exceptii(string mesaj_validare) : mesaj_exceptie{ mesaj_validare }{}
	friend ostream& operator<<(ostream& afisare, const validator_oferta_exceptii& mesaj_exceptie);
};

ostream& operator<<(ostream& afisare, const validator_oferta_exceptii& mesaj_exceptie);

void test_validator();