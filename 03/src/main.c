#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

#include "main.h"

uint16_t test_slope(uint8_t map[][31], uint8_t stride_c, uint8_t stride_r) {
	uint16_t tree_count = 0;
	uint16_t r = 0;
	uint16_t c = 0;

	while (r < 323)
	{
		tree_count += map[r][c % 31];
		c += stride_c;
		r += stride_r;
	}

	return tree_count;
}

int main(int argc, char** argv) {
    printf(WHITE "x------------------------------------------------x\n" RESET);
    printf(WHITE "|           " BLUE "2020 " B_BLUE "advent of code" BLUE " day 03" WHITE "           |\n" RESET);
    printf(WHITE "x------------------------------------------------x\n\n" RESET);

	// file i/o variables
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
	int num_read = 0;

	// open file
    fp = fopen("./input.txt", "r");
    if (fp == NULL) { return -1; }

	// timing
	clock_t time_start, time_end;

	printf(YELLOW "starting...\n" RESET);

	time_start = clock();

	uint8_t map[323][31];
	uint16_t r = 0;

	while ((num_read = getline(&line, &len, fp)) != -1) {
		// do something
		for (uint8_t c = 0; c < 31; c++) { // ...c++ would make this easier
			map[r][c] = line[c] == '#';
		}
		r++;
	}

	uint16_t p1_count = test_slope(map, 3, 1);

	uint64_t p2_count = test_slope(map, 1, 1);
	p2_count *= p1_count;
	p2_count *= test_slope(map, 5, 1);
	p2_count *= test_slope(map, 7, 1);
	p2_count *= test_slope(map, 1, 2);

	time_end = clock();

    printf(GREEN "done.\n" RESET);

	printf(B_WHITE "\ntotal time taken" WHITE "\t: " RED "%f" WHITE " seconds\n" RESET, (double) (time_end - time_start) / CLOCKS_PER_SEC);
	printf(B_RED "[" MAGENTA "part 1" B_RED "] " B_WHITE "tree count" WHITE "\t: " CYAN "%u\n" RESET, p1_count);
	printf(B_RED "[" MAGENTA "part 2" B_RED "] " B_WHITE "tree count" WHITE "\t: " CYAN "%lu\n" RESET, p2_count);

	// free up memory
	fclose(fp);
	if (line) { free(line); }

	return 0;
}
