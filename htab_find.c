// htab_find.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora vyhlada zaznam so zadanym klucom v hashovacej tabulke

#include "htab.h"
#include "htab_priv.h"

/**
 * @brief Funkcia, ktora vyhlada zaznam so zadanym klucom v hash tabulke
 * 
 * @param t pointer na hash tabulku
 * @param key kluc, urcujuci ktory zaznam hladame
 * @return pointer na htab_par_t s danym klucom alebo NULL ak hladany kluc v tabulke nenachadza
 */
htab_pair_t *htab_find(htab_t *t, htab_key_t key)
{
    if (t == NULL || key == NULL)
    {
        return NULL;
    }
    // Vypocet hash daneho kluca na zistenie na akom indexy pola by sa zaznam mal nachadzat
    size_t hash = htab_hash_function(key);
    // Loop ktory prechadza list itemov na najdenom indexe pola pointerov a ak sa zhoduju kluce, vracia pointer na pair s hladanym klucom
    htab_item_t *tmp = t->arr[hash % t->arr_size];
    while (tmp != NULL)
    {
        if (strcmp(tmp->pair.key, key) == 0)
        {
            return &tmp->pair;
        }
        tmp = tmp->next;
    }
    return NULL;
}