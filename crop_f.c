#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generale_f.h"

#define CROP "CROP"
#define P2_TIP "P2"
#define P3_TIP "P3"
#define P5_TIP "P5"
#define P6_TIP "P6"
#define TOT 1
#define NU_TOT 0
#define ORIG 0

int **crop_ascii(img_t *img, select_t *select)
{
	// Se elibereaza structura anterioara
	eliberare(img);

	if (strcmp(select->tip, P2_TIP) == 0) {
		int lin = select->y2 - select->y1;
		int col = select->x2 - select->x1;

		// Se aloca memorie in functie de liniile si coloanele selectiei
		img->mat = aloc_2d(lin, col);

		// Se copiaza valorile din selectie in noua matrice
		for (int i = 0; i < lin; i++)
			for (int j = 0; j < col; j++)
				img->mat[i][j] = select->mat[i][j];

		// Se modifica variabilele cu noile valori.
		img->col = col;
		img->lin = lin;

		select->x1 = ORIG;
		select->x2 = col;
		select->y1 = ORIG;
		select->y2 = lin;
	} else if (strcmp(select->tip, P3_TIP) == 0) {
		int lin = select->y2 - select->y1;
		int col = 3 * (select->x2 - select->x1);

		img->mat = aloc_2d(lin, col);

		for (int i = 0; i < lin; i++)
			for (int j = 0; j < col; j++)
				img->mat[i][j] = select->mat[i][j];

		img->col = col;
		img->lin = lin;

		select->x1 = ORIG;
		select->x2 = col / 3;
		select->y1 = ORIG;
		select->y2 = lin;
	}
	return img->mat;
}

// Explicatiile sunt similare, doar ca se aplica pentru imagine binara.
unsigned char **crop_bin(img_b_t *img_b, select_b_t *select_b)
{
	eliberare_bin(img_b);
	if (strcmp(select_b->tip, P5_TIP) == 0) {
		int lin = select_b->y2 - select_b->y1;
		int col = select_b->x2 - select_b->x1;

		img_b->mat = aloc_2d_bin(lin, col);

		for (int i = 0; i < lin; i++)
			for (int j = 0; j < col; j++)
				img_b->mat[i][j] = select_b->mat[i][j];

		img_b->col = col;
		img_b->lin = lin;

		select_b->x1 = ORIG;
		select_b->x2 = col;
		select_b->y1 = ORIG;
		select_b->y2 = lin;

	} else if (strcmp(select_b->tip, P6_TIP) == 0) {
		int lin = select_b->y2 - select_b->y1;
		int col = 3 * (select_b->x2 - select_b->x1);

		img_b->mat = aloc_2d_bin(lin, col);

		for (int i = 0; i < lin; i++)
			for (int j = 0; j < col; j++)
				img_b->mat[i][j] = select_b->mat[i][j];

		img_b->col = col;
		img_b->lin = lin;

		select_b->x1 = ORIG;
		select_b->x2 = col / 3;
		select_b->y1 = ORIG;
		select_b->y2 = lin;
	}
	return img_b->mat;
}

void crop_cmd(img_t *img, img_b_t *img_b, select_t *sel, select_b_t *select_b
, char op[], int exista, int bin)
{
	if (!exista) {
		printf("No image loaded\n");
	} else {
		if (!verif_op_un_cuv(op, CROP)) {
			printf("Invalid command\n");
		} else {
			if (!bin)
				img->mat = crop_ascii(img, sel);
			else
				img_b->mat = crop_bin(img_b, select_b);
			printf("Image cropped\n");
		}
	}
}
