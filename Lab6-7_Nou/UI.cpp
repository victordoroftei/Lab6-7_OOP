#include <iostream>

#include "UI.h"

using namespace std;

void Console::afisareRepo()
{
	int k = 1;
	DynamicArray<Oferta> continut = repo.getContinut();

	if (continut.size() == 0)
	{
		cout << "Lista de oferte este vida!\n";

		return;
	}

	cout << "Lista de oferte este:\n";

	int i;
	for (i = 0; i <= continut.size() - 1; i++)
	{
		cout << k << ": Denumire: " << continut.at(i).getDenumire() << ", Destinatie: " << continut.at(i).getDestinatie();
		cout << ", Tip: " << continut.at(i).getTip() << ", Pret: " << continut.at(i).getPret() << '\n';
		
		k++;
	}
}

void Console::afisareOfertaDupaIndex(const int index)
{
	const DynamicArray<Oferta>& v = this->repo.getContinutRef();

	cout << index + 1 << ": Denumire: " << v.at(index).getDenumire() << ", Destinatie: " << v.at(index).getDestinatie();
	cout << ", Tip: " << v.at(index).getTip() << ", Pret: " << v.at(index).getPret() << '\n';
}

void Console::afisareVectorOferte(const DynamicArray<Oferta>& vec)
{
	if (vec.size() == 0)
	{
		cout << "\nNu exista nicio Oferta cu filtrul dorit!\n";
		return;
	}

	int k = 0;
	cout << '\n';

	int i;
	for (i = 0; i <= vec.size() - 1; i++)
	{
		cout << k + 1 << ": Denumire: " << vec.at(i).getDenumire() << ", Destinatie: " << vec.at(i).getDestinatie();
		cout << ", Tip: " << vec.at(i).getTip() << ", Pret: " << vec.at(i).getPret() << '\n';

		k++;
	}
}

void Console::afisareMeniu()
{
	cout << "=============== AGENTIE DE TURISM ===============";
	cout << "\n1) Adaugare oferta.";
	cout << "\n2) Modificare oferta.";
	cout << "\n3) Stergere oferta.";
	cout << "\n4) Afisare lista de oferte.";
	cout << "\n5) Cautare oferta.";
	cout << "\n6) Filtrare oferte dupa destinatie.";
	cout << "\n7) Filtrare oferte dupa pret.";
	cout << "\n8) Sortarea listei de oferte.";

	cout << "\n0) Inchiderea aplicatiei.";
}

void Console::run()
{
	int comanda = -1;
	while (true)
	{
		comanda = -1;

		afisareMeniu();
		cout << "\n\nIntroduceti comanda dorita: ";
		cin >> comanda;


		if (comanda == 1)
		{
			string denumire, destinatie, tip;
			int pret;

			cout << "\nIntroduceti denumirea ofertei pe care doriti sa o adaugati: ";
			cin.get();
			getline(cin, denumire);

			cout << "\nIntroduceti destinatia ofertei pe care doriti sa o adaugati: ";
			getline(cin, destinatie);

			cout << "\nIntroduceti tipul ofertei pe care doriti sa o adaugati: ";
			getline(cin, tip);

			cout << "\nIntroduceti pretul ofertei pe care doriti sa o adaugati: ";
			cin >> pret;

			try
			{
				this->srv.srvAdaugareOferta(denumire, destinatie, tip, pret);

				cout << "Oferta a fost adaugata!\n";
				
				this->afisareRepo();
			}
			
			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}

			catch (...)
			{
				cout << "Iaca pozna";
			}
		}

		else if (comanda == 2)
		{
			string destinatieOld, denumire, destinatie, tip;
			int pret = 0;

			cout << "\nIntroduceti destinatia ofertei pe care doriti sa o modificati: ";

			cin.get();
			getline(cin, destinatieOld);

			cout << "\nIntroduceti noua denumire: ";
			getline(cin, denumire);

			cout << "\nIntroduceti noua destinatie: ";
			getline(cin, destinatie);

			cout << "\nIntroduceti noul tip: ";
			getline(cin, tip);

			cout << "\nIntroduceti noul pret: ";
			cin >> pret;

			try
			{
				this->srv.srvModificareOferta(destinatieOld, denumire, destinatie, tip, pret);

				cout << "Oferta a fost modificata!\n";

				this->afisareRepo();
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		}

		else if (comanda == 3)
		{
			string destinatie;

			cout << "\nIntroduceti destinatia ofertei pe care doriti sa o stergeti: ";
			cin.get();
			getline(cin, destinatie);

			try
			{
				this->srv.srvStergereOferta(destinatie);

				cout << "Oferta a fost stearsa!\n";

				this->afisareRepo();
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		}

		else if (comanda == 4)
			this->afisareRepo();

		else if (comanda == 5)
		{
			string destinatie;

			cout << "\nIntroduceti destinatia ofertei pe care doriti sa o cautati: ";

			cin.get();
			getline(cin, destinatie);

			try
			{
				const int index = this->srv.srvCautareOferta(destinatie);

				cout << "Aceasta oferta exista!\n";
				this->afisareOfertaDupaIndex(index);
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		
		}

		else if (comanda == 6)
		{
			string substr;
			cout << "\nIntroduceti substring-ul dupa care doriti sa faceti filtrarea: ";

			cin.get();
			getline(cin, substr);

			this->afisareVectorOferte(this->srv.srvFiltrareDupaDestinatie(substr));
		}

		else if (comanda == 7)
		{
			int pret;
			cout << "\nIntroduceti pretul dupa care doriti sa faceti filtrarea: ";

			cin >> pret;

			this->afisareVectorOferte(this->srv.srvFiltrareDupaPret(pret));
		}

		else if (comanda == 8)
		{
			try
			{
				cout << "Introduceti campul dupa care doriti sa faceti sortarea (denumire / destinatie / tip + pret): ";
				string camp;

				cin.get();
				getline(cin, camp);

				cout << "Introduceti ordinea in care sa se faca sortarea (cresc / descresc): ";
				string cresc;

				getline(cin, cresc);

				this->srv.srvSortareGenerica(cresc, camp);
				this->afisareRepo();
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		}

		else
		{
			cout << "\nAplicatia se va inchide...\n";
			return;
		}
	}
}