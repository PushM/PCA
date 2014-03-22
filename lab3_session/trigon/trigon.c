
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define N 6000
#define PUNTS 1000

double memoization[PUNTS][2];
double buffer[PUNTS * 2];

int main(int argc, char *argv[])
{
	unsigned int i, r, j, n, index;
	double d;

	// Construct memoization cache
	for (i = 0, d = 0; i < PUNTS; ++i)
	{
		memoization[i][0] = cos(d);
		memoization[i][1] = sin(d);
		d += 2*M_PI/PUNTS;
	}
	
	if (argc == 1) n = N;
	else n = atoi(argv[1]);

	srand(0);
	for (i = 0; i < n; i++) {
		r = rand();
		index = 0;
		for (j = 0; j < PUNTS; j++) {
			buffer[  index  ] = r * memoization[j][0]; // x
			buffer[index + 1] = r * memoization[j][1]; // y
			index += 2;
		}
		fwrite(buffer, sizeof(double), 2 * PUNTS, stdout);
	}
	return 0;
}
