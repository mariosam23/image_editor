#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generale_f.h"

#define TOT 1
#define NU_TOT 0
#define ORIG 0
#define P2_TIP "P2"
#define P3_TIP "P3"
#define P5_TIP "P5"
#define P6_TIP "P6"

int verif_select(char linie[], const char comanda[])
{
	// Daca este comanda "SELECT ALL"
	if (strstr(linie, comanda) && strstr(linie, "ALL"))
		return 1;

	int cnt_num = 0;
	for (int i = 0; i < (int)strlen(linie); i++) {
		int numar = 0;
		while (is_digit(linie[i]))
			i++, numar = 1;
		if (numar == 1)
			cnt_num++;
	}

	// Daca se gasesc 4 numere in linie
	if (cnt_num == 4)
		return 2;

	return 0;
}

void select_ascii(img_t *img, select_t *sel, int tot, int x1, int y1, int x2
, int y2)
{
	strcpy(sel->tip, img->tip);
	sel->val_max = img->val_max;

	// Daca este selectia pe toata imaginea
	if (tot == 1) {
		// Se copiaza valorile din structura imaginii in structura selectiei
		sel->x1 = ORIG;
		sel->x2 = img->col;
		sel->y1 = ORIG;
		sel->y2 = img->lin;

		int lin = sel->y2;
		int col = sel->x2;
		sel->mat = aloc_2d(lin, col);
		for (int i = 0; i < lin; i++)
			for (int j = 0; j < col; j++)
				sel->mat[i][j] = img->mat[i][j];

		if (strcmp(img->tip, P3_TIP) == 0)
			sel->x2 /= 3;
	} else {
		if (strcmp(img->tip, P2_TIP) == 0) {
			sel->x1 = x1;
			sel->x2 = x2;
			sel->y1 = y1;
			sel->y2 = y2;

			int lin = y2 - y1;
			int col = x2 - x1;

			// Se copiaza valorile de la coordonatele din comanda SELECT
			sel->mat = aloc_2d(lin, col);
			for (int i = 0; i < lin; i++)
				for (int j = 0; j < col; j++)
					sel->mat[i][j] = img->mat[i + y1][j + x1];
		}	else {
			sel->x1 = x1;
			sel->x2 = x2;
			sel->y1 = y1;
			sel->y2 = y2;

			int lin = y2 - y1;
			int  col = x2 - x1;

			sel->mat = aloc_2d(lin, 3 * col);
			for (int i = 0; i < lin; i++)
				for (int j = 0; j < 3 * col; j++)
					sel->mat[i][j] = img->mat[i + y1][j + 3 * x1];
		}
	}
}

void select_bin(img_b_t *img_b, select_b_t *sel_b, int tot, int x1
, int y1, int x2, int y2)
{
	strcpy(sel_b->tip, img_b->tip);
	sel_b->val_max = img_b->val_max;

	if (tot == 1) {
		sel_b->x1 = ORIG;
		sel_b->x2 = img_b->col;
		sel_b->y1 = ORIG;
		sel_b->y2 = img_b->lin;

		int lin = sel_b->y2;
		int col = sel_b->x2;

		sel_b->mat = aloc_2d_bin(lin, col);

		for (int i = 0; i < lin; i++)
			for (int j = 0; j < col; j++)
				sel_b->mat[i][j] = img_b->mat[i][j];
		if (strcmp(img_b->tip, P6_TIP) == 0)
			sel_b->x2 /= 3;

	} else {
		if (strcmp(img_b->tip, P5_TIP) == 0) {
			sel_b->x1 = x1;
			sel_b->x2 = x2;
			sel_b->y1 = y1;
			sel_b->y2 = y2;

			int lin = y2 - y1;
			int col = x2 - x1;

			sel_b->mat = aloc_2d_bin(lin, col);

			for (int i = 0; i < lin; i++)
				for (int j = 0; j < col; j++)
					sel_b->mat[i][j] = img_b->mat[i + y1][j + x1];
		} else {
			sel_b->x1 = x1;
			sel_b->x2 = x2;
			sel_b->y1 = y1;
			sel_b->y2 = y2;

			int lin = y2 - y1;
			int col = x2 - x1;
			sel_b->mat = aloc_2d_bin(lin, 3 * col);

			for (int i = 0; i < lin; i++)
				for (int j = 0; j < 3 * col; j++)
					sel_b->mat[i][j] = img_b->mat[i + y1][j + 3 * x1];
		}
	}
}

// Functia care realizeaza selectarea intregii imagini.
void select_tot_cmd(img_t *img, img_b_t *img_b, char op[]
, int bin, select_t *sel, select_b_t *sel_b, int exista)
{
	if (!exista) {
		printf("No image loaded\n");
	} else {
		if (strstr(op, " ALL\n") || strstr(op, " ALL ")) {
			if (!bin) {
				eliberare_select_ascii(sel);
				int y2 = img->col;

				int x2 = img->lin;

				// Se selecteaza toata imaginea.
				select_ascii(img, sel, TOT, ORIG, ORIG, x2, y2);

				printf("Selected ALL\n");
			} else {
				eliberare_select_b(sel_b);

				int y2 = img_b->col;
				int x2 = img_b->lin;

				select_bin(img_b, sel_b, TOT, ORIG, ORIG, x2, y2);

				printf("Selected ALL\n");
			}
		} else {
			printf("Invalid command\n");
		}
	}
}

// Functia care verifica daca sunt corecte coordonatele comenzii SELECT.
int verif_coord_ascii(int x1, int x2, int y1, int y2, img_t *img)
{
	if (strcmp(img->tip, P2_TIP) == 0) {
		if (min(x1, x2) < 0 || max(x1, x2) > img->col || min(y1, y2) < 0)
			return 0;
		else if (max(y1, y2) > img->lin || x1 == x2 || y1 == y2)
			return 0;
	} else {
		if (min(x1, x2) < 0 || max(x1, x2) > img->col / 3 || min(y1, y2) < 0)
			return 0;
		else if (max(y1, y2) > img->lin || x1 == x2 || y1 == y2)
			return 0;
	}
	return 1;
}

int verif_coord_bin(int x1, int x2, int y1, int y2, img_b_t *img_b)
{
	if (strcmp(img_b->tip, P5_TIP) == 0) {
		if (min(x1, x2) < 0 || max(x1, x2) > img_b->col || min(y1, y2) < 0)
			return 0;
		else if (max(y1, y2) > img_b->lin || x1 == x2 || y1 == y2)
			return 0;
	} else {
		if (min(x1, x2) < 0 || max(x1, x2) > img_b->col / 3 || min(y1, y2) < 0)
			return 0;
		else if (max(y1, y2) > img_b->lin || x1 == x2 || y1 == y2)
			return 0;
	}
	return 1;
}

// Functia care realizeaza selectarea coordonatelor asupara imaginii.
void select_coord_cmd(img_t *img, img_b_t *img_b, char op[]
, int bin, select_t *sel, select_b_t *sel_b, int exista)
{
	if (!exista) {
		printf("No image loaded\n");
	} else {
		int x1, x2, y1, y2;

		int nr = sscanf(op, "%*[^0123456789-]%d %d %d %d", &x1, &y1, &x2, &y2);
		if (nr != 4) {
			fprintf(stderr, "Eroare la citire\n");
			exit(-1);
		}
		if (!bin) {
			if (!verif_coord_ascii(x1, x2, y1, y2, img)) {
				printf("Invalid set of coordinates\n");
			} else {
				eliberare_select_ascii(sel);

				if (x1 > x2)
					inters_int(&x1, &x2);
				if (y1 > y2)
					inters_int(&y1, &y2);

				// Se selecteaza doar coordonatele x1, y1, x2, y2.
				select_ascii(img, sel, NU_TOT, x1, y1, x2, y2);
				printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
			}
		} else {
			if (!verif_coord_bin(x1, x2, y1, y2, img_b)) {
				printf("Invalid set of coordinates\n");
			} else {
				eliberare_select_b(sel_b);

				if (x1 > x2)
					inters_int(&x1, &x2);
				if (y1 > y2)
					inters_int(&y1, &y2);

				select_bin(img_b, sel_b, NU_TOT, x1, y1, x2, y2);
				printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
			}
		}
	}
}
