// htab_for_each.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora vykona funkciu f na kazdy zaznam v hash tabulke
#include "htab.h"
#include "htab_priv.h"

/**
 * @brief Funkcia, ktora vykona funkciu f nad kazdym zaznamom v hash tabulke 
 * 
 * @param t pointer na hash tabulku
 * @param f pointer na funkciu s jednym parametrom typu pointer na htab_pair_t, ktora sa ma vykonat pre kazdy zaznam
 */
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data))
{
    if(t == NULL){
        return;
    }
    // Loop ktory prechadza postupne cele pole pointerov hash tabulky
    for (size_t i = 0; i < t->arr_size; i++)
    {
        // Vnutorny loop, ktory prechadza cely list pre dany index v poli pointerov a vykonava nad kazdym zaznamom funkciu f.
        htab_item_t *tmp = t->arr[i];
        while (tmp != NULL)
        {
            f(&tmp->pair);
            tmp = tmp->next;
        }
    }
}
