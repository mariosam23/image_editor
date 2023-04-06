#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generale_f.h"
#include "select_f.h"

#define LUNG_MAX_OP 70
#define TOT 1
#define NU_TOT 0
#define ORIG 0
#define P2_TIP "P2"
#define P3_TIP "P3"
#define P5_TIP "P5"
#define P6_TIP "P6"

// Functia prin intermediul careia verific daca comanda "LOAD" a fost
// scrisa corect.
int verif_load(char linie[], const char comanda[])
{
	// Declar un vector in care salvez linia originala, astfel incat aceasta
	// sa ramana nemodificata dupa ce folosesc functia "strtok"
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

	if (cnt != 3)
		return 0;

	return 1;
}

// Daca urmeaza sa se introduca un nou fisier, fisierul existent impreuna
// cu memoria alocata pentru structuri sunt eliberate.
void eliberare_fis_existent(img_t *img, img_b_t *img_b, char op[]
, char num_f[], int exis, int bin, FILE *imag, select_t *sel, select_b_t *s_b)
{
	// Se obtine numele fisierului.
	denumire(num_f, op);

	if (exis == 1) {
		fclose(imag);
		if (!bin) {
			eliberare_select_ascii(sel);
			eliberare(img);
		} else {
			eliberare_select_b(s_b);
			eliberare_bin(img_b);
		}
	}
}

void load_ascii(img_t *img, select_t *select, FILE *imag, int *bin)
{
	// Se parseaza fisierul cu imaginea de tip P2.
	if (strcmp(img->tip, P2_TIP) == 0) {
		extragere(img, imag);

		img->mat = aloc_2d(img->lin, img->col);
		citire_mat(img, imag);

		int y2 = img->col;
		int x2 = img->lin;

		// Valorile de pe structura imaginii sunt copiate si in structura
		// selectiei cu selectia maxima a matricei.
		select_ascii(img, select, TOT, ORIG, ORIG, x2, y2);
	} else {
		// Se parseaza fisierul cu imaginea de tip P3.
		extragere(img, imag);

		// Deoarece pixelii sunt de forma unui triplet, matricea poate fi
		// interpretata ca una cu 3 * nr_col din fisier.
		img->col *= 3;
		img->mat = aloc_2d(img->lin, img->col);

		citire_mat(img, imag);

		int y2 = img->col;

		int x2 = img->lin;

		// Valorile de pe structura imaginii sunt copiate si in structura
		// selectiei cu selectia maxima a matricei.
		select_ascii(img, select, TOT, ORIG, ORIG, x2, y2);
	}

	*bin = 0;
}

void load_bin(img_b_t *img_b, select_b_t *select_b, FILE *imag, int *bin
, img_t *img)
{
	// Se parseaza fisierul cu imaginea de tip P5.
	verif_fisier(imag);
	if (strcmp(img->tip, P5_TIP) == 0) {
		prelucrare_fisier_p5(img_b, imag);
		*bin = 1;

		int y2 = img_b->col;
		int x2 = img_b->lin;

		select_bin(img_b, select_b, TOT, ORIG, ORIG, x2, y2);

	} else {
		// Se parseaza fisierul cu imaginea de tip P6.
		prelucrare_fisier_p6(img_b, imag);
		*bin = 1;

		int y2 = img_b->col;
		int x2 = img_b->lin;

		select_bin(img_b, select_b, TOT, ORIG, ORIG, x2, y2);
	}
}
