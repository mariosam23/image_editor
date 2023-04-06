#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generale_f.h"

#define LUNG_MAX_OP 70
#define P2_TIP "P2"
#define P3_TIP "P3"
#define P5_TIP "P5"
#define P6_TIP "P6"
#define SAVE "SAVE"

int verif_save(char linie[], const char comanda[])
{
	// Declar un vector in care salvez linia originala, astfel incat aceasta
	// sa ramana nemodificata dupa ce folosesc functia "strtok".
	char tmp[LUNG_MAX_OP];
	strcpy(tmp, linie);

	char *p = strtok(tmp, " ");
	int cnt = 1;

	while (p) {
		if (cnt == 1 && strcmp(comanda, p))
			return 0;
		cnt++;
		p = strtok(NULL, "\n");
	}

	// Daca nu apare sirul "ascii"
	if (cnt == 3)
		return 1;

	// Daca apare sirul "ascii"
	if (cnt == 4)
		return 2;

	return 0;
}

void save_p2_ascii(FILE *img_salvata, img_t *img)
{
	fprintf(img_salvata, "%s\n", img->tip);
	fprintf(img_salvata, "%d %d\n", img->col, img->lin);
	fprintf(img_salvata, "%d\n", img->val_max);

	for (int i = 0; i < img->lin; i++, fprintf(img_salvata, "\n"))
		for (int j = 0; j < img->col; j++)
			fprintf(img_salvata, "%d ", img->mat[i][j]);
}

void save_p3_ascii(FILE *img_salvata, img_t *img)
{
	fprintf(img_salvata, "%s\n", img->tip);
	fprintf(img_salvata, "%d %d\n", img->col / 3, img->lin);
	fprintf(img_salvata, "%d\n", img->val_max);

	for (int i = 0; i < img->lin; i++, fprintf(img_salvata, "\n"))
		for (int j = 0; j < img->col; j++)
			fprintf(img_salvata, "%d ", img->mat[i][j]);
}

void save_p5_ascii(FILE *img_salvata, img_b_t *img_b)
{
	fprintf(img_salvata, "P2\n");
	fprintf(img_salvata, "%d %d\n", img_b->col, img_b->lin);
	fprintf(img_salvata, "%d\n", img_b->val_max);

	for (int i = 0; i < img_b->lin; i++, fprintf(img_salvata, "\n"))
		for (int j = 0; j < img_b->col; j++)
			fprintf(img_salvata, "%d ", (int)img_b->mat[i][j]);
}

void save_p6_ascii(FILE *img_salvata, img_b_t *img_b)
{
	fprintf(img_salvata, "P3\n");
	fprintf(img_salvata, "%d %d\n", img_b->col / 3, img_b->lin);
	fprintf(img_salvata, "%d\n", img_b->val_max);

	for (int i = 0; i < img_b->lin; i++, fprintf(img_salvata, "\n"))
		for (int j = 0; j < img_b->col; j++)
			fprintf(img_salvata, "%d ", (int)img_b->mat[i][j]);
}

void save_ascii(img_t *img, img_b_t *img_b, char op[], int exista)
{
	if (!exista) {
		printf("No image loaded\n");
	} else {
		char nume_fis[70];

		// Extrag numele fisierului
		denumire(nume_fis, op);

		FILE *img_salvata;
		img_salvata = fopen(nume_fis, "wt");
		verif_fisier(img_salvata);

		if (strcmp(img->tip, P3_TIP) == 0)
			save_p3_ascii(img_salvata, img);
		else if (strcmp(img->tip, P2_TIP) == 0)
			save_p2_ascii(img_salvata, img);
		else if (strcmp(img_b->tip, P5_TIP) == 0)
			save_p5_ascii(img_salvata, img_b);
		else if (strcmp(img_b->tip, P6_TIP) == 0)
			save_p6_ascii(img_salvata, img_b);

		fclose(img_salvata);

		printf("Saved %s\n", nume_fis);
	}
}

void save_p2_bin(FILE *img_sal, img_t *img)
{
	fprintf(img_sal, "P5\n");
	fprintf(img_sal, "%d %d\n", img->col, img->lin);
	fprintf(img_sal, "%d\n", img->val_max);

	for (int i = 0; i < img->lin; i++)
		for (int j = 0; j < img->col; j++)
			fwrite(&img->mat[i][j], sizeof(unsigned char), 1, img_sal);
}

void save_p3_bin(FILE *img_sal, img_t *img)
{
	fprintf(img_sal, "P6\n");
	fprintf(img_sal, "%d %d\n", img->col / 3, img->lin);
	fprintf(img_sal, "%d\n", img->val_max);

	for (int i = 0; i < img->lin; i++)
		for (int j = 0; j < img->col; j++)
			fwrite(&img->mat[i][j], sizeof(unsigned char), 1, img_sal);
}

void save_p5_bin(FILE *img_sal, img_b_t *img_b)
{
	fprintf(img_sal, "%s\n", img_b->tip);
	fprintf(img_sal, "%d %d\n", img_b->col, img_b->lin);
	fprintf(img_sal, "%d\n", img_b->val_max);

	for (int i = 0; i < img_b->lin; i++)
		for (int j = 0; j < img_b->col; j++) {
			unsigned char tmp = (unsigned char)img_b->mat[i][j];
			fwrite(&tmp, sizeof(unsigned char), 1, img_sal);
		}
}

void save_p6_bin(FILE *img_sal, img_b_t *img_b)
{
	fprintf(img_sal, "%s\n", img_b->tip);
	fprintf(img_sal, "%d %d\n", img_b->col / 3, img_b->lin);
	fprintf(img_sal, "%d\n", img_b->val_max);

	for (int i = 0; i < img_b->lin; i++)
		for (int j = 0; j < img_b->col; j++) {
			unsigned char tmp = (unsigned char)img_b->mat[i][j];
			fwrite(&tmp, sizeof(unsigned char), 1, img_sal);
		}
}

void save_bin(img_t *img, img_b_t *img_b, char op[], int exista)
{
	if (!exista) {
		printf("No image loaded\n");
	} else {
		char nume_fis[70];
		denumire(nume_fis, op);

		FILE *img_sal;
		img_sal = fopen(nume_fis, "wb");
		verif_fisier(img_sal);

		if (strcmp(img->tip, P2_TIP) == 0)
			save_p2_bin(img_sal, img);
		else if (strcmp(img->tip, P3_TIP) == 0)
			save_p3_bin(img_sal, img);
		else if (strcmp(img_b->tip, P5_TIP) == 0)
			save_p5_bin(img_sal, img_b);
		else if (strcmp(img_b->tip, P6_TIP) == 0)
			save_p6_bin(img_sal, img_b);

		fclose(img_sal);
		printf("Saved %s\n", nume_fis);
	}
}

void save_cmd(img_t *img, img_b_t *img_b, char op[], int exista)
{
	if (!verif_save(op, SAVE))
		printf("Invalid command\n");
	else if (verif_save(op, SAVE) == 1)
		save_bin(img, img_b, op, exista);
	else if (verif_save(op, SAVE) == 2)
		save_ascii(img, img_b, op, exista);
}
