// tail.c
// Riešenie IJC-DU2, príklad 1), 12.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Program na vypis poslednych n riadkov suboru

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

// Definicie defaultneho poctu riadkov na vypis, limitu dlzky riadku a minimalne cisla zadaneho v argumente
#define DEFAULT_LINE_COUNT 10
#define LINE_LENGTH_LIMIT 511
#define MIN_NUMBER_IN_ARG 0

/**
 * @brief Funkcia na vypis chyboveho hlasenia na stderr a ukoncenie suboru.
 * 
 * @param fmt formatovaci retazec
 * @param ... premenne pre formatovaci retazec
 */
void error_exit(const char *fmt, ...)
{
    va_list variables;
    va_start(variables, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, variables);
    fprintf(stderr, "\n");
    va_end(variables);
    exit(1);
}

/**
 * @brief Funkcia na zistenie cisla v zadanom argumente
 * 
 * @param num_start pointer na znak, ktorym cislo zacina
 * @return precitane cislo 
 */
unsigned long get_number_from_arg(char *num_start)
{
    char *test_ptr = NULL;
    long tmp = strtol(num_start, &test_ptr, 10);
    if (*test_ptr != 0 || tmp < MIN_NUMBER_IN_ARG)
    {
        error_exit("Nespravne spustanie.");
    }
    return (unsigned long)tmp;
}

/**
 * @brief Funkcia na otvorenie suboru a pripadne vypisanie chyby
 * 
 * @param file_name nazov suboru
 * @return pointer na otovreny subor.
 */
FILE *open_src_file(char *file_name)
{
    FILE *tmp = fopen(file_name, "r");
    if (tmp == NULL)
    {
        error_exit("Chyba pri otvarani subru %s.", file_name);
    }
    return tmp;
}

/**
 * @brief Funkcia na uvolnenie pamate alokovanej pre buffer retazcov
 * 
 * @param last_lines Pointer na pole pointerov na stringy, v ktorych su ulozene posledne precitane riadky
 * @param line_count Velkost pola last_lines
 */
void free_last_lines(char **last_lines, unsigned long line_count)
{
    if (last_lines == NULL)
        return;

    // Loop ktory uvolni pamat alokovanu pre vsetky stringy z pola last_lines
    for (unsigned long i = 0; i < line_count; i++)
    {
        if (last_lines[i] != NULL)
        {
            free(last_lines[i]);
        }
    }
    // uvolnenie pamate pre pola pointer
    free(last_lines);
    return;
}

/**
 * @brief Funkcia, ktora alokuje pamat pre buffer pouzity na ukladanie poslednych riadkov
 * 
 * @param line_count pocet riadkov, pre ktore sa ma pamat alokovat
 * @return pointer na vytvorené pole pointerov
 */
char **alloc_last_lines(unsigned long line_count)
{
    // Alokovanie pola pointerov
    char **last_lines = calloc(line_count, sizeof(char *));
    if (last_lines == NULL)
    {
        return NULL;
    }
    // Alokovanie pamate pre jednotlive riadky
    for (unsigned long i = 0; i < line_count; i++)
    {
        last_lines[i] = calloc(LINE_LENGTH_LIMIT + 1, sizeof(char));
        if (last_lines[i] == NULL)
        {
            free_last_lines(last_lines, line_count);
            return NULL;
        }
    }
    return last_lines;
}

/**
 * @brief Funkcia ktora prida riadok do buffer a posunie ostatne riadky
 * 
 * @param last_lines pointer na buffer pouzivany na ukladanie poslednych riadkov
 * @param line_count pocet riadkov, ktore ukladame
 * @param new_line pointer na string, ktoreho text sa ma pridat do noveho riadku
 */
void add_last_line(char **last_lines, unsigned long line_count, char *new_line)
{
    if (line_count < 1)
        return;

    // Loop ktory posunie kazdy riadok o index o jedna nizsi
    char *tmp = last_lines[0];
    for (unsigned long i = 0; i < line_count - 1; i++)
    {
        last_lines[i] = last_lines[i + 1];
    }
    // Presunutie pointera ktory bol povodne nulty na vrch
    last_lines[line_count - 1] = tmp;
    // Prepisanie horneho stringu na new_line
    strcpy(last_lines[line_count - 1], new_line);
}

int main(int argc, char **argv)
{
    // Kontrola spravneho formatu argumentov
    if (argc > 4 || (argc == 3 && strcmp(argv[1], "-n") != 0) || (argc == 4 && (strcmp(argv[1], "-n") != 0 && strcmp(argv[2], "-n") != 0)))
    {
        error_exit("Nespravne spustanie.");
    }

    // Premenne pre program, su nastavene switchom nizsie
    FILE *source_file;
    // Urcuje mod, v ktorom ma program fungovat ('./tail -n +x' alebo './tail -n x')
    bool has_plus = false;
    unsigned long first_line = 0;
    unsigned long line_count = 0;

    // Switch, ktory vykona nastavenie podla poctu argumentov
    switch (argc)
    {
    case 1:
        source_file = stdin;
        line_count = DEFAULT_LINE_COUNT;
        break;
    case 2:
        source_file = open_src_file(argv[1]);
        line_count = DEFAULT_LINE_COUNT;
        break;
    case 3:
        if (argv[2][0] == '+')
        {
            first_line = get_number_from_arg(&argv[2][1]);
            has_plus = true;
        }
        else
        {
            line_count = get_number_from_arg(argv[2]);
        }
        source_file = stdin;
        break;
        ;
    case 4:
        if (strcmp(argv[1], "-n") == 0)
        {
            if (argv[2][0] == '+')
            {
                first_line = get_number_from_arg(&argv[2][1]);
                has_plus = true;
            }
            else
            {
                line_count = get_number_from_arg(argv[2]);
            }
            source_file = open_src_file(argv[3]);
        }
        else
        {
            if (argv[3][0] == '+')
            {
                first_line = get_number_from_arg(&argv[3][1]);
                has_plus = true;
            }
            else
            {
                line_count = get_number_from_arg(argv[3]);
            }
            source_file = open_src_file(argv[1]);
        }
        break;
    default:
        error_exit("Nespravne spustanie.");
    }

    // Bool zaistujuci, ze error o prekroceni dlzky riadku bude vypisany len raz
    bool printed_error = false;

    if (has_plus)
    {
        /* 
        Mod '-n +x'. Vypisuje vsetky riadky od first_line
        */

        // Alokovanie bufferu pre riadok.
        char *buffer = calloc(LINE_LENGTH_LIMIT + 1, sizeof(char));
        if (buffer == NULL)
        {
            fprintf(stderr, "Chyba pri alokacii pamate.\n");
            goto ON_ERROR;
        }

        // While loop ktory postupne spracuva riadky
        unsigned long counter = 1;
        while (fgets(buffer, LINE_LENGTH_LIMIT + 1, source_file) != NULL)
        {
            // Kontrola, ci dany riadok ma byt vypisany a pripadny vypis
            if (counter++ >= first_line)
            {
                printf("%s", buffer);
            }
            // Ak nebol nacitany cely riadok
            if (buffer[strlen(buffer) - 1] != '\n')
            {
                // Ak bol riadok vypisany, prida ukoncenie riadku
                if (counter - 1 >= first_line)
                {
                    printf("\n");
                }
                // Ak nebol vypisany error, vypise ho a prepne printed_error, aby uz znovy vypisany nebol
                if (!printed_error)
                {
                    fprintf(stderr, "Riadok bol dlhsi ako maximalna povolena dlzka %d.\n", LINE_LENGTH_LIMIT);
                    printed_error = true;
                }
                // Postupne nacitavanie zo suboru, kym neziskame riadok ukonceny koncovym znakom na preskocenie zbytku riadku
                while (buffer[strlen(buffer) - 1] != '\n')
                {
                    char *tmp = fgets(buffer, LINE_LENGTH_LIMIT + 1, source_file);
                    if (tmp == NULL)
                        break;
                }
            }
        }
        free(buffer);
    }
    else
    {
        /*
        Mod '-n x'. Vypisuje len urceny pocet posledných riadkov
        */

        // Alokovanie bufferu pre posledne riadky
        char **last_lines = alloc_last_lines(line_count);
        if (last_lines == NULL)
        {
            fprintf(stderr, "Chyba pri alokacii pamate.\n");
            goto ON_ERROR;
        }

        // Alokovanie bufferu na citanie
        char *buffer = calloc(LINE_LENGTH_LIMIT + 1, sizeof(char));
        if (buffer == NULL)
        {
            fprintf(stderr, "Chyba pri alokacii pamate.\n");
            free_last_lines(last_lines, line_count);
            goto ON_ERROR;
        }

        // Loop ktory postupne cita zo suboru
        unsigned long lines_read = 0;
        while (fgets(buffer, LINE_LENGTH_LIMIT + 1, source_file) != NULL)
        {
            // Prida riadok do bufferu pre posledne riadky
            add_last_line(last_lines, line_count, buffer);
            lines_read++;

            // Ak nacitany riadok nebol ukonceny koncovym znakom, znamena ze je dlhsi ako maximalna povolena dlzka
            if (buffer[strlen(buffer) - 1] != '\n')
            {
                // Ak este nebol vypisany error, vypise error a prepne printed_error na true, aby sa uz znova nevypisoval
                if (!printed_error)
                {
                    fprintf(stderr, "Riadok bol dlhsi ako maximalna povolena dlzka %d.\n", LINE_LENGTH_LIMIT);
                    printed_error = true;
                }
                // Postupne nacitavanie zo suboru, kym neziskame riadok ukonceny koncovym znakom na preskocenie zbytku riadku
                while (buffer[strlen(buffer) - 1] != '\n')
                {
                    char *tmp = fgets(buffer, LINE_LENGTH_LIMIT + 1, source_file);
                    if (tmp == NULL)
                        break;
                }
            }
        }

        /*
            Vypocet toho, kde ma zacat vypisovanie riadkov.
            Pouzite na osterenie toho, ak je zadany vyssi pocet riadkov ktory cheme vypisat ako pocet riadkov v subore.
        */
        unsigned long start = (lines_read < line_count ? line_count - lines_read : 0);

        // Loop na vypis riadkov
        for (unsigned long i = start; i < line_count; i++)
        {
            printf("%s", last_lines[i]);
            if (last_lines[i][strlen(last_lines[i]) - 1] != '\n')
            {
                printf("\n");
            }
        }
        free_last_lines(last_lines, line_count);
        free(buffer);
    }

    fclose(source_file);
    return 0;

    // Navestie pre jednoduchy error exit.
ON_ERROR:
    fclose(source_file);
    return 1;
}