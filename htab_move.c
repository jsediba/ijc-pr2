// htab_move.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora presunie zaznamy z hash tabulky do novej a vycisti povodnu hash tabulku.
#include "htab.h"
#include "htab_priv.h"
#include <stdlib.h>

/**
 * @brief Funkcia, ktora presunie zaznamy z hash tabulky do novej a vycisti povodnu hash tabulku.
 * 
 * @param n velkost pola pointerov pre novu hash tabulku
 * @param from odkaz na povodnu hash tabulku
 * @return pointer na novu hash tabulku
 */
htab_t *htab_move(size_t n, htab_t *from)
{
    // Inicializacia novej hash tabulky
    htab_t *new = htab_init(n);
    if (new == NULL)
    {
        return NULL;
    }

    // Loop ktory prechadza postupne cele pole pointerov povodnej tabulky
    for (size_t i = 0; i < from->arr_size; i++)
    {
        // Vnutorny loop ktory prechadza list zaznamov pre dany index pola pointerov hash tabulky
        htab_item_t *tmp = from->arr[i];
        while (tmp != NULL)
        {
            // Pridanie zaznamu zo starej hash tabukly do novej
            htab_pair_t *newPair = htab_lookup_add(new, tmp->pair.key);
            if (newPair == NULL)
            {
                htab_free(new);
                return NULL;
            }
            tmp=tmp->next;
        }
    }
    // Vycistenie povodnej hash tabulky
    htab_clear(from);
    return new;
}