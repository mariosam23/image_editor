#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generale_f.h"

#define EXIT "EXIT"

// Se elibereaza resursele alocate in functie de tipul imaginii :
// binar/ascii sau se afiseaza eventualele erori.
int exit_cmd(int bin, img_b_t *img_b, img_t *img, char op[], int exista
, select_t *sel, select_b_t *sel_b, FILE **imag)
{
	if (!bin && verif_op_un_cuv(op, EXIT)) {
		if (exista == 1) {
			fclose(*imag);

			eliberare_select_ascii(sel);

			eliberare(img);
			return 1;
		} else if (!exista) {
			printf("No image loaded\n");

			return 2;
		}
	}

	if (verif_op_un_cuv(op, EXIT)) {
		if (exista == 1) {
			fclose(*imag);

			eliberare_select_b(sel_b);

			eliberare_bin(img_b);
			return 1;
		}
		if (exista == 0) {
			printf("No image loaded\n");

			return 2;
		}
	}

	printf("Invalid command\n");
	return 0;
}
