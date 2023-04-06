#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EROARE -1
#define LUNG_MAX_TIP 3
#define LINE_MAX 70
#define APPLY "APPLY"
#define MAX_VAL 255
#define MIN_VAL 0

typedef struct __attribute__((__packed__)) {
	char tip[LUNG_MAX_TIP];
	unsigned char **mat;
	int col;
	int lin;
	int val_max;
} img_b_t;

typedef struct __attribute__((__packed__)) {
	unsigned char **mat;
	int x1, x2;
	int y1, y2;
	int val_max;
	char tip[LUNG_MAX_TIP];
} select_b_t;

typedef struct __attribute__((__packed__)) {
	int **mat;
	int lin;
	int col;
	int val_max;
	char tip[LUNG_MAX_TIP];
} img_t;

typedef struct __attribute__((__packed__)) {
	int **mat;
	int x1, x2;
	int y1, y2;
	int val_max;
	char tip[LUNG_MAX_TIP];
} select_t;

unsigned char **aloc_2d_bin(int l, int c)
{
	unsigned char **p = malloc(l * sizeof(unsigned char *));

	if (!p) {
		fprintf(stderr, "Eroare la alocare");

		exit(EROARE);
	}

	for (int i = 0; i < l; i++) {
		p[i] = malloc(c * sizeof(unsigned char));

		if (!p[i]) {
			for (int j = 0; j < i; j++)
				free(p[i]);
			free(p);

			fprintf(stderr, "Eroare la alocare");

			exit(EROARE);
		}
	}
	return p;
}

void citire_mat_bin(img_b_t *img_b, FILE *imag)
{
	for (int i = 0; i < img_b->lin; i++)
		for (int j = 0; j < img_b->col; j++)
			fread(&img_b->mat[i][j], sizeof(unsigned char), 1, imag);
}

void eliberare_bin(img_b_t *img_b)
{
	for (int i = 0; i < img_b->lin; i++)
		free(img_b->mat[i]);
	free(img_b->mat);
}

// Parsarea fisierului de tip "P5"
void prelucrare_fisier_p5(img_b_t *img_b, FILE *imag)
{
	fscanf(imag, "%s", img_b->tip);

	char line[LINE_MAX];
	fgets(line, LINE_MAX, imag);
	while (fgets(line, LINE_MAX, imag)) {
		// Daca nu este linie goala si nu se gaseste caracterul '#'
		if (!strchr(line, '#') && line[0] != '\n')
			break;
	}

	// Verific daca sscanf a returnat rezultatul dorit
	int nr = sscanf(line, "%d %d", &img_b->col, &img_b->lin);

	if (nr != 2) {
		fprintf(stderr, "Eroare la sscanf\n");
		exit(EROARE);
	}
	fscanf(imag, "%d", &img_b->val_max);

	img_b->mat = aloc_2d_bin(img_b->lin, img_b->col);

	fseek(imag, 1, SEEK_CUR);

	citire_mat_bin(img_b, imag);
}

// Parsarea fisierului de tip "P6"
void prelucrare_fisier_p6(img_b_t *cont_b, FILE *imag)
{
	fscanf(imag, "%s", cont_b->tip);

	char line[LINE_MAX];
	fgets(line, LINE_MAX, imag);
	while (fgets(line, LINE_MAX, imag)) {
		// Daca nu este linie goala si nu se gaseste caracterul '#'
		if (!strchr(line, '#') && line[0] != '\n')
			break;
	}

	int nr = sscanf(line, "%d %d", &cont_b->col, &cont_b->lin);
	if (nr != 2) {
		fprintf(stderr, "Eroare la sscanf\n");
		exit(EROARE);
	}

	fscanf(imag, "%d", &cont_b->val_max);

	cont_b->col *= 3;
	cont_b->mat = aloc_2d_bin(cont_b->lin, cont_b->col);

	fseek(imag, 1, SEEK_CUR);

	citire_mat_bin(cont_b, imag);
}

int **aloc_2d(int l, int c)
{
	int **p = malloc(l * sizeof(int *));
	if (!p) {
		fprintf(stderr, "Eroare la alocare");
		exit(EROARE);
	}

	for (int i = 0; i < l; i++) {
		p[i] = malloc(c * sizeof(int));
		if (!p[i]) {
			for (int j = 0; j < i; j++)
				free(p[i]);
			free(p);

			fprintf(stderr, "Eroare la alocare");

			exit(EROARE);
		}
	}
	return p;
}

void citire_mat(img_t *img, FILE *imag)
{
	for (int i = 0; i < img->lin; i++)
		for (int j = 0; j < img->col; j++)
			fscanf(imag, "%d", &img->mat[i][j]);
}

void extragere(img_t *img, FILE *imag)
{
	char line[LINE_MAX];
	fgets(line, LINE_MAX, imag);
	while (fgets(line, LINE_MAX, imag)) {
		// Daca nu este linie goala si nu se gaseste caracterul '#'
		if (!strchr(line, '#') && line[0] != '\n')
			break;
	}

	int nr = sscanf(line, "%d %d", &img->col, &img->lin);
	if (nr != 2) {
		fprintf(stderr, "Eroare la sscanf\n");
		exit(EROARE);
	}

	fscanf(imag, "%d", &img->val_max);
}

// Functia folosita pentru a verifica daca comenzile alcatuite doar
// dintr-un cuvant sunt corecte.
int verif_op_un_cuv(char linie[], const char comanda[])
{
	if (strstr(linie, comanda)) {
		char *aux = strstr(linie, comanda);

		int inainte = strlen(linie) - strlen(aux);
		int dupa = inainte + strlen(comanda);

		// Verific daca inainte de prima aparitie a comenzii am alte caractere
		// in afara de spatii
		for (int i = 0; i < inainte; i++) {
			if (linie[i] != ' ')
				return 0;
			}

		// Verific daca dupa prima aparitie a comenzii am alte caractere
		// in afara de spatii
		for (int i = dupa; i < (int)strlen(linie) - 1; i++) {
			if (linie[i] != ' ')
				return 0;
		}
	}	else {
		return 0;
	}

	return 1;
}

void eliberare(img_t *img)
{
	for (int i = 0; i < img->lin; i++)
		free(img->mat[i]);

	free(img->mat);
}

// Functia folosita pentru a extrage numele unui fisier sau parametrul
// comenzii "APPLY".
void denumire(char num_fis[], char op[])
{
	int denum_apply = verif_op_un_cuv(op, APPLY);

	if (denum_apply == 1) {
		num_fis[0] = '\0';
		return;
	}

	int cnt = 1;
	char *p = strtok(op, " ");
	while (p) {
		if (*p != '\n' && cnt == 2)
			strcpy(num_fis, p);
		cnt++;
		p = strtok(NULL, " ");
	}

	// Elimin caracterul 'new line' sau spatiu
	if (cnt == 2 || cnt == 3)
		num_fis[strlen(num_fis) - 1] = '\0';
}

int is_digit(char ch)
{
	return ch >= '0' && ch <= '9';
}

void inters_int(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int max(int x, int y)
{
	if (x > y)
		return x;
	return y;
}

int min(int x, int y)
{
	if (x < y)
		return x;
	return y;
}

void clamp(int *nr)
{
	if (*nr > MAX_VAL)
		*nr = MAX_VAL;
	if (*nr < MIN_VAL)
		*nr = MIN_VAL;
}

void eliberare_select_ascii(select_t *select)
{
	int l = select->y2 - select->y1;
	for (int i = 0; i < l; i++)
		free(select->mat[i]);
	free(select->mat);
}

void eliberare_select_b(select_b_t *select_b)
{
	int l = select_b->y2 - select_b->y1;
	for (int i = 0; i < l; i++)
		free(select_b->mat[i]);
	free(select_b->mat);
}

void verif_fisier(FILE *fisier)
{
	if (!fisier) {
		fprintf(stderr, "Eroare la deschiderea fisierului\n");
		exit(EROARE);
	}
}
