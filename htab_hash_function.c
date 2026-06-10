// htab_hash_function.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul s definiciou funkcie, na vypocet hashu pre zadane pole znakov

#include "htab.h"
#include <stdint.h>

/**
 * @brief Funkcia na vypocet hashu pre zadane pole znakov
 *          Varianta sdbm z http://www.cse.yorku.ca/~oz/hash.html, na zaklade public-domain.
 * 
 * @param str pointer na zaciatok pola znakov, pre ktore chceme hash vypocitat
 * @return vypocitany hash
 */
size_t htab_hash_function(const char *str)
{
    if(str == NULL){
        return 0;
    }
    uint32_t h = 0; // musí mít 32 bitů
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}