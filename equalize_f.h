#pragma once

#include <stdio.h>

#define LUNG_MAX_TIP 3

void egalizare(img_t *img);

void egalizare_bin(img_b_t *img_b);

void egalizare_cmd(img_t *img, img_b_t *img_b, char op[], int bin, int exis);
