// htab_free.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora uvolni pamat alokovanu pre hash tabulku
#include "htab.h"
#include "htab_priv.h"
#include <stdlib.h>

/**
 * @brief Funkcia, ktora uvolni pamate alokovanu pre hash tabulku
 * 
 * @param t pointer na hash tabulku
 */
void htab_free(htab_t *t)
{
    if (t == NULL)
    {
        return;
    }
    // Volanie funkcie htab_clear na vycistenie a uvolnenie pamate alokovanej pre vsetky zaznamy
    htab_clear(t);
    // Uvolnenie pamate alokovanej pre samotnu hash tabulku
    free(t);
    return;
}