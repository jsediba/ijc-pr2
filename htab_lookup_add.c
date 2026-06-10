// htab_lookup_add.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora vyhlada zaznam v hash tabulke, v pripade, ze zaznam neexistuje, vytvori novy
#include "htab.h"
#include "htab_priv.h"
#include "stdlib.h"

/**
 * @brief Funkcia, ktora vyhlada zaznam v hash tabulke, v pripade, ze zaznam neexistuje, vytvori novy
 * 
 * @param t pointer na hash tabulku
 * @param key kluc, urcujuci ktory zaznam hladame alebo vytvarame
 * @return pointer na htab_pair_t ktory obsahuje zaznam so zadanym klucom
 */
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    if (t == NULL || key == NULL)
    {
        return NULL;
    }
    // Zistenie, ci zaznam s hladanym klucom uz exituje a jeho pripadne vratenie.
    htab_pair_t *existingPair = htab_find(t, key);
    if (existingPair != NULL)
    {
        return existingPair;
    }
    // Vypocet hashu daneho klucu a alkovanie pamate pre zadany kluc
    size_t hash = htab_hash_function(key);
    char *newKey = malloc(strlen(key) + 1);
    if (newKey == NULL)
    {
        return NULL;
    }
    strcpy(newKey, key);

    // Alokovanie pamate pre novy zaznam a nastavenie zaznamu.
    htab_item_t *newItem = malloc(sizeof(htab_pair_t) + sizeof(htab_item_t *));
    if (newItem == NULL)
    {
        free(newKey);
        return NULL;
    }
    newItem->pair.key = newKey;
    newItem->pair.value = 0;
    newItem->next = t->arr[hash % t->arr_size];
    t->arr[hash % t->arr_size] = newItem;
    t->size++;
    return &newItem->pair;
}