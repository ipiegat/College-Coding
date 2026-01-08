#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

int coordinates_to_index(int x, int y, int z, int n)
{
    return x+n+(2*n+1)*(y+n) + (2*n+1)*(2*n+1)*(z+n);
}

void one_particle(int *grid, int n)
{
    int x = 0;
    int y = 0;
    int z = 0;
    int r = 0;
    for (int i = 0; i < n; i++){
        r = rand() % 6;
		switch (r) {
			case 0:
				x -= 1;
				break;
			case 1:
				x += 1;
				break;
            case 2:
                z -= 1;
                break;
			case 3:
				z += 1;
				break;
			case 4:
				y -= 1;
				break;
			case 5:
				y += 1;
				break;
		}
    
    }
    //printf("[%d], [%d], [%d]", x, y, z);
    grid[coordinates_to_index(x, y, z, n)] += 1;
    
    //for (int k = 0; k < sizeof(grid); k++) {
      //  grid[coordinates_to_index(x, y, z, n)] += 1;
    //}
    //for (int num = 0; num < sizeof(grid); num++) {
      //  printf("%d", grid[num]);
    //}

}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r)
{
    int inside = 0;
    int outside = 0;
    
    for (int i = 0; i < (2*n+1); i++) {
		for (int j = 0; j < (2*n+1); j++) {
            for (int k = 0; k < (2*n+1); k++) {
			    if ((i-n)*(i-n)+(j-n)*(j-n)+(k-n)*(k-n) <= (r*n)*(r*n)) {
                    inside += grid[coordinates_to_index(i-n, j-n, k-n, n)];
                } else {
                    outside += grid[coordinates_to_index(i-n, j-n, k-n, n)];
                }
		    }
        }
    }
    int total = inside + outside;
    //printf("[%d], [%d]", outside, inside);
    if (total == 0) {
        return 1;
    } else {
        return inside / (double) (inside + outside);
    }


    
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below
    //int grid[2*n+1][2*n+1][2*n+1];
    int *grid = malloc(sizeof(int)*(2*n+1)*(2*n+1)*(2*n+1));

    for (int i = 0; i < (2*n+1); i++) {
		for (int j = 0; j < (2*n+1); j++) {
            for (int k = 0; k < (2*n+1); k++) {
               // printf("[%d], [%d], [%d]", i, j, k);
			    grid[coordinates_to_index(i-n, j-n, k-n, n)] = 0;
		    }
        }
    }

	for(int i = 1; i<=m; i++) one_particle(grid, n);

    //printf("radius density\n");
    //for(double r = 0.0; r<=1.0; r+=0.05) {
      //  double d = 0.0;
        //d = density(grid, n, r);
        //printf("[%.02f], [%.06f]", r, d);
    //}




	print_result(grid, n);
	//fill in some code below
    free(grid);

}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}