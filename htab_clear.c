// htab_clear.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora vycisti hash tabulku

#include "htab.h"
#include "htab_priv.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Funkcia, ktora vycisti hash tabulku a uvolni pamat alokovanu pre kazdy zaznam
 * 
 * @param t pointer na hash tabulku
 */
void htab_clear(htab_t *t)
{
    if (t == NULL || t->size==0)
    {
        return;
    }
    // Loop ktory prechadza vsetky pointre v poli pointerov hash tabulky
    for (size_t i = 0; i < t->arr_size; i++)
    {
        // While loop, ktory vycisti vsetky polozky listu v danom indexe pola pointerov
        htab_item_t *tmp = t->arr[i];
        while (tmp != NULL)
        {
            htab_item_t *next = tmp->next;
            free((void *)tmp->pair.key);
            free(tmp);
            tmp = next;
        }
    }
    t->size = 0;
    return;
}