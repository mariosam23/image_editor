#pragma once

#include <stdio.h>

#define LUNG_MAX_TIP 3

int verif_histogram(char linie[], const char comanda[]);

int putere_2(int nr);

void afisare_histograma(int intervale, int sum[], int frecv_max, int stele);

void calcul_frecv_ascii(int frecv[], int *frecv_max, int sum[], int intervale
, img_t *img, int *lun_inter);

void calcul_frecv_bin(int frecv[], int *frecv_max, int sum[], int intervale
, img_b_t *img_b, int *lun_inter);

void histogram_cmd(img_t *img, img_b_t *img_b, int bin, char op[]);

