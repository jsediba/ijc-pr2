// htab_size.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, ktora vrati pocet zaznamov v hash tabulke
#include "htab.h"
#include "htab_priv.h"

/**
 * @brief Funkcia, ktora vrati pocet zaznamov v hash tabulke
 * 
 * @param t pointer na hash tabulku
 * @return pocet zaznamov v hash tabulke
 */
size_t htab_size(const htab_t *t)
{
    if(t==NULL){
        return 0;
    }
    return t->size;
}