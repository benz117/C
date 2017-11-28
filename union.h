#ifndef UNION_H
#define UNION_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

#define LIGNE_MAX 1024
int nb_champs(char* fichier);
FILE* ouverture_fichier(char* nom_fichier);
int comparer_nb_champs(int nb_param,char* fichier,...);
void copy_fic(FILE *fsrc, FILE *fdst);
void myunion(int nbr_fichier,char *fichier,...);

#endif