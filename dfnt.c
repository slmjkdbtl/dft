// wengwengweng

#include <stdio.h>
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#define ASCII_CHARS " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

#define HEADER_SIZE \
	sizeof(uint8_t) \
	+ sizeof(uint8_t) \
	+ sizeof(uint8_t) \
	+ sizeof(uint8_t) \
	+ sizeof(char) * 128 \

typedef struct {
	uint8_t gw;
	uint8_t gh;
	uint8_t cols;
	uint8_t rows;
	char chars[128];
	uint8_t *pixels;
} d_fnt_bin;

int main(int argc, char **argv) {

	if (argc < 5) {
		fprintf(stderr, "nope\n");
		return 0;
	}

	int w, h;
	unsigned char *pixels = stbi_load(argv[1], &w, &h, NULL, 4);
	uint8_t *map = malloc(sizeof(uint8_t) * w * h);

	uint8_t gw = atoi(argv[3]);
	uint8_t gh = atoi(argv[4]);
	uint8_t cols = w / gw;
	uint8_t rows = h / gh;

	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int i = y * w + x;
			if (pixels[i * 4 + 3] > 0) {
				map[i] = 1;
			} else {
				map[i] = 0;
			}
		}
	}

	d_fnt_bin fnt = (d_fnt_bin) {
		.gw = gw,
		.gh = gh,
		.cols = cols,
		.rows = rows,
		.chars = ASCII_CHARS,
		.pixels = map,
	};

	if (cols * rows != strlen(fnt.chars)) {
		fprintf(stderr, "nope\n");
	}

	FILE *f = fopen(argv[2], "wb");
	fwrite(&fnt, HEADER_SIZE, 1, f);
	fwrite(map, sizeof(uint8_t), w * h, f);
	fclose(f);

	printf("yep\n");

	return 0;

}

