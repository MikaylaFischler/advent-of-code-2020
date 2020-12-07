#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

#include "main.h"

int main(int argc, char** argv) {
    printf(WHITE "x------------------------------------------------x\n" RESET);
    printf(WHITE "|           " BLUE "2020 " B_BLUE "advent of code" BLUE " day 01" WHITE "           |\n" RESET);
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

	uint8_t i = 0;
	uint16_t values[200];
	uint32_t sol_p1 = UINT32_MAX;
	uint32_t sol_p2 = UINT32_MAX;

	while ((num_read = getline(&line, &len, fp)) != -1) {
		// read in value
		values[i++] = atoi(line);
	}

	for (i = 0; i < 200; i++) {
		for (uint8_t j = 0; j < 200; j++) {
			if (values[i] + values[j] == 2020) {
				sol_p1 = values[i] * values[j];
				break;
			}
		}

		if (sol_p1 != UINT32_MAX) { break; }
	}

	for (i = 0; i < 200; i++) {
		for (uint8_t j = 0; j < 200; j++) {
			for (uint8_t k = 0; k < 200; k++) {
				if (values[i] + values[j] + values[k] == 2020) {
					sol_p2 = values[i] * values[j] * values[k];
					break;
				}
			}

			if (sol_p2 != UINT32_MAX) { break; }

		}

		if (sol_p2 != UINT32_MAX) { break; }
	}

	time_end = clock();

    printf(GREEN "done.\n" RESET);

	printf(B_WHITE "\ntotal time taken" WHITE "\t\t: " RED "%f" WHITE " seconds\n" RESET, (double) (time_end - time_start) / CLOCKS_PER_SEC);
	printf(B_RED "[" MAGENTA "part 1" B_RED "] " B_WHITE "2 sum product" WHITE "\t\t: " CYAN "%d\n" RESET, sol_p1);
	printf(B_RED "[" MAGENTA "part 2" B_RED "] " B_WHITE "3 sum product" WHITE "\t\t: " CYAN "%u\n" RESET, sol_p2);

	// free up memory
	fclose(fp);
	if (line) { free(line); }

	return 0;
}
