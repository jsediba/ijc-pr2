// htab_bucket_count.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie na zistenie velkosti pola pointerov v hash tabulke

#include "htab.h"
#include "htab_priv.h"

/**
 * @brief Funkcia na zistenie velkosti pola pointerov v hash tabulke
 * 
 * @param t pointer na hash tabulku
 * @return velkost pola pointerov v hash tabulke
 */
size_t htab_bucket_count(const htab_t *t)
{
    if(t==NULL){
        return 0;
    }
    return t->arr_size;
}