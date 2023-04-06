#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "generale_f.h"

#define EQUALIZE "EQUALIZE"
#define P2_TIP "P2"
#define P3_TIP "P3"
#define P5_TIP "P5"
#define P6_TIP "P6"
#define MAX_VALUE 256

void egalizare(img_t *img)
{
	int arie = img->lin * img->col;

	// Calculez frecventa elementelor din matrice
	int frecv[MAX_VALUE] = {0};
	for (int i = 0; i < img->lin; i++)
		for (int j = 0; j < img->col; j++)
			frecv[img->mat[i][j]]++;

	int val_noua[MAX_VALUE] = {0};
	int sum = 0;

	// Aplic formula de egalizare, salvand in vectorul val_noua,
	// noile valori
	for (int i = 0; i < 256; i++) {
		while (frecv[i] == 0) {
			i++;
			if (i > 255)
				break;
		}
		sum += frecv[i];

		val_noua[i] = (round((((double)sum) * 255) / arie));
		clamp(&val_noua[i]);
	}

	// Modific pixelii initiali cu cei modificati dupa egalizare.
	for (int i = 0; i < img->lin; i++)
		for (int j = 0; j < img->col; j++)
			img->mat[i][j] = val_noua[img->mat[i][j]];

	printf("Equalize done\n");
}

void egalizare_bin(img_b_t *img_b)
{
	int arie = img_b->lin * img_b->col;

	int frecv[MAX_VALUE] = {0};

	for (int i = 0; i < img_b->lin; i++)
		for (int j = 0; j < img_b->col; j++)
			frecv[(int)img_b->mat[i][j]]++;

	int val_noua[MAX_VALUE] = {0};
	int sum = 0;

	for (int i = 0; i < MAX_VALUE; i++) {
		while (frecv[i] == 0) {
			i++;
			if (i > MAX_VALUE)
				break;
		}
		sum += frecv[i];

		val_noua[i] = (round((((double)sum) * MAX_VALUE) / arie));
		clamp(&val_noua[i]);
	}

	for (int i = 0; i < img_b->lin; i++)
		for (int j = 0; j < img_b->col; j++)
			img_b->mat[i][j] = (unsigned char)val_noua[img_b->mat[i][j]];

	printf("Equalize done\n");
}

void egalizare_cmd(img_t *img, img_b_t *img_b, char op[], int bin, int exis)
{
	if (!exis) {
		printf("No image loaded\n");
	} else {
		if (!verif_op_un_cuv(op, EQUALIZE)) {
			printf("Invalid command\n");
		} else {
			if (!bin) {
				if (strcmp(img->tip, P2_TIP))
					printf("Black and white image needed\n");
				else
					egalizare(img);
			} else {
				if (strcmp(img_b->tip, P5_TIP))
					printf("Black and white image needed\n");
				else
					egalizare_bin(img_b);
			}
		}
	}
}
