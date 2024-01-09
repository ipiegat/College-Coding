#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n)
{
	//Fill in code below
	//When deciding which way to go for the next step, generate a random number as follows.
	int x = 0;
	int y = 0;
	int sum = 0;
	double fraction = 0.0;
	int r;
	int visited[2*n-1][2*n-1];

    // initialize array with all 0s
	for (int i = 0; i < (2*n-1); i++) {
		for (int j = 0; j < (2*n-1); j++) {
			visited[i][j] = 0;
		}
	}

	// while x, y do not hit edge, move and save position as 1
	while ((x > -n && x < n) && (y > -n && y < n)) {
		visited[x+n-1][y+n-1] = 1;
		r = rand() % 4;
		switch (r) {
			case 0:
				y += 1;
				break;
			case 1:
				x += 1;
				break;
			case 2:
				y -= 1;
				break;
			case 3:
				x -= 1;
				break;
		}
	}
    // go through array and sum all the 1s
	for (int i = 0; i < (2*n-1); i++) {
		for (int j = 0; j < (2*n-1); j++) {
			sum += visited[i][j];
		}
	}
	
    // visited area divided by square area
	fraction = sum/((2*n-1)*(2*n-1)*1.0);

	return fraction; 
}

//Do not change the code below
int main(int argc, char* argv[])
{
	int trials = 1000;
	int i, n, seed;
	if (argc == 2) seed = atoi(argv[1]);
	else seed = 12345;

	srand(seed);
	for(n=1; n<=64; n*=2)
	{	
		double sum = 0.;
		for(i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	return 0;
}
