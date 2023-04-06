#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "generale_f.h"
#include "load_f.h"
#include "select_f.h"
#include "exit_f.h"
#include "histogram_f.h"
#include "apply_f.h"
#include "crop_f.h"
#include "equalize_f.h"
#include "save_f.h"
#include "rotate_f.h"

#define LUNG_MAX_COMANDA 70
#define P2_TIP "P2"
#define P3_TIP "P3"
#define P5_TIP "P5"
#define P6_TIP "P6"
#define SELECT "SELECT"
#define LOAD "LOAD"
#define CROP "CROP"
#define EQUALIZE "EQUALIZE"
#define HISTOGRAM "HISTOGRAM"
#define APPLY "APPLY"
#define SAVE "SAVE"
#define ROTATE "ROTATE"
#define EXIT "EXIT"

int main(void)
{
	// Am declarat structuri separate pentru fiecare tip de imagine.
	// Variabila "exista" verifica daca este incarcata o imagine in memorie.
	img_t img; img_b_t img_b;
	select_t sel; select_b_t sel_b;
	char cmd[LUNG_MAX_COMANDA], num_fis[LUNG_MAX_COMANDA];
	int exista = 0, bin = 0;
	FILE *imag = NULL;
	// Se citeste linie cu linie cate o comanda
	while (fgets(cmd, LUNG_MAX_COMANDA, stdin)) {
		if (strstr(cmd, LOAD)) {
			// Daca comanda ce contine subsirul "LOAD" este invalida, se
			// afiseaza mesajul de eroare.
			if (!verif_load(cmd, "LOAD")) {
				printf("Invalid command\n");
			} else {
				// Daca se afla deja un fisier incarcat in memorie
				//  acesta se elibereaza.
				eliberare_fis_existent(&img, &img_b, cmd, num_fis, exista, bin
				, imag, &sel, &sel_b);
				// Se deschide initial fisierul in format "rt" pana se afla
				// tipul acestuia, apoi se incarcac in memorie imaginea cu
				// tipul aferent prin intermediul functiilor "load_ascii\bin".
				imag = fopen(num_fis, "rt");
				if (!imag) {
					exista = 0;
					printf("Failed to load %s\n", num_fis);
				} else {
					printf("Loaded %s\n", num_fis);
					exista = 1;
					fscanf(imag, "%s", img.tip);
					if (!strcmp(img.tip, P2_TIP) || !strcmp(img.tip, P3_TIP))
						load_ascii(&img, &sel, imag, &bin);
					if (!strcmp(img.tip, "P5") || !strcmp(img.tip, "P6")) {
						fclose(imag);
						imag = fopen(num_fis, "rb");
						verif_fisier(imag);
						load_bin(&img_b, &sel_b, imag, &bin, &img);
					}
				}
			}
		} else if (strstr(cmd, SELECT)) {
			if (!verif_select(cmd, SELECT))
				printf("Invalid command\n");
			else if (verif_select(cmd, SELECT) == 1)
				select_tot_cmd(&img, &img_b, cmd, bin, &sel, &sel_b, exista);
			else if (verif_select(cmd, SELECT) == 2)
				select_coord_cmd(&img, &img_b, cmd, bin, &sel, &sel_b, exista);
		} else if (strstr(cmd, HISTOGRAM)) {
			if (!exista) {
				printf("No image loaded\n");
			} else {
				if (!verif_histogram(cmd, HISTOGRAM))
					printf("Invalid command\n");
				else
					histogram_cmd(&img, &img_b, bin, cmd);
			}
		} else if (strstr(cmd, EQUALIZE)) {
			egalizare_cmd(&img, &img_b, cmd, bin, exista);
		} else if (strstr(cmd, CROP)) {
			crop_cmd(&img, &img_b, &sel, &sel_b, cmd, exista, bin);
		} else if (strstr(cmd, APPLY)) {
			apply_cmd(&img, &img_b, &sel, &sel_b, bin, cmd, exista);
		} else if (strstr(cmd, EXIT)) {
			// Functia returneaza 1 daca exista un fisier incarcat in memorie.
			// Daca nu exista returneaza 2, iar daca nu este valida comanda
			// returneaza 0 si afiseaza mesajul sugestiv.
			int ok = exit_cmd(bin, &img_b, &img, cmd, exista, &sel, &sel_b
			, &imag);
			if (ok == 1 || ok == 2)
				return 0;
		} else if (strstr(cmd, SAVE)) {
			save_cmd(&img, &img_b, cmd, exista);
		} else if (strstr(cmd, ROTATE)) {
			rotate_cmd(&img, &img_b, &sel, &sel_b, bin, cmd, exista);
		} else if (cmd[0] != '\n') {
			printf("Invalid command\n");
		}
	}
	return 0;
}
