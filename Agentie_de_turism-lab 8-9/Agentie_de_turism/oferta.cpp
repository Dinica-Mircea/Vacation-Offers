#include "oferta.h"
#include <assert.h>
void test_oferta()
{
	Oferta oferta{"vac","bali","relax",12.4f};
	assert(oferta.obtine_denumire() == "vac");
	assert(oferta.obtine_destinatie() == "bali");
	assert(oferta.obtine_tip() == "relax");
	assert(oferta.obtine_pret() == 12.4f);
	oferta.modifica_destinatie("dest1");
	oferta.modifica_tip("tip1");
	oferta.modifica_pret(10.1f);
	assert(oferta.obtine_destinatie() == "dest1");
	assert(oferta.obtine_tip() == "tip1");
	assert(oferta.obtine_pret() == 10.1f);
}