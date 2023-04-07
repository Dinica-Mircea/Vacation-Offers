// Agentie_de_turism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "oferta.h"
#include "oferte_repo.h"
#include "interfata_utilizator.h"
#include "oferte_store.h"
#include "vector_dinamic.h"
#include "validator.h"
//#include "wishlist.h"
void ruleaza_toate_testele()
{
    std::cout << "Au inceput testele..\n";
    test_oferta();
    test_validator();
    test_oferte_repo();
    test_oferte_store();
    test_filtrare_store();
    test_sortare_store();
    test_vector_dinamic();
    test_wishlist();
    test_undo();
    test_salvare_in_fisier();
    test_repo_random();
    std::cout << "S-au terminat testele!\n";
}
int main()
{
    ruleaza_toate_testele();
    srand(static_cast<unsigned> (time(0)));
    Oferte_repo oferte_repo;
    Repo_probabilitate_random repo_random;
    Oferte_store oferte_store(repo_random);
    wishlist_oferte wishlist(oferte_repo);
    consola_UI consola(oferte_store,wishlist);
    consola.incepe_UI();
    oferte_repo.distruge_toate_ofertele();
    _CrtDumpMemoryLeaks();
 
}

