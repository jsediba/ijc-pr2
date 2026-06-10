// htab_priv.h
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Privatny hlavickovy subor obsahujuci definiciu datovych typov pre hashovaciu tabulku a zaznam v hashovacej tabulke.

#ifndef HTAB_PRIV_H
#define HTAB_PRIV_H
#include "htab.h"

typedef struct htab_item
{
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

struct htab
{
    size_t size;
    size_t arr_size;
    htab_item_t *arr[];
};

#endif