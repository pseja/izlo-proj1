#include <stddef.h>
#include "cnf.h"

//
// LOGIN: xpsejal00
//

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 1)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
// Pole streets ma velikost num_of_streets a obsahuje vsechny existujuci ulice
//    - pro 0 <= i < num_of_streets predstavuje streets[i] jednu existujici
//      ulici od krizovatky streets[i].crossroad_from ke krizovatce streets[i].crossroad_to
void at_least_one_valid_street_for_each_step(CNF *formula, unsigned num_of_crossroads, unsigned num_of_streets, const Street *streets)
{
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    assert(streets != NULL);

    for (unsigned i = 0; i < num_of_streets; i++)
    {
        Clause *new_clause = create_new_clause(formula);

        // Přidáme literály pro všechny ulice
        for (unsigned j = 0; j < num_of_streets; j++)
        {
            add_literal_to_clause(new_clause, true, i, streets[j].crossroad_from, streets[j].crossroad_to);
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 2)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void at_most_one_street_for_each_step(CNF *formula, unsigned num_of_crossroads, unsigned num_of_streets)
{
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    for (int i = 0; i < num_of_streets; i++)
    {
        // První ulice
        for (int z = 0; z < num_of_crossroads; z++)
        {
            for (int k = 0; k < num_of_crossroads; k++)
            {
                // Druhá ulice
                for (int z2 = 0; z2 < num_of_crossroads; z2++)
                {
                    for (int k2 = 0; k2 < num_of_crossroads; k2++)
                    {
                        // Pokud jsou ulice různé, tak vytvoříme klauzuli a přidáme do ní literály
                        if ((k != k2 || z != z2) && (z != k || z2 != k2))
                        {
                            Clause *new_clause = create_new_clause(formula);

                            add_literal_to_clause(new_clause, false, i, z, k);
                            add_literal_to_clause(new_clause, false, i, z2, k2);
                        }
                    }
                }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 3)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_connected(CNF *formula, unsigned num_of_crossroads, unsigned num_of_streets)
{
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    for (int i = 0; i < num_of_streets - 1; i++)
    {
        // První ulice
        for (int z = 0; z < num_of_crossroads; z++)
        {
            for (int k = 0; k < num_of_crossroads; k++)
            {
                // Druhá ulice
                for (int z2 = 0; z2 < num_of_crossroads; z2++)
                {
                    for (int k2 = 0; k2 < num_of_crossroads; k2++)
                    {
                        // Pokud konec první ulice není stejný jako začátek druhé ulice,
                        // tak vytvoříme klauzuli a přidáme do ní literály
                        if (k != z2)
                        {
                            Clause *new_clause = create_new_clause(formula);

                            add_literal_to_clause(new_clause, false, i, z, k);
                            add_literal_to_clause(new_clause, false, i + 1, z2, k2);
                        }
                    }
                }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 4)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_do_not_repeat(CNF *formula, unsigned num_of_crossroads, unsigned num_of_streets)
{
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    for (unsigned i = 0; i < num_of_streets; ++i)
    {
        // pro kazdy krok i
        for (unsigned j = 0; j < num_of_streets; ++j)
        {
            if (i != j)
            {
                // pro kazdy jiny krok j
                for (unsigned z = 0; z < num_of_crossroads; ++z)
                {
                    for (unsigned k = 0; k < num_of_crossroads; ++k)
                    {
                        // pro kazdu dvojici krizovatek (z, k)
                        Clause *cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, z, k);
                        add_literal_to_clause(cl, false, j, z, k);
                    }
                }
            }
        }
    }
}
