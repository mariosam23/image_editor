#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generale_f.h"

#define P2_TIP "P2"
#define P3_TIP "P3"
#define P5_TIP "P5"
#define P6_TIP "P6"
#define UNGHI_90 90
#define ORIG 0

// Rotirea este spre dreapta
void rotire_90_p2(img_t *img, select_t *select)
{
	int linii = select->y2 - select->y1;
	int coloane = select->x2 - select->x1;

	// Matricea in care voi salva elementele in urma rotirii.
	int **mat_rot = aloc_2d(coloane, linii);

	// Indicii matricei "mat_rot".
	int k = 0, l = 0;

	// Parcurg pe coloane selectia si coiez coloana 0 din selectie in
	// linia 0 din "mat_rot", coloana 1 in linia 2, si asa mai departe.
	for (int j = select->x1; j < select->x2; j++) {
		for (int i = select->y2 - 1; i >= select->y1; i--)
			mat_rot[k][l++] = img->mat[i][j];
		k++, l = 0;
	}

	// Daca selectia este pe toata imaginea
	if (linii == img->lin && coloane == img->col) {
		eliberare(img);

		eliberare_select_ascii(select);

		// Liniile devin coloane si invers.
		img->lin = coloane;
		img->col = linii;

		// Se aloca matricea cu noile dimensiuni
		img->mat = aloc_2d(img->lin, img->col);

		select->x1 = ORIG;
		select->y1 = ORIG;
		select->x2 = linii;
		select->y2 = coloane;

		select->mat = aloc_2d(select->y2, select->x2);

		// Valorile rezultate in urma rotirii sunt copiate in matricea
		//  structurii.
		for (int i = 0; i < coloane; i++)
			for (int j = 0; j < linii; j++) {
				img->mat[i][j] = mat_rot[i][j];
				select->mat[i][j] = mat_rot[i][j];
			}

	} else {
		// Daca este o matrice patrata, se copiaza direct valorile
		// rezultate in urma rotirii in matricea structurii.
		for (int i = 0; i < coloane; i++)
			for (int j = 0; j < linii; j++) {
				img->mat[i + select->y1][j + select->x1] = mat_rot[i][j];
				select->mat[i][j] = mat_rot[i][j];
			}
	}

	for (int i = 0; i < coloane; i++)
		free(mat_rot[i]);
	free(mat_rot);
}

void rotire_90_p3(img_t *img, select_t *select)
{
	int linii = select->y2 - select->y1;
	int coloane = select->x2 - select->x1;

	int **mat_rot = aloc_2d(coloane, 3 * linii);

	int k = 0, l = 0;

	for (int j = 3 * select->x1; j < 3 * select->x2; j += 3) {
		for (int i = select->y2 - 1; i >= select->y1; i--)
			for (int t = j; t < j + 3; t++)
				mat_rot[k][l++] = img->mat[i][t];
		k++, l = 0;
	}

	if (linii == img->lin && coloane == img->col / 3) {
		eliberare(img);
		eliberare_select_ascii(select);

		img->lin = coloane;
		img->col = linii * 3;
		img->mat = aloc_2d(img->lin, img->col);

		select->x1 = ORIG;
		select->y1 = ORIG;
		select->x2 = linii;
		select->y2 = coloane;
		select->mat = aloc_2d(img->lin, img->col);

		for (int i = 0; i < coloane; i++)
			for (int j = 0; j < 3 * linii; j++) {
				img->mat[i][j] = mat_rot[i][j];
				select->mat[i][j] = mat_rot[i][j];
			}

	} else {
		for (int i = 0; i < coloane; i++)
			for (int j = 0; j < 3 * linii; j++) {
				select->mat[i][j] = mat_rot[i][j];
				img->mat[i + select->y1][j + 3 * select->x1] = mat_rot[i][j];
			}
	}

	for (int i = 0; i < coloane; i++)
		free(mat_rot[i]);
	free(mat_rot);
}

void rotire_90_p5(img_b_t *img, select_b_t *select)
{
	int linii = select->y2 - select->y1;
	int coloane = select->x2 - select->x1;

	unsigned char **mat_rot = aloc_2d_bin(coloane, linii);

	int k = 0, l = 0;

	for (int j = select->x1; j < select->x2; j++) {
		for (int i = select->y2 - 1; i >= select->y1; i--)
			mat_rot[k][l++] = img->mat[i][j];
		k++, l = 0;
	}

	if (linii == img->lin && coloane == img->col) {
		eliberare_bin(img);
		eliberare_select_b(select);

		img->lin = coloane;
		img->col = linii;
		img->mat = aloc_2d_bin(img->lin, img->col);

		select->x1 = ORIG;
		select->y1 = ORIG;
		select->x2 = linii;
		select->y2 = coloane;
		select->mat = aloc_2d_bin(select->y2, select->x2);

		for (int i = 0; i < coloane; i++)
			for (int j = 0; j < linii; j++) {
				img->mat[i][j] = mat_rot[i][j];
				select->mat[i][j] = mat_rot[i][j];
			}

	} else {
		for (int i = 0; i < coloane; i++)
			for (int j = 0; j < linii; j++) {
				img->mat[i + select->y1][j + select->x1] = mat_rot[i][j];
				select->mat[i][j] = mat_rot[i][j];
			}
	}

	for (int i = 0; i < coloane; i++)
		free(mat_rot[i]);
	free(mat_rot);
}

void rotire_90_p6(img_b_t *img, select_b_t *select)
{
	int linii = select->y2 - select->y1;
	int coloane = select->x2 - select->x1;

	unsigned char **mat_rot = aloc_2d_bin(coloane, 3 * linii);

	int k = 0, l = 0;

	for (int j = 3 * select->x1; j < 3 * select->x2; j += 3) {
		for (int i = select->y2 - 1; i >= select->y1; i--)
			for (int t = j; t < j + 3; t++)
				mat_rot[k][l++] = img->mat[i][t];
		k++, l = 0;
	}

	if (linii == img->lin && coloane == img->col / 3) {
		eliberare_bin(img);
		eliberare_select_b(select);

		img->lin = coloane;
		img->col = linii * 3;
		img->mat = aloc_2d_bin(img->lin, img->col);

		select->x1 = ORIG;
		select->y1 = ORIG;
		select->x2 = linii;
		select->y2 = coloane;

		select->mat = aloc_2d_bin(img->lin, img->col);

		for (int i = 0; i < coloane; i++)
			for (int j = 0; j < 3 * linii; j++) {
				img->mat[i][j] = mat_rot[i][j];
				select->mat[i][j] = mat_rot[i][j];
			}

	} else {
		for (int i = 0; i < coloane; i++)
			for (int j = 0; j < 3 * linii; j++) {
				select->mat[i][j] = mat_rot[i][j];
				img->mat[i + select->y1][j + 3 * select->x1] = mat_rot[i][j];
			}
	}

	for (int i = 0; i < coloane; i++)
		free(mat_rot[i]);
	free(mat_rot);
}

void rotire_ascii(img_t *img, select_t *sel, int unghi)
{
	if (strcmp(img->tip, P2_TIP) == 0) {
		int lin = sel->y2 - sel->y1;
		int col = sel->x2 - sel->x1;

		// Daca nu este selectata toata imaginea si selectia nu este patrata.
		if (lin != col && (img->lin != lin || img->col != col)) {
			printf("The selection must be square\n");
		} else if (unghi % UNGHI_90) {
			printf("Unsupported rotation angle\n");
		} else {
			int copie_unghi = unghi;

			// Am implementat doar rotirea spre 90 de grade la dreapta,
			// deoarece orice rotire multiplu de 90 poate fi realizata doar
			// cu rotirea dreapta la 90 de grade. De exemplu rotirea la -270
			// inseamna rotirea o data la 90 spre dreapta.
			while (copie_unghi != 0 && copie_unghi != -360) {
				rotire_90_p2(img, sel);
				copie_unghi -= 90;
				if (copie_unghi == 0 || copie_unghi == -360)
					break;
			}
			printf("Rotated %d\n", unghi);
		}
	} else if (strcmp(img->tip, P3_TIP) == 0) {
		int lin = sel->y2 - sel->y1;
		int col = sel->x2 - sel->x1;

		if (lin != col && (img->lin != lin || img->col / 3 != col)) {
			printf("The selection must be square\n");
		} else if (unghi % UNGHI_90) {
			printf("Unsupported rotation angle\n");
		} else {
			int copie_unghi = unghi;

			while (copie_unghi != 0 && copie_unghi != -360) {
				rotire_90_p3(img, sel);
				copie_unghi -= 90;
				if (copie_unghi == 0 || copie_unghi == -360)
					break;
			}
			printf("Rotated %d\n", unghi);
		}
	}
}

void rotire_bin(img_b_t *img_b, select_b_t *select_b, int unghi)
{
	if (strcmp(img_b->tip, P5_TIP) == 0) {
		int lin = select_b->y2 - select_b->y1;
		int col = select_b->x2 - select_b->x1;

		if (lin != col && (img_b->lin != lin || img_b->col != col)) {
			printf("The selection must be square\n");
		} else if (unghi % UNGHI_90) {
			printf("Unsupported rotation angle\n");
		} else {
			int copie_unghi = unghi;

			while (copie_unghi != 0 && copie_unghi != -360) {
				rotire_90_p5(img_b, select_b);
				copie_unghi -= 90;
				if (copie_unghi == 0 || copie_unghi == -360)
					break;
			}
			printf("Rotated %d\n", unghi);
		}
	} else if (strcmp(img_b->tip, P6_TIP) == 0) {
		int lin = select_b->y2 - select_b->y1;
		int col = select_b->x2 - select_b->x1;

		if (lin != col && (img_b->lin != lin || img_b->col / 3 != col)) {
			printf("The selection must be square\n");
		} else if (unghi % UNGHI_90) {
			printf("Unsupported rotation angle\n");
		} else {
			int copie_unghi = unghi;

			while (copie_unghi != 0 && copie_unghi != -360) {
				rotire_90_p6(img_b, select_b);
				copie_unghi -= 90;
				if (copie_unghi == 0 || copie_unghi == -360)
					break;
			}
			printf("Rotated %d\n", unghi);
		}
	}
}

void rotate_cmd(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin, char op[], int exista)
{
	if (!exista) {
		printf("No image loaded\n");
	} else {
		int unghi;

		int nr = sscanf(op, "%*[^-0123456789]%d", &unghi);
		if (nr != 1) {
			fprintf(stderr, "Eroare la citire\n");
			exit(-1);
		}
		if (!bin)
			rotire_ascii(img, select, unghi);
		else
			rotire_bin(img_b, select_b, unghi);
	}
}
