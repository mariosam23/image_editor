#pragma once

#include <stdio.h>

#define LUNG_MAX_TIP 3

int **crop_ascii(img_t *img, select_t *select);

unsigned char **crop_bin(img_b_t *img_b, select_b_t *select_b);

void crop_cmd(img_t *img, img_b_t *img_b, select_t *sel, select_b_t *select_b
, char op[], int exista, int bin);
