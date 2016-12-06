#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]) {

	// This is ORIGINAL
	// title + 34 rows
	int a1[34], b1[34];
	float result1[34];

	// This is TARGET
	// title + 34 rows
	int a2[34], b2[34];
	float result2[34];

	char *ORIGINAL, *TARGET;

	if (argc == 1) {
		printf("Use default setting...\nORIGINAL = out1.txt\nTARGET = out2.txt\n");
		ORIGINAL = "out1.txt";
		TARGET = "out2.txt";
	}
	else if (argc == 3) {
		ORIGINAL = argv[1];
		TARGET = argv[2];
	}
	else {
		printf("Input error. You need to input three arguments.\n./ProgramName ORIGINAL TARGET\n");
		exit(1);
	}

	// define the relative error as threshold value
	const float relativeTolerance = 1e-6;

	FILE *fp_r1 = fopen(ORIGINAL, "r");
	FILE *fp_r2 = fopen(TARGET, "r");

	if (fp_r1 == NULL) {
		printf("Miss original file error.\n");
		exit(1);
	}

	if (fp_r2 == NULL) {
		printf("Miss target cuda generate file error.\n");
		exit(1);
	}

	char line[50];
	const char s[2] = ", ";
	char *token;
	int i;         // count column number
	int j = 0;     // count network number

	fgets(line, 50, fp_r1);           // First line is title.

	// Use while loop to load the file into memory
	while(fgets(line, 50, fp_r1)) {
		token = strtok(line, s);
		
		for (i = 0; i < 3; i++) {
			if (i == 0) {
				a1[j] = atoi(token);
				token = strtok(NULL, s);
			}
			else if (i == 1) {
				b1[j] = atoi(token);
				token = strtok(NULL, s);
			}
			else {
				result1[j] = atof(token);
			}
		}

		j++;
	}

	fclose(fp_r1);

	j = 0;     // reset j
	char line2[50];
	char *token2;

	fgets(line2, 50, fp_r2);           // First line is title.

	// Use while loop to load the file into memory
	while(fgets(line2, 50, fp_r2)) {
		token2 = strtok(line2, s);

		for (i = 0; i < 3; i++) {
			if (i == 0) {
				a2[j] = atoi(token2);
				token2 = strtok(NULL, s);
			}
			else if (i == 1) {
				b2[j] = atoi(token2);
				token2 = strtok(NULL, s);
			}
			else {
				result2[j] = atof(token2);
			}
		}

		j++;
	}

	fclose(fp_r2);

	int count;
	float sum = 0.f;

	for (count = 0; count < 34; count++) {
		if ((a1[count] != a2[count]) || (b1[count] != b2[count])) {
			printf("Counting error in %d .\n", count);
			exit(1);
		}

		else {
			float diff = fabs((result1[count] - result2[count]) / result1[count]);
			sum += diff;

			if (diff > relativeTolerance) {
				printf("Subtraction error in %d .\n", count);
				exit(1);
			}

			if (sum > relativeTolerance) {
				printf("Relative error in %d .\n", count);
				exit(1);
			}
		}
		
	}

	printf("TEST PASSED.\n");
	return 0;
}
