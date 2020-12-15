// wengwengweng

#include <stdio.h>
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

typedef struct {
	uint16_t width;
	uint16_t height;
	uint8_t num_frames;
	uint8_t num_anims;
	uint8_t *pixels;
} d_img;

int main(int argc, char **argv) {

	if (argc < 3) {
		fprintf(stderr, "nope\n");
		return 0;
	}

	int w, h;
	unsigned char *pixels = stbi_load(argv[1], &w, &h, NULL, 4);

	d_img img = (d_img) {
		.width = w,
		.height = h,
		.num_frames = 1,
		.num_anims = 0,
		.pixels = pixels,
	};

	int header_size =
		sizeof(uint16_t) // width
		+ sizeof(uint16_t) // height
		+ sizeof(uint8_t) // num_frames
		+ sizeof(uint8_t) // num_anims
		;

	FILE *f = fopen(argv[2], "wb");
	fwrite(&img, header_size, 1, f);
	fwrite(img.pixels, sizeof(uint8_t), w * h * 4, f);
	fclose(f);

	printf("yep\n");

	return 0;

}

