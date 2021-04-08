#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "domain.h"
#include "utils.h"
#include "DynamicArray.h"

using std::swap;

/// <summary>
/// Repository-ul de Oferte.
/// </summary>
class Repo
{

private:

	DynamicArray<Oferta> continut;

public:

	/*
		Parametri de intrare / iesire:
			-

		Preconditii:
			-

		Postconditii:
			- se va crea un repository vid

		Constructorul pentru obiectele de tip Repo.
	*/
	Repo();

	/*
		Parametri de intrare:
			- repo: repo-ul cu care trebuie comparat repo-ul curent

		Parametri de iesire:
			-

		Preconditii:
			- other: un obiect de tipul Repo

		Postconditii:
			-

		Supraincarcarea operatorului ==
		Functia returneaza true daca obiectul curent este egal cu obiectul other,
		sau false in caz contrar.
	*/
	bool operator ==(const Repo& other) const;

	/*
		Parametri de intrare / iesire:
			-
		
		Preconditii / postconditii:
			-

		Functie getter pentru continutul repository-ului.
	*/
	const DynamicArray<Oferta>& getContinut() const;

	/*
		Parametri de intrare:
			- newContinut: std::vector de Oferte ce va fi noul continut al Repository-ului

		Parametri de iesire:
			-

		Preconditii:
			- newContinut: std::vector de Oferte

		Postconditii:
			- this->continut = newContinut

		Functie ce actualizeaza continutul obiectului curent cu cel nou, transmis ca parametru.
	*/
	void setContinut(const DynamicArray<Oferta>& newContinut);

	/*
		Parametri de intrare:
			- of: obiect de tipul Oferta, ce trebuie adaugat in continutul repository-ului

		Parametri de iesire:
			- 

		Preconditii:
			- of: obiect de tipul Oferta

		Postconditii:
			- this->continut = this->continut + of

		Functia adauga Oferta transmisa ca parametru in continutul repository-ului.
	*/
	void repoAdaugareOferta(const Oferta& of);

	/*	
		Parametri de intrare:
			- of: obiect de tipul Oferta; trebuie sa se verifice daca exista sau nu in continutul repository-ului

		Parametri de iesire:
			-
		
		Preconditii / postconditii:
			-

		Functia verifica daca oferta of exista in continutul repository-ului
		si returneaza true daca da, sau false in caz contrar.
	*/
	const bool repoExistentaOferta(const Oferta& of);

	/*
		Parametri de intrare:
			- of: obiect de tipul Oferta, ce trebuie sters din continutul repository-ului.

		Parametri de iesire:
			-

		Preconditii:
			- of: obiect de tipul Oferta ce apartine continutului repository-ului.

		Postconditii:
			- this->continut = this->continut - of
	*/
	void repoStergereOferta(const Oferta& of);

	/*
		Parametri de intrare:
			- ofOld: obiect de tipul Oferta, ce trebuie modificat
			- denumire: string, noua denumire a obiectului ce trebuie modificat
			- destinatie: string, noua destinatie a obiectului ce trebuie modificat
			- tip: string, noul tip al obiectului ce trebuie modificat
			- pret: integer, noul pret al obiectului ce trebuie modificat

		Parametri de iesire:
			-

		Preconditii:
			- ofOld: obiect de tipul Oferta
			- denumire, destinatie, tip: string-uri nevide
			- pret: integer pozitiv nenul

		Functia modifica datele ofertei ofOld cu cele noi, date ca parametri.
	*/
	void repoModificareOferta(const Oferta& ofOld, const string& denumire, const string& destinatie, const string& tip, const int pret);

	/*
		Parametri de intrare:
			- of: Oferta a carui index trebuie returnat

		Parametri de iesire:
			-

		Preconditii:
			-

		Postconditii:
			-

		Functia returneaza -1 daca Oferta transmisa ca parametru nu exista in repository, sau indexul sau in caz contrar.
	*/
	const int getIndexFromOferta(const Oferta& of) ;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditie:
			-

		Functie de getter pentru continutul repository-ului, ce returneaza o referinta catre acesta.
	*/
	DynamicArray<Oferta>& getContinutRef() ;

	/*
		Parametri de intrare:
			- substr: string-ul ce reprezinta subsirul dupa care se va realiza filtrarea

		Parametri de iesire:
			-

		Preconditii:
			- substr: string

		Postconditii:
			-

		Functia returneaza un vector de Oferte ce contine toate Ofertele care au in destinatie subsirul dat ca parametru.
	*/
	DynamicArray<Oferta> repoFiltrareDupaDestinatie(const string& substr);

	/*
		Parametri de intrare:
			- pret: pretul dupa care se va realiza filtrarea

		Parametri de iesire:
			- 

		Preconditii:
			- pret: integer

		Postconditii:
			-

		Functia returneaza un vector de Oferte ce contine toate Ofertele care au pretul mai mic sau egal cu cel dat ca parametru.
	*/
	const DynamicArray<Oferta> repoFiltrareDupaPret(const int pret);

	/*
		Parametri de intrare:
			- cresc: ordinea sortarii (crescator = true / descrescator = false)
			- camp: campul dupa care se va face sortarea

		Parametri de iesire:
			-

		Preconditii:
			- cresc: boolean
			- camp: string (denumire / destinatie / tip + pret)

		Functia sorteaza repository-ul in functie de ordinea si campul dat.
	*/
	void repoSortareGenerica(const bool cresc, const string camp);

	/*
		Parametri de intrare:
			- cresc: ordinea sortarii

		Parametri de iesire:
			-

		Preconditii:
			-

		Postconditii:
			-

		Functia sorteaza repository-ul dupa doua criterii (tip si pret).
	*/
	void repoSortareMultipla(const bool cresc);
};