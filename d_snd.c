// wengwengweng

#include <stdio.h>
#include <stdint.h>
#include <stb_vorbis.c>

typedef struct {
	uint32_t num_frames;
	int16_t *frames;
} d_snd;

int main(int argc, char **argv) {

	if (argc < 3) {
		fprintf(stderr, "nope\n");
		return 0;
	}

	int channels;
	int sample_rate;
	short *frames;
	int num_frames = stb_vorbis_decode_filename(argv[1], &channels, &sample_rate, &frames);
	int num_frames_mono = num_frames / channels;
	short *frames_mono = malloc(sizeof(short) * num_frames_mono);

	for (int i = 0; i < num_frames_mono; i++) {
		int frame = 0;
		for (int j = 0; j < channels; j++) {
			frame += frames[i * channels + j];
		}
		frames_mono[i] = frame / channels;
	}

	free(frames);

	d_snd snd = (d_snd) {
		.frames = frames_mono,
		.num_frames = num_frames_mono,
	};

	int header_size =
		sizeof(uint32_t) // num_frames
		;

	FILE *f = fopen(argv[2], "wb");
	fwrite(&snd, header_size, 1, f);
	fwrite(snd.frames, sizeof(int16_t), snd.num_frames, f);
	fclose(f);

	printf("yep\n");

	return 0;

}

