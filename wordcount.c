// tail.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Program na vypocet kolko krat sa kazde slovo nachadza v subore.
#include "htab.h"
#include "io.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
// Maximalna povolena dlzka slova
#define MAX_WORD_LEN 127
// Velkost hash tabulky. Zvolil som 500, pretoze po testovani s viacerymi textami z http://www.gutenberg.org/ mi to pri tejto velkosti dosahovalo najvacsiu rychlost.
#define HTAB_ARR_SIZE 500

/*
 * Test moznosti vymenenia htab_hash_function, pre pouzitie prelozit s -DHASHTEST
*/
#ifdef HASHTEST

/**
 * @brief Funkcia na vypocet hashu pre zadane pole znakov
 *          Varianta  z http://www.cse.yorku.ca/~oz/hash.html, na zaklade public-domain.
 * 
 * @param str pointer na zaciatok pola znakov, pre ktore chceme hash vypocitat
 * @return vypocitany hash
 */
size_t htab_hash_function(htab_key_t str)
{
    if (str == NULL)
    {
        return 0;
    }
    uint32_t hash = 5381;
    uint32_t c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

#endif


/**
 * @brief Funkcia na vypis zaznamov hash tabulky
 * 
 * @param data pointer na data zaznamu tabulky
 */
void print_htab(htab_pair_t *data)
{
    printf("%s\t%d\n", data->key, data->value);
}

int main(int argc, char **argv)
{
    // Osetrenie argumentov
    if (argc > 2)
    {
        fprintf(stderr, "Chybne parametre. Program sa spusta s jednym parametrom pre citanie zo suboru a bez parametrov pre citanie zo stdin.\n");
        return 1;
    }

    // Nastavenie source file
    FILE *srcFile;
    switch (argc)
    {
    case 1:
        srcFile = stdin;
        break;
    case 2:
        srcFile = fopen(argv[1], "r");
        if (srcFile == NULL)
        {
            fprintf(stderr, "Chyba pri otvarani suboru %s.\n", argv[1]);
            return 1;
        }
        break;
    default:
        fprintf(stderr, "Chyba pri spustani programu.\n");
        return 1;
    }

    // Alokovanie pamate pre buffer, do ktoreho budeme citat slova.
    char *buffer = calloc(MAX_WORD_LEN + 1, sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "Chyba pri alokacii pamate pre buffer.\n");
        goto CLOSE_FILE;
    }

    // Alokovanie hash tabulky
    htab_t *tab = htab_init(HTAB_ARR_SIZE);
    if (tab == NULL)
    {
        fprintf(stderr, "Chyba pri alkoacii pamate pre htab.\n");
        goto FREE_BUFFER;
    }

    // While loop ktory vzdy precita slovo a ulozi ho do bufferu
    int wordLen;
    while ((wordLen = read_word(buffer, MAX_WORD_LEN + 1, srcFile)) != EOF)
    {
        // Vlozenie slova z buffer do hash tabulky
        htab_pair_t *pair = htab_lookup_add(tab, buffer);
        if (pair == NULL)
        {
            fprintf(stderr, "Chyba pri pridavani zaznamu do htab.\n");
            goto FREE_TAB;
        }
        pair->value++;
    }

/*
 * Test htab_move, aktivne pri prelozeni s -DMOVETEST
*/
#ifdef MOVETEST
    htab_t *tab_old = tab;
    tab = htab_move(50, tab_old);
    htab_free(tab_old);
    if (tab == NULL)
    {
        goto FREE_TAB;
    }
#endif

    // Pouzitie htab_for_each s funkciou print_htab na vypis zaznamov.
    htab_for_each(tab, print_htab);

    fclose(srcFile);
    free(buffer);
    htab_free(tab);

    return 0;

    // Navestia pre jednoduchsie ukoncovanie programu.
FREE_TAB:
    htab_free(tab);
FREE_BUFFER:
    free(buffer);
CLOSE_FILE:
    fclose(srcFile);
    return 1;
}