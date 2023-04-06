#pragma once

#include <stdio.h>

#define LUNG_MAX_TIP 3

int verif_load(char linie[], const char comanda[]);

void eliberare_fis_existent(img_t *img, img_b_t *img_b, char op[]
, char num_f[], int exis, int bin, FILE *imag, select_t *sel, select_b_t *s_b);

void load_ascii(img_t *img, select_t *select, FILE *imag, int *bin);

void load_bin(img_b_t *img_b, select_b_t *select_b, FILE *imag, int *bin
, img_t *img);
