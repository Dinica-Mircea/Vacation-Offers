#pragma once

#include "oferta.h"
typedef Oferta TElement;
#define capacitate_initiala 2
#include <memory>

class IteratorVector;

class Vector_Dinamic
{
public:

	Vector_Dinamic();

	Vector_Dinamic(const Vector_Dinamic& alt_vector);

	~Vector_Dinamic();

	Vector_Dinamic& operator=(const Vector_Dinamic& alt_vector);

	Vector_Dinamic(Vector_Dinamic&& alt_vector) noexcept;

	Vector_Dinamic& operator=(Vector_Dinamic&& alt_vector) noexcept;

	void adauga_TElement(const TElement& TElement_de_adaugat);

	void sterge_TElement(const int pozitia_TElementului);

	TElement& obtine_TElement(int pozitia_TElementului) const noexcept;

	void modifica_TElement(int pozitia_TElementului, const TElement& TElement_nou);

	int marimea_vectorului() const noexcept;

	friend class IteratorVector;
	IteratorVector begin() noexcept;
	IteratorVector end() noexcept;


private:
	int numar_elemente;
	int capacitate;
	//TElement* toate_elementele;
	std::unique_ptr<TElement[]> toate_elementele;

	void asigura_capacitatea_vectorului();
};

class IteratorVector {
private:
	const Vector_Dinamic& vector_dinamic;
	int pozitia_TElementului = 0;
public:
	IteratorVector(const Vector_Dinamic& vector_dinamic) noexcept;
	IteratorVector(const Vector_Dinamic& vector_dinamic, int pozitia_TElementului)noexcept;
	bool este_valid()const noexcept;
	TElement& element() const noexcept;
	void urmatorul_TElement() noexcept;
	TElement& operator*() noexcept;
	IteratorVector& operator++() noexcept;
	bool operator==(const IteratorVector& alt_iterator)noexcept;
	bool operator!=(const IteratorVector& alt_iterator)noexcept;
};

void test_vector_dinamic();
