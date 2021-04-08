#include "service.h"

void Service::srvAdaugareOferta(const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	try
	{
		this->validator.validareDateOferta(denumire, destinatie, tip, pret);

		Oferta of(denumire, destinatie, tip, pret);

		if (this->repo.repoExistentaOferta(of) == true)
			throw RepoError("Exista deja o Oferta cu aceasta destinatie, deci nu se poate face adaugarea!", 0);

		this->repo.repoAdaugareOferta(of);
	}

	catch (...)
	{
		throw;}
}

void Service::srvModificareOferta(const string& destinatieOld, const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	try
	{
		Oferta ofOld("", destinatieOld, "", 0);

		if (this->repo.repoExistentaOferta(ofOld) == false)
			throw RepoError("Nu exista o Oferta cu aceasta destinatie, deci nu se poate face modificarea!", 1);

		this->validator.validareDateOferta(denumire, destinatie, tip, pret);

		this->repo.repoModificareOferta(ofOld, denumire, destinatie, tip, pret);
	}

	catch (...)
	{
		throw;}
}

void Service::srvStergereOferta(const string& destinatie)
{

	Oferta of("", destinatie, "", 0);

	if (this->repo.repoExistentaOferta(of) == false)
		throw RepoError("Nu exista o Oferta cu aceasta destinatie, deci nu se poate face stergerea!", 6);

	this->repo.repoStergereOferta(of);
}

Repo Service::srvGetRepo() const
{
	return this->repo;
}

const int Service::srvCautareOferta(const string& destinatie)
{
	Oferta o("", destinatie, "", 0);

	const int index = this->repo.getIndexFromOferta(o);

	if (index == -1)
		throw RepoError("Aceasta Oferta NU exista!", 7);

	else
		return index;}

const DynamicArray<Oferta> Service::srvFiltrareDupaDestinatie(const string& substr)
{
	return this->repo.repoFiltrareDupaDestinatie(substr);
}

const DynamicArray<Oferta> Service::srvFiltrareDupaPret(const int pret)
{
	return this->repo.repoFiltrareDupaPret(pret);
}

void Service::srvSortareGenerica(const string& ord, const string& camp)
{
	try
	{	
		this->validator.validareCampSortare(camp);
		this->validator.validareOrdineSortare(ord);

		bool cresc = true;
		if (ord == "cresc")
			cresc = true;

		else
			cresc = false;

		if (camp != "tip + pret")
			this->repo.repoSortareGenerica(cresc, camp);

		else
			this->repo.repoSortareMultipla(cresc);
	}

	catch (...)
	{
		throw;}
}