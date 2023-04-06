#pragma once

#include <stdio.h>

int verif_apply(char linie[], const char comanda[]);

int in_mat(img_t *img, select_t *sel, int i, int j);

void aplicare_kernel1(img_t *img, select_t *select, const int mat[3][3]);

void aplicare_kernel2(img_t *img, select_t *select, const int mat[3][3]
, double fractie);

void apply_ascii(img_t *img, select_t *select, const int mat[3][3]
, double fractie);

int in_mat_b(img_b_t *img, select_b_t *sel, int i, int j);

void aplicare_kernel1_b(img_b_t *img_b, select_b_t *sel_b
, const int mat[3][3]);

void aplicare_kernel2_b(img_b_t *img_b, select_b_t *sel_b, const int mat[3][3]
, double fractie);

void apply_bin(img_b_t *img_b, select_b_t *sel_b, const int mat[3][3]
, double fractie);

void apply_cmd_edge(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin);

void apply_sharpen_cmd(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin);

void apply_blur_cmd(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin);

void apply_gaussian(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin);

void apply_cmd(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin, char op[], int exista);
