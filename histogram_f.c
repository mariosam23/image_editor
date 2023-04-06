#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generale_f.h"

#define MAX_VALUE 256
#define P2_TIP "P2"
#define P5_TIP "P5"

int verif_histogram(char linie[], const char comanda[])
{
	if (!strstr(linie, comanda))
		return 0;

	int cnt_num = 0;

	for (int i = 0; i < (int)strlen(linie); i++) {
		int numar = 0;

		while (is_digit(linie[i]))
			i++, numar = 1;

		if (numar == 1)
			cnt_num++;
	}

	// Verific daca s-au gasit doua numere (parametrii histogramei).
	if (cnt_num == 2)
		return 1;

	return 0;
}

int putere_2(int nr)
{
	if (nr < 2)
		return 0;
	if (nr > 256)
		return 0;
	while (nr != 1) {
		if (nr % 2 == 1)
			return 0;
		nr /= 2;
	}
	return 1;
}

void afisare_histograma(int intervale, int sum[], int frecv_max, int stele)
{
	for (int i = 0; i < intervale; i++) {
		double nr_stele = (double)sum[i] / frecv_max * stele;

		printf("%d\t|\t", (int)nr_stele);

		for (int j = 0; j < (int)nr_stele; j++)
			printf("*");

		printf("\n");
	}
}

void calcul_frecv_ascii(int frecv[], int *frecv_max, int sum[], int intervale
, img_t *img, int *lun_inter)
{
	// Calculez frecventa elementelor din matrice.
	for (int i = 0; i < img->lin; i++)
		for (int j = 0; j < img->col; j++)
			frecv[img->mat[i][j]]++;

	// Calculez frecventa maxima parcurgand intervalele
	for (int i = 0; i < intervale; i++) {
		for (int j = i * (*lun_inter); j < (i + 1) * (*lun_inter); j++)
			sum[i] += frecv[j];

		if (sum[i] > *frecv_max)
			*frecv_max = sum[i];
	}
}

void calcul_frecv_bin(int frecv[], int *frecv_max, int sum[], int intervale
, img_b_t *img_b, int *lun_inter)
{
	for (int i = 0; i < img_b->lin; i++)
		for (int j = 0; j < img_b->col; j++)
			frecv[img_b->mat[i][j]]++;

	for (int i = 0; i < intervale; i++) {
		for (int j = i * (*lun_inter); j < (i + 1) * (*lun_inter); j++)
			sum[i] += frecv[j];
		if (sum[i] > *frecv_max)
			*frecv_max = sum[i];
	}
}

void histogram_cmd(img_t *img, img_b_t *img_b, int bin, char op[])
{
	int intervale, stele;

	int nr = sscanf(op, "%*[^0123456789]%d %d", &stele, &intervale);
	if (nr != 2) {
		fprintf(stderr, "Eroare la sscanf\n");
		exit(-1);
	}

	if (!putere_2(intervale)) {
		printf("Invalid set of parameters\n");
	} else {
		int frecv[MAX_VALUE] = {0};

		int frecv_max = 0, sum[MAX_VALUE] = {0};

		int lun_inter = MAX_VALUE / intervale;

		if (!bin) {
			if (strcmp(img->tip, P2_TIP)) {
				printf("Black and white image needed\n");
			} else {
				calcul_frecv_ascii(frecv, &frecv_max, sum, intervale, img
				, &lun_inter);

				afisare_histograma(intervale, sum, frecv_max, stele);
			}
		} else {
			if (strcmp(img_b->tip, P5_TIP)) {
				printf("Black and white image needed\n");
			} else {
				calcul_frecv_bin(frecv, &frecv_max, sum, intervale, img_b
				, &lun_inter);

				afisare_histograma(intervale, sum, frecv_max, stele);
			}
		}
	}
}
