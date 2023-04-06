#pragma once

#include <stdio.h>

#define LUNG_MAX_TIP 3

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

unsigned char **aloc_2d_bin(int l, int c);

void citire_mat_bin(img_b_t *img_b, FILE *imag);

void eliberare_bin(img_b_t *img_b);

void prelucrare_fisier_p5(img_b_t *continut, FILE *imag);

void prelucrare_fisier_p6(img_b_t *cont_b, FILE *imag);

int **aloc_2d(int l, int c);

void citire_mat(img_t *img, FILE *imag);

void extragere(img_t *img, FILE *imag);

int verif_op_un_cuv(char linie[], const char comanda[]);

void eliberare(img_t *img);

void denumire(char num_fis[], char op[]);

int is_digit(char ch);

void inters_int(int *a, int *b);

int min(int x, int y);

int max(int x, int y);

void clamp(int *nr);

void eliberare_select_ascii(select_t *select);

void eliberare_select_b(select_b_t *select_b);

void verif_fisier(FILE *fisier);
