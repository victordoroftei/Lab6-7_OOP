#include "test.h"
#include <iostream>

using std::cout;

void testDomain()
{
	Oferta o("Tur", "Grecia", "Mare", 100);

	assert(o.getDenumire() == "Tur");
	assert(o.getDestinatie() == "Grecia");
	assert(o.getTip() == "Mare");
	assert(o.getPret() == 100);

	o.setDenumire("Vacanta de vara");
	o.setDestinatie("Turcia");
	o.setTip("Mare cu soare");
	o.setPret(999);

	assert(o.getDenumire() == "Vacanta de vara");
	assert(o.getDestinatie() == "Turcia");
	assert(o.getTip() == "Mare cu soare");
	assert(o.getPret() == 999);

	Oferta o2("Antalya", "Turcia", "Mare cu soare", 999);
	assert(o == o2);
}

void testDynamicArray()
{
	DynamicArray<Oferta> v;

	v.push_back(Oferta("Munte", "Elvetia", "Hotel", 1000));
	assert(v.size() == 1);
	assert(v.at(0) == Oferta("Munte", "Elvetia", "Hotel", 1000));

	DynamicArray<Oferta> v2 = v;
	assert(v2.size() == 1);
	assert(v2.at(0) == Oferta("Munte", "Elvetia", "Hotel", 1000));
	assert(v == v2);

	v = v;

	v.push_back(Oferta("Mare", "Caraibe", "Motel", 2900));
	assert(!(v == v2));

	v2.push_back(Oferta("Mare", "Zimbabwe", "Resort", 999));
	assert(!(v == v2));

	vector<Oferta> vec;
	vec.push_back(Oferta("Munte", "Elvetia", "Hotel", 1000));
	vec.push_back(Oferta("Mare", "Caraibe", "Motel", 2900));

	int i = 0;
	for (auto of : v)
	{
		assert(of == vec.at(i));
		i++;
	}
}

void testRepo()
{
	Repo r;
	Oferta o1("Munte", "Austria", "Resort", 305), o2("Mare", "Bahamas", "Xll-inclusive", 700);

	r.repoAdaugareOferta(o1);

	DynamicArray<Oferta> vec = r.getContinut();

	assert(vec.at(0) == o1);

	DynamicArray<Oferta> v, vec2;
	v.push_back(o1);
	v.push_back(o2);
	r.setContinut(v);

	assert(r.getContinut().at(0) == Oferta ("Munte", "Austria", "Resort", 305));
	assert(r.getContinut().at(1) == Oferta("Mare", "Bahamas", "Xll-inclusive", 700));

	Oferta o3("Litoral", "Mamaia", "Hotel", 50), o4("Mare", "Austria", "Camping cu rulota", 120);
	assert(r.repoExistentaOferta(o3) == false);
	assert(r.repoExistentaOferta(o4) == true);

	vec = r.repoFiltrareDupaDestinatie("ama");
	assert(vec.at(0) == o2);

	vec = r.repoFiltrareDupaDestinatie("a");
	assert(vec.at(0) == o1);
	assert(vec.at(1) == o2);

	vec = r.repoFiltrareDupaDestinatie("ej");
	assert(vec.size() == 0);

	vec = r.repoFiltrareDupaPret(400);
	assert(vec.at(0) == o1);

	vec = r.repoFiltrareDupaPret(1000);
	assert(vec.at(0) == o1);
	assert(vec.at(1) == o2);

	vec = r.repoFiltrareDupaPret(100);
	assert(vec.size() == 0);

	r.repoModificareOferta(o1, "Mare", "Austria", "Camping cu rulota", 120);
	vec2 = r.getContinut();
	assert(vec2.at(0) == o4);

	vec2 = r.getContinutRef();
	assert(vec2.at(0) == o4);

	r.repoSortareGenerica(false, "destinatie");
	vec2 = r.getContinut();
	assert(vec2.at(0) == o2);
	assert(vec2.at(1) == o4);

	r.repoAdaugareOferta(Oferta("Munte", "Italia", "Camping cu rulota", 50));
	r.repoSortareMultipla(true);
	vec2 = r.getContinut();
	assert(vec2.at(0) == Oferta("Munte", "Italia", "Camping cu rulota", 50));
	assert(vec2.at(1) == o4);
	assert(vec2.at(2) == o2);

	assert(r.getIndexFromOferta(o4) == 1);

	r.repoStergereOferta(Oferta("Munte", "Italia", "Camping cu rulota", 50));
	r.repoStergereOferta(o2);
	assert(r.getContinut().size() == 1);

	Repo r2;
	r2.repoAdaugareOferta(o2);
	assert(r2.getContinut().size() == 1);

	assert(!(r == r2));
}

void testService()
{
	Repo r, r2;
	Validator v;
	Service s{ r, v };

	Oferta o("Litoral", "Mamaia", "Hotel", 65);

	s.srvAdaugareOferta("Litoral", "Mamaia", "Hotel", 65);
	r2.repoAdaugareOferta(o);
	r = s.srvGetRepo();
	assert(r2 == r);

	DynamicArray<Oferta> vec, vec2;

	vec = s.srvFiltrareDupaDestinatie("ama");
	vec2 = r.getContinut();
	assert(vec.at(0) == vec2.at(0));

	vec = s.srvFiltrareDupaPret(100);
	vec2 = r.getContinut();
	assert(vec.at(0) == vec2.at(0));

	try
	{
		s.srvAdaugareOferta("Plaja", "Mamaia", "Motel", 50);}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 0);
	}

	try
	{
		s.srvAdaugareOferta("", "Finlanda", "Hotel", 300);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 2);
	}

	try
	{
		s.srvAdaugareOferta("Munte", "", "Hotel", 300);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 3);
	}

	try
	{
		s.srvAdaugareOferta("Munte", "Finlanda", "", 300);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 4);
	}

	try
	{
		s.srvAdaugareOferta("Munte", "Finlanda", "Hotel", -10);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 5);
	}

	try
	{
		s.srvModificareOferta("Munte", "Finlanda", "Estonia", "Hotel", 300);}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 1);
	}

	try
	{
		s.srvStergereOferta("Finlanda");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 6);
	}

	try
	{
		s.srvCautareOferta("Finlanda");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 7);
	}

	assert(s.srvCautareOferta("Mamaia") == 0);

	s.srvModificareOferta("Mamaia", "Plaja", "Mexic", "All-inclusive", 560);
	r2.repoModificareOferta(o, "Plaja", "Mexic", "All-inclusive", 560);
	r = s.srvGetRepo();
	assert(r == r2);

	Repo r3;
	s.srvAdaugareOferta("Munte", "Austria", "Pensiune", 300);
	s.srvSortareGenerica("cresc", "denumire");
	r3.repoAdaugareOferta(Oferta("Plaja", "Mexic", "All-inclusive", 560));
	r3.repoAdaugareOferta(Oferta("Munte", "Austria", "Pensiune", 300));
	r3.repoAdaugareOferta(Oferta("Litoral", "Mamaia", "Zotel", 65));
	r = s.srvGetRepo();
	assert(r == r3);

	try
	{
		s.srvSortareGenerica("abc", "destinatie");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 9);
	}

	try
	{
		s.srvSortareGenerica("descresc", "abc");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 8);
	}

	s.srvSortareGenerica("descresc", "tip + pret");
	r = s.srvGetRepo();
	assert(r == r3);

	Oferta o2("Plaja", "Mexic", "All-inclusive", 560);

	s.srvStergereOferta("Mexic");
	r3.repoStergereOferta(o2);
	r = s.srvGetRepo();
	assert(r == r3);
}

void testUtils()
{
	assert(cmpString("Ala", "Bala", true) == 1);
	assert(cmpString("Bala", "Ala", true) == -1);
	assert(cmpString("Ala", "Ala", true) == 0);

	assert(cmpString("Ala", "Bala", false) == -1);
	assert(cmpString("Bala", "Ala", false) == 1);
	assert(cmpString("Ala", "Ala", false) == 0);

	assert(cmpInt(10, 100, true) == 1);
	assert(cmpInt(100, 10, true) == -1);
	assert(cmpInt(10, 10, true) == 0);

	assert(cmpInt(10, 100, false) == -1);
	assert(cmpInt(100, 10, false) == 1);
	assert(cmpInt(10, 10, false) == 0);

	Oferta o1("Mare", "Mamaia", "Motel", 60), o2("Munte", "Mecklenburg", "Motel", 660);
	assert(comparatorGeneric(o1, o2, "denumire", true) == 1);
	assert(comparatorGeneric(o1, o2, "destinatie", false) == -1);
	assert(comparatorGeneric(o1, o2, "tip", true) == 0);
	assert(comparatorGeneric(o1, o2, "pret", false) == -1);

	DomainError de("Eroare Mare!", 404);
	RepoError re("Eroare Mica...", 501);

	assert(de.getCode() == 404);
	assert(re.getCode() == 501);

	assert(de.getMessage() == "Eroare Mare!");
	assert(re.getMessage() == "Eroare Mica...");
}

void testValidator()
{
	Validator v;

	try
	{
		v.validareCampSortare("anc");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 8);
	}

	try
	{
		v.validareOrdineSortare("abc");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 9);
	}

	try
	{
		v.validareDateOferta("", "Polonia", "Hotel", 500);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 2);
	}

	try
	{
		v.validareDateOferta("Tara", "", "Hotel", 500);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 3);
	}

	try
	{
		v.validareDateOferta("Tara", "Polonia", "", 500);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 4);
	}

	try
	{
		v.validareDateOferta("Tara", "Polonia", "Hotel", -500);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 5);
	}
}

void runAllTests()
{
	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functie ce ruleaza toate testele.
	*/

	testDomain();
	testDynamicArray();
	testRepo();
	testValidator();
	testService();
	testUtils();
}