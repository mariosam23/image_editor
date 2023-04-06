#pragma once

#include <stdio.h>

#define LUNG_MAX_TIP 3

void rotire_90_p2(img_t *img, select_t *select);

void rotire_90_p3(img_t *img, select_t *select);

void rotire_90_p5(img_b_t *img, select_b_t *select);

void rotire_90_p6(img_b_t *img, select_b_t *select);

void rotire_ascii(img_t *img, select_t *sel, int unghi);

void rotire_bin(img_b_t *img_b, select_b_t *select_b, int unghi);

void rotate_cmd(img_t *img, img_b_t *img_b, select_t *select
, select_b_t *select_b, int bin, char op[], int exista);
