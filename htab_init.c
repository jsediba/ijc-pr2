// htab_init.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora inicializuje hash tabulku.
#include "htab.h"
#include "htab_priv.h"
#include <stdlib.h>


/**
 * @brief Funkcia, ktora iniclizuje hash tabulku
 * 
 * @param n Velkost pola pointerov, ktore ma tabulka mat
 * @return Pointer na vytvorenu tabulku alebo NULL pri chybe alkoacie pamate
 */
htab_t *htab_init(size_t n)
{
    // Alokovanie pamate cez calloc, sposobi to, ze prvky pola pointerov budu automaticky inicializovane na NULL
    htab_t *newTable = calloc(1, 2 * sizeof(size_t) + n * sizeof(htab_item_t *));
    if (newTable == NULL)
    {
        return NULL;
    }
    newTable->size = 0;
    newTable->arr_size = n;
    return newTable;
}