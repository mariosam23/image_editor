#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "generale_f.h"

#define LUNG_MAX_OP 70
#define APPLY "APPLY"
#define P2_TIP "P2"
#define P3_TIP "P3"
#define P5_TIP "P5"
#define P6_TIP "P6"

int verif_apply(char linie[], const char comanda[])
{
	// Declar un vector in care salvez linia originala, astfel incat aceasta
	// sa ramana nemodificata dupa ce folosesc functia "strtok"

	char tmp[LUNG_MAX_OP];
	strcpy(tmp, linie);

	char *p = strtok(tmp, " ");
	int nr_cuv = 1;

	while (p) {
		// Verific daca primul cuvant este numele comenzii
		if (nr_cuv == 1 && strcmp(comanda, p))
			return 0;
		nr_cuv++;
		p = strtok(NULL, "\n");
	}

	// Daca nu gasesc suficiente cuvinte pentru comanda APPLY.
	if (nr_cuv != 3)
		return 0;

	return 1;
}

int in_mat(img_t *img, select_t *sel, int i, int j)
{
	// Verific daca se poate aplica comanda APPLY pe pixelul de coordonate
	// (i, j).
	if (i + sel->y1 == 0 || j + 3 * sel->x1 < 3 || i + sel->y1 + 1 == img->lin)
		return 0;
	if (j + 3 * sel->x1 + 1 > img->col - 3)
		return 0;

	return 1;
}

// Functia pentru aplicarea matricei kernel cu elemente numere intregi
void aplicare_kernel1(img_t *img, select_t *select, const int mat_ker[3][3])
{
	int lin = select->y2 - select->y1;
	int col = select->x2 - select->x1;

	for (int i = 0; i < lin; i++)
		for (int j = 0; j < 3 * col; j++)
			// Daca pixelul are suficienti vecini, il modific.
			if (in_mat(img, select, i, j)) {
				// Declar matricea in care incadrez pixelul
				int mat_pix[3][3];
				for (int k = 0; k < 3; k++)
					for (int z = 0; z < 3; z++) {
						// Variabila auxiliara pentru a nu depasi limita de 80.
						int aux = j - 3 + 3 * select->x1 + 3 * z;
						// Iau pixelii din matricea mare pentru a incadra
						// pixelul de la pozitia (i, j).
						mat_pix[k][z] = img->mat[i + select->y1 - 1 + k][aux];
					}

			int sum = 0;
			// Realizez suma dintre matricea in care am incadrat pixelul
			// si kernel.
			for (int k = 0; k < 3; k++)
				for (int z = 0; z < 3; z++)
					sum += mat_pix[k][z] * mat_ker[k][z];

			clamp(&sum);
			select->mat[i][j] = sum;
		}
}

// Functia pentru aplicarea matricei kernel cu elemente numere reale
// (blur sau gaussian_blur)
void aplicare_kernel2(img_t *img, select_t *select, const int mat_ker[3][3]
, double fractie)
{
	int lin = select->y2 - select->y1;
	int col = select->x2 - select->x1;

	for (int i = 0; i < lin; i++)
		for (int j = 0; j < 3 * col; j++)
			if (in_mat(img, select, i, j)) {
				int mat_pix[3][3];
				for (int k = 0; k < 3; k++)
					for (int z = 0; z < 3; z++) {
						int aux = j - 3 + 3 * select->x1 + 3 * z;
						mat_pix[k][z] = img->mat[i + select->y1 - 1 + k][aux];
					}

			double sum = 0;

			for (int k = 0; k < 3; k++)
				for (int z = 0; z < 3; z++)
					sum += mat_pix[k][z] * mat_ker[k][z];

			// Dupa ce realizez suma inmultesc rezultatul cu variabila fractie
			sum *= fractie;

			int val = round(sum);
			clamp(&val);

			select->mat[i][j] = val;
			}
}

void apply_ascii(img_t *img, select_t *select, const int mat_ker[3][3]
, double fractie)
{
	int lin = select->y2 - select->y1;
	int col = select->x2 - select->x1;

	// Am initializat valoarea "fractie" cu o valoare mai mare decat 1
	// daca matricea are elemente intregi, altfel cu valoarea care trebuie
	// pentru a putea utiliza o singura functie pentru toate kernel-urile.
	if (fractie > 1)
		aplicare_kernel1(img, select, mat_ker);
	else
		aplicare_kernel2(img, select, mat_ker, fractie);

	// Modific elementele "matricei mare" cu elementele modificate dupa
	// aplicarea comenzii "APPLY".
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < 3 * col; j++)
			img->mat[i + select->y1][j + 3 * select->x1] = select->mat[i][j];
}

int in_mat_b(img_b_t *img, select_b_t *sel, int i, int j)
{
	if (i + sel->y1 == 0 || j + 3 * sel->x1 < 3 || i + sel->y1 + 1 == img->lin)
		return 0;
	if (j + 3 * sel->x1 + 1 > img->col - 3)
		return 0;

	return 1;
}

// Explicatiile sunt similare cu cele ale functiilor de mai sus, doar ca
// se aplica imaginilor in format binar.
void aplicare_kernel1_b(img_b_t *img_b, select_b_t *sel_b
, const int mat_ker[3][3])
{
	int lin = sel_b->y2 - sel_b->y1;
	int col = sel_b->x2 - sel_b->x1;

	for (int i = 0; i < lin; i++)
		for (int j = 0; j < 3 * col; j++)
			if (in_mat_b(img_b, sel_b, i, j)) {
				int mat_pix[3][3];

				for (int k = 0; k < 3; k++)
					for (int z = 0; z < 3; z++) {
						int aux = j - 3 + 3 * sel_b->x1 + 3 * z;

						mat_pix[k][z] = img_b->mat[i + sel_b->y1 - 1 + k][aux];
					}

				int sum = 0;

				for (int k = 0; k < 3; k++)
					for (int z = 0; z < 3; z++)
						sum += mat_pix[k][z] * mat_ker[k][z];

				clamp(&sum);
				sel_b->mat[i][j] = sum;
			}
}

void aplicare_kernel2_b(img_b_t *img_b, select_b_t *sel_b
, const int mat_ker[3][3], double fractie)
{
	int lin = sel_b->y2 - sel_b->y1;
	int col = sel_b->x2 - sel_b->x1;

	for (int i = 0; i < lin; i++)
		for (int j = 0; j < 3 * col; j++)
			if (in_mat_b(img_b, sel_b, i, j)) {
				int mat_pix[3][3];

				for (int k = 0; k < 3; k++)
					for (int z = 0; z < 3; z++) {
						int aux = j - 3 + 3 * sel_b->x1 + 3 * z;

						mat_pix[k][z] = img_b->mat[i + sel_b->y1 - 1 + k][aux];
					}

			double sum = 0;

			for (int k = 0; k < 3; k++)
				for (int z = 0; z < 3; z++)
					sum += mat_pix[k][z] * mat_ker[k][z];

			sum *= fractie;

			int val = round(sum);

			clamp(&val);

			sel_b->mat[i][j] = val;
			}
}

void apply_bin(img_b_t *img_b, select_b_t *sel_b, const int mat_ker[3][3]
, double fractie)
{
	int lin = sel_b->y2 - sel_b->y1;
	int col = sel_b->x2 - sel_b->x1;

	if (fractie > 1)
		aplicare_kernel1_b(img_b, sel_b, mat_ker);
	else
		aplicare_kernel2_b(img_b, sel_b, mat_ker, fractie);

	for (int i = 0; i < lin; i++)
		for (int j = 0; j < 3 * col; j++)
			img_b->mat[i + sel_b->y1][j + 3 * sel_b->x1] = sel_b->mat[i][j];
}

void apply_cmd_edge(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin)
{
	if (!bin) {
		if (strcmp(img->tip, P3_TIP)) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			const int edge[3][3] = {
				{-1, -1, -1},
				{-1, 8, -1},
				{-1, -1, -1}
			};

			// Initializez "fractie" cu o valoare mai mare decat 1 pentru
			// a nu fi luata in considerare.
			double fractie = 2.2;

			apply_ascii(img, select, edge, fractie);
			printf("APPLY EDGE done\n");
		}
	} else {
		if (strcmp(img->tip, P6_TIP)) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double fractie = 2.2;

			const int edge[3][3] = {
			{-1, -1, -1},
			{-1, 8, -1},
			{-1, -1, -1}
			};

			apply_bin(img_b, select_b, edge, fractie);

			printf("APPLY EDGE done\n");
		}
	}
}

void apply_sharpen_cmd(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin)
{
	if (!bin) {
		if (strcmp(img->tip, P3_TIP)) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double fractie = 2.2;

			const int sharpen[3][3] = {
					{0, -1, 0},
					{-1, 5, -1},
					{0, -1, 0}
				};

			apply_ascii(img, select, sharpen, fractie);

			printf("APPLY SHARPEN done\n");
		}
	} else {
		if (strcmp(img->tip, P6_TIP)) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			double fractie = 2.2;

			const int sharpen[3][3] = {
					{0, -1, 0},
					{-1, 5, -1},
					{0, -1, 0}
				};

			apply_bin(img_b, select_b, sharpen, fractie);

			printf("APPLY SHARPEN done\n");
		}
	}
}

void apply_blur_cmd(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin)
{
	if (!bin) {
		if (strcmp(img->tip, P3_TIP)) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			const int blur[3][3] = {
				{1, 1, 1},
				{1, 1, 1},
				{1, 1, 1}
			};

			double fractie = (double)1 / 9;

			apply_ascii(img, select, blur, fractie);

			printf("APPLY BLUR done\n");
		}
	} else {
		if (strcmp(img->tip, P6_TIP)) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			const int blur[3][3] = {
				{1, 1, 1},
				{1, 1, 1},
				{1, 1, 1}
			};

			double fractie = (double)1 / 9;

			apply_bin(img_b, select_b, blur, fractie);

			printf("APPLY BLUR done\n");
		}
	}
}

void apply_gaussian(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin)
{
	if (!bin) {
		if (strcmp(img->tip, P3_TIP)) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			const int gaussian[3][3] = {
				{1, 2, 1},
				{2, 4, 2},
				{1, 2, 1}
			};

			const double fractie = (double)1 / 16;

			apply_ascii(img, select, gaussian, fractie);

			printf("APPLY GAUSSIAN_BLUR done\n");
		}
	} else {
		if (strcmp(img->tip, P6_TIP)) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			const int gaussian[3][3] = {
				{1, 2, 1},
				{2, 4, 2},
				{1, 2, 1}
			};

			double fractie = (double)1 / 16;

			apply_bin(img_b, select_b, gaussian, fractie);

			printf("APPLY GAUSSIAN_BLUR done\n");
		}
	}
}

void apply_cmd(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin, char op[], int exista)
{
	if (!exista) {
		printf("No image loaded\n");
	} else {
		if (!verif_apply(op, APPLY)) {
			printf("Invalid command\n");
		} else {
			char nume_cmd[LUNG_MAX_OP];

			// Se obtine numele operatiei pentru care se doreste apply.
			denumire(nume_cmd, op);

			// Daca nu este data nicio denumire
			if (nume_cmd[0] == '\0') {
				printf("Invalid command\n");
			} else {
				if (strcmp(nume_cmd, "EDGE") == 0)
					apply_cmd_edge(img, img_b, select, select_b, bin);
				else if (strcmp(nume_cmd, "SHARPEN") == 0)
					apply_sharpen_cmd(img, img_b, select, select_b, bin);
				else if (strcmp(nume_cmd, "BLUR") == 0)
					apply_blur_cmd(img, img_b, select, select_b, bin);
				else if (strcmp(nume_cmd, "GAUSSIAN_BLUR") == 0)
					apply_gaussian(img, img_b, select, select_b, bin);
				else
					printf("APPLY parameter invalid\n");
			}
		}
	}
}
