// htab_clear.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora vymaze zaznam z hash tabulky
#include "htab.h"
#include "htab_priv.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Funkcia, ktora odstrani zaznam z hash tabulky
 * 
 * @param t pointer na hash tabulku
 * @param key kluc, urcujuci ktory zaznam ma byt odstraneny 
 * @return true ak hash tabulka zaznam obsahovala a bol odstraneny
 * @return false ak hash tabulka zaznam neobsahovala 
 */
bool htab_erase(htab_t *t, htab_key_t key)
{
    if (t == NULL || key == NULL)
    {
        return false;
    }

    // Vypocita hash kluca na vypocet indexu, v ktorom sa ma zaznam hladat 
    size_t hash = htab_hash_function(key);

    // Kontrola, ci dany index v hash tabulke nie je prazdny a ci sa hladany zaznamn nenachadza na zaciatku daneho indexu.
    htab_item_t *tmp = t->arr[hash % t->arr_size];
    if(tmp==NULL){
        return false;
    }
    if (strcmp(tmp->pair.key, key) == 0)
    {
        t->arr[hash % t->arr_size] = tmp->next;
        free((void *)tmp->pair.key);
        free(tmp);
        t->size--;
        return true;
    }
    // Loop ktory prechadza vsetky polozky na danom indexe, ak najde hladany zaznam, vymaze ho
    htab_item_t *last = tmp;
    tmp = tmp->next;
    while (tmp != NULL)
    {
        if (strcmp(tmp->pair.key, key) == 0)
        {
            last->next = tmp->next;
            free((void *)tmp->pair.key);
            free(tmp);
            t->size--;
            return true;
        }
        last = tmp;
        tmp = tmp->next;
    }
    return false;
}