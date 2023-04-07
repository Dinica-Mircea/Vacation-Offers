#include "vector_dinamic.h"
#include "assert.h"
#include <iostream>
#include <string>
#include <set>
#include <tuple>


Vector_Dinamic::Vector_Dinamic() :toate_elementele{ std::make_unique <TElement[]>(capacitate_initiala)}, capacitate{capacitate_initiala}, numar_elemente{0} {}

Vector_Dinamic::Vector_Dinamic(const Vector_Dinamic& alt_vector) {
	toate_elementele = std::make_unique<TElement[]>(alt_vector.capacitate);
	for (int i = 0; i < alt_vector.numar_elemente; i++) {
		obtine_TElement(i) = alt_vector.obtine_TElement(i);
	}
	numar_elemente = alt_vector.numar_elemente;
	capacitate = alt_vector.capacitate;
}

Vector_Dinamic& Vector_Dinamic::operator=(const Vector_Dinamic& alt_vector) {
	if (this == &alt_vector) {
		return *this;
	}
	if (toate_elementele != nullptr) {
		toate_elementele.reset();
		toate_elementele = std::make_unique <TElement[]>(alt_vector.capacitate);
		for (int i = 0; i < alt_vector.numar_elemente; i++) {
			obtine_TElement(i) = alt_vector.obtine_TElement(i);
		}
		numar_elemente = alt_vector.numar_elemente;
		capacitate = alt_vector.capacitate;
	}
		return *this;
}

Vector_Dinamic::~Vector_Dinamic() {
	//if(toate_elementele!=nullptr)
	toate_elementele.reset();
}

Vector_Dinamic::Vector_Dinamic(Vector_Dinamic&& alt_vector) noexcept{
	std::swap(toate_elementele, alt_vector.toate_elementele);
	numar_elemente = alt_vector.numar_elemente;
	capacitate = alt_vector.capacitate;
	alt_vector.toate_elementele = nullptr;
	alt_vector.numar_elemente = 0;
	alt_vector.capacitate = 0;
}

Vector_Dinamic& Vector_Dinamic::operator=(Vector_Dinamic&& alt_vector) noexcept{
	if (this == &alt_vector) {
		return *this;
	}
	if (toate_elementele != nullptr) {
		toate_elementele.reset();
		std::swap(toate_elementele,alt_vector.toate_elementele);
		numar_elemente = alt_vector.numar_elemente;
		capacitate = alt_vector.capacitate;
		alt_vector.toate_elementele = nullptr;
		alt_vector.numar_elemente = 0;
		alt_vector.capacitate = 0;
	}
	return *this;
}

void Vector_Dinamic::adauga_TElement(const TElement& TElement_de_adaugat) {
	asigura_capacitatea_vectorului();
	obtine_TElement(numar_elemente++) = TElement_de_adaugat;
}

TElement& Vector_Dinamic::obtine_TElement(int pozitia_TElementului) const noexcept{
	return toate_elementele[pozitia_TElementului];
}

void Vector_Dinamic::modifica_TElement(int pozitia_TElementului, const TElement& TElement_nou) {
	obtine_TElement(pozitia_TElementului) = TElement_nou;
}

int Vector_Dinamic::marimea_vectorului() const noexcept {
	return numar_elemente;
}

void Vector_Dinamic::asigura_capacitatea_vectorului() {
	if (numar_elemente < capacitate) {
		return; //mai avem loc
	}
	capacitate *= 2;
	//TElement* copia_TElementelor = new TElement[capacitate];
	auto copia_TElementelor = std::make_unique<TElement[]>(capacitate);
	for (int i = 0; i < numar_elemente; i++) {
		copia_TElementelor[i] = obtine_TElement(i);
	}
	toate_elementele.reset();
	std::swap(toate_elementele, copia_TElementelor);
}

void Vector_Dinamic::sterge_TElement(const int pozitia_TElementului)
{
	Vector_Dinamic Vector_fara_TElement;
	//int pozitie = 0;
	for (int i = 0; i < numar_elemente; i++)
	{
		if (i != pozitia_TElementului)
		Vector_fara_TElement.adauga_TElement(obtine_TElement(i));
	}
	toate_elementele.reset();
	std::swap(toate_elementele, Vector_fara_TElement.toate_elementele);
	numar_elemente--;

}

IteratorVector Vector_Dinamic::begin() noexcept
{
	return IteratorVector(*this); 
}

IteratorVector Vector_Dinamic::end() noexcept
{
	return IteratorVector(*this, numar_elemente);
}


IteratorVector::IteratorVector(const Vector_Dinamic& vector_dinamic) noexcept :vector_dinamic{ vector_dinamic } {}
IteratorVector::IteratorVector(const Vector_Dinamic& vector_dinamic, int pozitia_TElementului)noexcept :vector_dinamic{ vector_dinamic }, pozitia_TElementului{ pozitia_TElementului } {}

bool IteratorVector::este_valid()const noexcept {
	return pozitia_TElementului < vector_dinamic.numar_elemente;
}
TElement& IteratorVector::element() const noexcept {
	return vector_dinamic.obtine_TElement(pozitia_TElementului);
}
void IteratorVector::urmatorul_TElement() noexcept {
	pozitia_TElementului++;
}
TElement& IteratorVector::operator*() noexcept{
	return element();
}
IteratorVector& IteratorVector::operator++() noexcept{
	urmatorul_TElement();
	return *this;
}
bool IteratorVector::operator==(const IteratorVector& ot) noexcept {
	return pozitia_TElementului == ot.pozitia_TElementului;
}
bool IteratorVector::operator!=(const IteratorVector& ot)noexcept {
	return !(*this == ot);
}

void test_vector_dinamic() {
	Vector_Dinamic vector;
	Oferta Oferta1{ "vac1","dest1","tip1",1 };
	Oferta Oferta2{ "vac2","dest2","tip2",2 };
	Oferta Oferta3{ "vac3","dest3","tip3",3 };
	vector.adauga_TElement(Oferta1);
	vector.adauga_TElement(Oferta2);
	assert(vector.marimea_vectorului() == 2);
	vector.modifica_TElement(1, Oferta3);
	assert(vector.obtine_TElement(1).obtine_denumire() == Oferta3.obtine_denumire());
	assert(vector.begin().element().obtine_denumire() == Oferta1.obtine_denumire());
	//assert(vector.end().element().obtine_denumire() == Oferta2.obtine_denumire());
	//std::cout << vector.end().element().obtine_denumire();
	Vector_Dinamic vector_copie;
	vector_copie = vector;
	assert(vector_copie.marimea_vectorului() == 2);
	IteratorVector iterator(vector_copie,0);
	assert(iterator.element().obtine_denumire() == Oferta1.obtine_denumire());
	++iterator;
	assert(iterator.element().obtine_denumire() == Oferta3.obtine_denumire());
	IteratorVector const alt_iterator(vector_copie, 1);
	assert(iterator == alt_iterator);
	assert(iterator.operator*().obtine_denumire() == Oferta3.obtine_denumire());
	vector_copie = vector_copie;
	assert(vector_copie.marimea_vectorului() == 2);
	vector_copie.adauga_TElement(Oferta2);
	assert(vector_copie.marimea_vectorului() == 3);
	Vector_Dinamic alta_copie(vector_copie);
	assert(alta_copie.marimea_vectorului() == 3);
	IteratorVector const iterator_copie(vector_copie, 0);
	Oferta Oferta4{ "vac4","dest4","tip4",4 };
	alta_copie.adauga_TElement(Oferta4);
	alta_copie.end();
	Vector_Dinamic const*const inca_unul(&vector);
	assert(inca_unul != nullptr);
	iterator.urmatorul_TElement();
	assert(iterator != alt_iterator);
	assert(iterator.este_valid() == true);
	++iterator;
	vector.~Vector_Dinamic();
	vector_copie.~Vector_Dinamic();
	inca_unul->~Vector_Dinamic();
}