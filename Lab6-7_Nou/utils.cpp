#include "utils.h"

const int cmpString(const string& str1, const string& str2, const bool cresc) 
{
	if (str1 == str2)
		return 0;

	if (str1 < str2)
	{
		if (cresc)
			return 1;

		else
			return -1;}

	else
	{
		if (cresc)
			return -1;

		else
			return 1;
	}
}

const int cmpInt(const int num1, const int num2, const bool cresc) 
{
	if (num1 == num2)
		return 0;

	else if (num1 < num2)
	{
		if (cresc)
			return 1;

		else
			return -1;}

	else
	{
		if (cresc)
			return -1;

		else
			return 1;
	}
}

const int comparatorGeneric(const Oferta& of1, const Oferta& of2, const string& camp, const bool cresc) 
{
	// Camp: 1 = denumire, 2 = destinatie, 3 = tip, 4 = pret

	if (camp == "denumire")
		return cmpString(of1.getDenumire(), of2.getDenumire(), cresc);

	else if (camp == "destinatie")
		return cmpString(of1.getDestinatie(), of2.getDestinatie(), cresc);

	else if (camp == "tip")
		return cmpString(of1.getTip(), of2.getTip(), cresc);

	else
		return cmpInt(of1.getPret(), of2.getPret(), cresc);
}

DomainError::DomainError(const string& message, int code)
{
	this->message = message;
	this->code = code;
}

string DomainError::getMessage() const 
{
	return this->message;
}

int DomainError::getCode() const 
{
	return this->code;
}

RepoError::RepoError(const string& message, int code)
{
	this->message = message;
	this->code = code;
}

string RepoError::getMessage() const 
{
	return this->message;
}

int RepoError::getCode() const 
{
	return this->code;
}
