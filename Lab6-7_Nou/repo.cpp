#include "repo.h"

Repo::Repo() 
{
	this->continut = {};
}

const DynamicArray<Oferta>& Repo::getContinut() const 
{
	return this->continut;
}

bool Repo::operator ==(const Repo& other) const 
{
	bool found = false;
	int i = 0, j = 0;

	for (i = 0; i <= this->continut.size() - 1; i++)
	{
		found = false;

		for (j = 0; j <= other.continut.size() - 1; j++)
			if (this->continut.at(i) == other.continut.at(j))
				found = true;

		if (!found)
			return false;
	}

	return true;
}

void Repo::setContinut(const DynamicArray<Oferta>& newContinut) 
{
	this->continut = newContinut;
}

void Repo::repoAdaugareOferta(const Oferta& of) 
{
	this->continut.push_back(of);
}

const bool Repo::repoExistentaOferta(const Oferta& of)
{
	int i;

	for (i = 0; i <= this->continut.size() - 1; i++)
		if (this->continut.at(i) == of)
			return true;

	return false;
}

void Repo::repoStergereOferta(const Oferta& of)
{
	int i = 0;
	for (i = 0; i <= this->continut.size() - 1; i++)
		if (this->continut.at(i) == of)
		{
			this->continut.erase(i);
			return;
		}
}

void Repo::repoModificareOferta(const Oferta& ofOld, const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	int i = 0;
	for (i = 0; i <= this->continut.size() - 1; i++)
	{
		if (this->continut.at(i) == ofOld)
		{
			Oferta of = Oferta(denumire, destinatie, tip, pret);
			
			this->continut.modify(i, of);

			return;}}
}

const int Repo::getIndexFromOferta(const Oferta& of) 
{
	int poz = 0, i = 0;

	for (i = 0; i <= this->continut.size() - 1; i++)
	{
		if (this->continut.at(i) == of)
			return poz;

		poz++;
	}

	return -1;
}

DynamicArray<Oferta>& Repo::getContinutRef() 
{
	return this->continut;
}

DynamicArray<Oferta> Repo::repoFiltrareDupaDestinatie(const string& substr)
{
	DynamicArray<Oferta> vec;
	int i = 0;

	for (i = 0; i <= this->continut.size() - 1; i++)
	{
		if (this->continut.at(i).getDestinatie().find(substr) <= this->continut.at(i).getDestinatie().size() - 1)
			vec.push_back(this->continut.at(i));
	}

	return vec;
}

const DynamicArray<Oferta> Repo::repoFiltrareDupaPret(const int pret)
{
	DynamicArray<Oferta> vec;
	int i = 0;

	for (i = 0; i <= this->continut.size() - 1; i++)
		if (this->continut.at(i).getPret() <= pret)
			vec.push_back(this->continut.at(i));

	return vec;
}

void Repo::repoSortareGenerica(const bool cresc, const string camp)
{
	int i = 0, j = 0;
	for(i = 0; i <= this->continut.size() - 2; i++)
		for (j = i + 1; j <= this->continut.size() - 1; j++)
			if (comparatorGeneric(this->continut.at(i), this->continut.at(j), camp, cresc) != 1)
				swap(this->continut.at(i), this->continut.at(j));
}

void Repo::repoSortareMultipla(const bool cresc)
{
	int i = 0, j = 0;
	for (i = 0; i <= this->continut.size() - 2; i++)
		for (j = i + 1; j <= this->continut.size() - 1; j++)
		{
			if (comparatorGeneric(this->continut.at(i), this->continut.at(j), "tip", cresc) == -1)
				swap(this->continut.at(i), this->continut.at(j));
			
			else if (comparatorGeneric(this->continut.at(i), this->continut.at(j), "tip", cresc) == 0)
				if (comparatorGeneric(this->continut.at(i), this->continut.at(j), "pret", cresc) != 1)
					swap(this->continut.at(i), this->continut.at(j));
		}
}