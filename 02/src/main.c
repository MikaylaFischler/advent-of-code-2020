#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

#include "main.h"

uint8_t count_char(const char* passwd, char c) {
	uint8_t len = strlen(passwd);
	uint8_t count = 0;

	for (uint8_t i = 0; i < len; i++) {
		if (passwd[i] == c) {
			count++;
		}
	}

	return count;
}

uint8_t verify_positions(const char* passwd, char c, uint8_t first, uint8_t second) {
	uint8_t ok = 0;

	if (passwd[first - 1] == c) {
		ok = !ok;
	}
	
	if (passwd[second - 1] == c) {
		ok = !ok;
	}

	return ok;
}

int main(int argc, char** argv) {
    printf(WHITE "x------------------------------------------------x\n" RESET);
    printf(WHITE "|           " BLUE "2020 " B_BLUE "advent of code" BLUE " day 02" WHITE "           |\n" RESET);
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

	uint16_t good_count = 0;
	uint16_t good_count2 = 0;
	char line_copy[40];
	uint8_t min, max;
	char letter;
	char* passwd;

	while ((num_read = getline(&line, &len, fp)) != -1) {
		// why am i doing this
		strcpy(line_copy, line);
		char* token = strtok(line, "-");
		min = atoi(token);

		token = strtok(NULL, "-");
		max = atoi(token);

		strcpy(line, line_copy);

		token = strtok(line, " ");
		token = strtok(NULL, " ");
		letter = token[0];

		passwd = strtok(NULL, " ");

		uint8_t count = count_char(passwd, letter);

		good_count += count >= min && count <= max;
		good_count2 += verify_positions(passwd, letter, min, max);
	}

	time_end = clock();

    printf(GREEN "done.\n" RESET);

	printf(B_WHITE "\ntotal time taken" WHITE "\t: " RED "%f" WHITE " seconds\n" RESET, (double) (time_end - time_start) / CLOCKS_PER_SEC);
	printf(B_RED "[" MAGENTA "part 1" B_RED "] " B_WHITE "good passwords" WHITE "\t: " CYAN "%d\n" RESET, good_count);
	printf(B_RED "[" MAGENTA "part 2" B_RED "] " B_WHITE "good passwords" WHITE "\t: " CYAN "%d\n" RESET, good_count2);

	// free up memory
	fclose(fp);
	if (line) { free(line); }

	return 0;
}