#include <iostream>
#include <crtdbg.h>

#include "test.h"
#include "UI.h"

/*
    6 Agenție de turism
    Creați o aplicație care permite:
        · gestiunea unei liste de oferte turistice. Oferta: denumire, destinatie, tip, pret
        · adaugare, stergere, modificare si afisare oferte turistice
        · cautare oferta
        · filtrare oferte turistice dupa: destinație, pret
        · sortare oferte dupa: denumire, destinatie, tip + pret
*/

int main()
{

    {
        runAllTests();
        Validator v;
        Repo r;
        Service s{ r, v };
        Console c{ s, r, v };

        c.run();
    }
    
    _CrtDumpMemoryLeaks();
    return 0;
}