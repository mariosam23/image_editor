#pragma once

#include <stdio.h>

#define LUNG_MAX_TIP 3

int verif_save(char linie[], const char comanda[]);

void save_p2_ascii(FILE *img_salvata, img_t *img);

void save_p3_ascii(FILE *img_salvata, img_t *img);

void save_p5_ascii(FILE *img_salvata, img_b_t *img_b);

void save_p6_ascii(FILE *img_salvata, img_b_t *img_b);

void save_ascii(img_t *img, img_b_t *img_b, char op[], int exista);

void save_p2_bin(FILE *img_sal, img_t *img);

void save_p3_bin(FILE *img_sal, img_t *img);

void save_p5_bin(FILE *img_sal, img_b_t *img_b);

void save_p6_bin(FILE *img_sal, img_b_t *img_b);

void save_bin(img_t *img, img_b_t *img_b, char op[], int exista);

void save_cmd(img_t *img, img_b_t *img_b, char op[], int exista);
