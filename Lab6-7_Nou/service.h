#pragma once

#include "repo.h"
#include "validator.h"

/// <summary>
/// Serivce-ul (controller-ul) aplicatiei
/// </summary>
class Service
{

private:

	Repo& repo;
	Validator& validator;

public:

	/*
		Parametri de intrare:
			- r: repository-ul ce trebuie asignat service-ului
			- v: validatorul ce trebuie asignat service-ului

		Parametri de iesire:
			-

		Preconditii:
			- r: obiect de tipul Repository
			- v: obiect de tipul Validator

		Postconditii:
			- this->repo = r
			- this->validator = v

		Constructorul clasei Service.
	*/
	Service(Repo& r, Validator& v) : repo{ r }, validator{ v } {};

	/*
		Parametri de intrare:
			- denumire: string ce reprezinta denumirea Ofertei ce trebuie adaugata
			- destinatie: string ce reprezinta destinatia Ofertei ce trebuie adaugata
			- tip: string ce reprezinta tipul Ofertei ce trebuie adaugata
			- pret: integer ce reprezinta pretul Ofertei ce trebuie adaugata

		Parametri de iesire:
			-

		Preconditii:
			- denumire, destinatie, tip: string-uri
			- pret: integer

		Postconditii:
			- daca datele sunt valide, se creeaza si adauga in repository o Oferta cu datele transmise ca parametri

		Functia valideaza datele noii oferte, si daca totul este in regula, creeaza o Oferta cu aceste date
		si o trimite repository-ului pentru a fi adaugata.
	*/
	void srvAdaugareOferta(const string& denumire, const string& destinatie, const string& tip, const int pret);

	/*
		Parametri de intrare:
			- destinatieOld: string ce reprezinta destinatia Ofertei ce ar trebui sa fie modificata
			- denumire: string ce reprezinta noua denumire a Ofertei ce trebuie modificata
			- destinatie: string ce reprezinta noua destinatie a Ofertei ce trebuie modificata
			- tip: string ce reprezinta noul tip al Ofertei ce trebuie modificata
			- pret: integer ce reprezinta noul pret al Ofertei ce trebuie modificata

		Parametri de iesire:
			-

		Preconditii:
			- destinatieOld, denumire, destinatie, tip: string-uri
			- pret: integer

		Postconditii:
			- daca toate datele sunt valide, se modifica in repository Oferta cu destinatia destinatieOld

		Functia valideaza existenta Ofertei cu destinatia destinatieOld. Daca exista, se valideaza noile date,
		si daca totul este in regula, se modifica in repository Oferta.
	*/
	void srvModificareOferta(const string& destinatieOld, const string& denumire, const string& destinatie, const string& tip, const int pret);

	/*
		Parametri de intrare:
			- destinatie: string-ul dupa care trebuie stersa Oferta

		Parametri de iesire:
			-

		Preconditii:
			- destinatie: string

		Postconditi:
			- daca Oferta cu destinatia transmisa ca parametru exista, va fi stearsa din repository

		Functia sterge Oferta cu destinatia transmisa ca parametru, daca aceasta exista in repository.
	*/
	void srvStergereOferta(const string& destinatie);

	/*
		Parametri de intrare:
			- destinatie: string ce reprezinta destinatia Ofertei ce trebuie cautate

		Parametri de iesire:
			-

		Preconditii:
			- destinatie: string

		Postconditii:
			-

		Functia cauta in repository Oferta cu destinatia data si arunca eroare daca nu exista,
		sau ii returneaza indexul daca exista. 
	*/
	const int srvCautareOferta(const string& destinatie);

	/*
		Parametri de intrare / iesire:
			- 

		Preconditii / postconditii:
			-

		Functia de getter pentru Repository-ul Service-ului.
	*/
	Repo srvGetRepo() const;

	/*
		Parametri de intrare:
			- substr: subsirul dupa care se va realiza filtrarea

		Parametri de iesire:
			-

		Preconditii:
			- substr: string

		Postconditii:
			-

		Functia are rolul de a valida subsirul transmis ca parametru 
		si de a apela functii din repository pentru filtrare.
	*/
	const DynamicArray<Oferta> srvFiltrareDupaDestinatie(const string& substr);

	/*
		Parametri de intrare:
			- pret: pretul dupa care se va realiza filtrarea

		Parametri de iesire:
			-

		Preconditii:
			- pret: integer

		Postconditii:
			-

		Functia are rolul de a valida pretul transmis ca parametru si de a apela functii din repository pentru filtrare.
	*/
	const DynamicArray<Oferta> srvFiltrareDupaPret(const int pret);

	/*
		Parametri de intrare:
			- ord: ordinea sortarii
			- camp: string

		Parametri de iesire:
			-
		Preconditii:
			- ord: string
			- camp: string

		Postconditii:
			-

		Functia are rolul de a valida campul transmis ca parametru 
		si de a apela functii din repository ce sorteaza lista de Oferte.
	*/
	void srvSortareGenerica(const string& ord, const string& camp);
};