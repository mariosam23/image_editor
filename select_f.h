#pragma once

#include <stdio.h>

#define LUNG_MAX_TIP 3

int verif_select(char linie[], const char comanda[]);

void select_ascii(img_t *con, select_t *sel, int s, int x1, int y1, int x2
, int y2);

void select_bin(img_b_t *c, select_b_t *s_b, int s, int x1, int y1, int x2
, int y2);

void select_tot_cmd(img_t *img, img_b_t *img_b, char op[]
, int bin, select_t *sel, select_b_t *s_b, int exista);

int verif_coord_ascii(int x1, int x2, int y1, int y2, img_t *img);

int verif_coord_bin(int x1, int x2, int y1, int y2, img_b_t *img_b);

void select_coord_cmd(img_t *img, img_b_t *img_b, char op[]
, int bin, select_t *sel, select_b_t *s_b, int exista);
