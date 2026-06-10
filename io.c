// io.c
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Modul obsahujuci definiciu funkcie na citanie slov zo suboru
#include "io.h"

/**
 * @brief Funkcia, ktora precita slovo zo suboru. Ako slovo sa pocita subor znakov oddeleny isspace znakmi.
 *          Pri precitani slova s dlzkou vacsou ako max slovo oreze, a vypise error.
 * 
 * @param s pointer na alokovanu pamat, kam sa ma precitane slovo ulozit
 * @param max maximalna dlzka slova 
 * @param f subor, z ktoreho slovo citame
 * @return pocet znakov v slove, ktore sa ulozilo do s
 */
int read_word(char *s, int max, FILE *f)
{
    if (f == NULL || s == NULL)
    {
        fprintf(stderr, "Bol zadany neplatny pointer na buffer alebo subor.\n");
        return EOF;
    }
    // Osetrenie hranicnych stavov maximalnej dlzky
    else if (max < 1)
    {
        if (max == 0)
        {
            s[0] = '\0';
            return 0;
        }
        else
        {
            fprintf(stderr, "Bola zadana zaporna maximalna dlzka slova.\n");
            return EOF;
        }
    }

    // Static bool, zaistuje aby bol error dlzky slova vypisany len raz
    static bool printedError = false;


    // Preskocenie isspace znakov pred slovom a riesenie isspace znakov pred koncom suboru
    int c = 0;
    int counter = 0;

    c = fgetc(f);

    if (c == EOF)
    {
        return EOF;
    }
    else if (isspace(c))
    {
        while (isspace(c))
        {
            c = fgetc(f);
            if (c == EOF)
            {
                return EOF;
            }
        }
    }

    // Citanie znakov zo suboru a ukladanie do bufferu (len po max-1 pre osetrenie overflowu)
    do
    {
        if (counter < max - 1)
        {
            s[counter] = c;
        }
        counter++;
    } while ((c = fgetc(f)) != EOF && !isspace(c));

    // Ukoncenie slova nulovym znakom a navrat poctu precitanych znakov v pripade, ze slovo malo menej ako max znakov
    if (counter < max)
    {
        s[counter] = '\0';
        return counter;
    }
    // Ukoncenie slova nulovym znakom a pripadne vypisanie erroru v pripade, ze slovo malo viac ako max znakov
    else
    {
        if (!printedError)
        {
            fprintf(stderr, "Naslo sa slovo dlhsie ako %d znakov, taketo slova su orezane.\n", max - 1);
            printedError = true;
        }
        s[max - 1] = '\0';
        return max - 1;
    }
}