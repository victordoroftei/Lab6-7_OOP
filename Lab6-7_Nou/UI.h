#pragma once

#include "repo.h"
#include "service.h"
#include "utils.h"

using std::cout;
using std::cin;

class Console
{

private:

	Service& srv;
	Repo& repo;
	Validator& validator;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia afiseaza repository-ul.
	*/
	void afisareRepo();

	/*
		Parametri de intrare:
			- index: integer ce reprezinta indexul Ofertei ce trebuie afisata

		Parametri de iesire:
			-

		Preconditii / postconditii:
			-

		Functia afiseaza Oferta din repository cu indexul dat.
	*/
	void afisareOfertaDupaIndex(const int index);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia ce afiseaza meniul.
	*/
	void afisareMeniu();

	/*
		Parametri de intrare:
			- vec: vectorul de Oferte ce trebuie afisat

		Parametri de iesire:
			- 

		Preconditii:
			- vec: vector de Oferte

		Postconditii:
			-

		Functia afiseaza vectorul de Oferte.
	*/
	void afisareVectorOferte(const DynamicArray<Oferta>& vec);

public:

	Console(Service& s, Repo& r, Validator& v) : srv{ s }, repo{ r }, validator{ v } {};

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			- 

		Functia ce serveste pe post de consola / meniu.
	*/
	void run();	

};