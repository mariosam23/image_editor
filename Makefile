#Sampetru Mario 311 CA

CC=gcc
CFLAGS=-Wall -Wextra

COMPILE=image_editor.c generale_f.c load_f.c select_f.c exit_f.c apply_f.c
FILES=histogram_f.c crop_f.c equalize_f.c save_f.c rotate_f.c
build:
	$(CC) $(CFLAGS) $(COMPILE) $(FILES) -lm -o image_editor
clean:
	rm -f image_editor
