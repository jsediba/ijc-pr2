// io.h
// Riešenie IJC-DU2, príklad 2), 19.4. 2020
// Autor: Jakub Šediba, FIT
// Preložené: gcc 9.3
// Hlavickovy subor obsahujuci deklaraciu funkcie na citanie slov zo suboru

#ifndef IO_H
#define IO_H

#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>

int read_word(char *s, int max, FILE *f);

#endif