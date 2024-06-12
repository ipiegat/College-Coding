#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h> 

//write an integer to a pipe
void write_int(int pd, int value)
{
	write(pd, &value, sizeof(int));
}
//read an integer from a pipe
//the function returns the number of bytes read
int read_int(int pd, int *value)
{
	return read(pd, value , sizeof(int));
}

//TODO
//implement the function using binary search
//if v is in array a[], whose length is n, return 1
//otherwise, return 0
int in_array(int a[], int n, int v)
{
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if(v == a[mid]) 
        {
                return 1;
        } else if (v < a[mid]) {
                right = mid - 1; // Search in the left half
        } else {
                left = mid + 1; // Search in the right half
        }
    }
    return 0;
}   

void run_search(int n, int m)
{
        int pd1[2];
        //pipe creation
        if(pipe(pd1) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd2[2];
        //pipe creation
        if(pipe(pd2) < 0)
        {
                perror("Error.");
                exit(-1);
        }
        pid_t childA = fork();
        if(childA == 0)
        {
                //TODO
                //fill in code below
		//note this is process A
                close(pd1[0]);
                close(pd2[1]);

		srand(3100);

                //now generate array A

                int A[n];
                A[0] = rand() % 10 +1;
                for(int i = 1; i < n; i++)
                {
                        A[i] = A[i-1] + rand() % 10 + 1; 
                }

                int v;
                int round = 0;
		//TODO
		//complete the following line of code

                while(read_int(pd2[0], &v)!=0)
                {
                    for(int i = 0; i < n; i++) {
                        write_int(pd1[1], A[i]);
                        round ++;
                    }

			//TODO
			//fill in code below
                }
                close(pd1[0]);
                close(pd1[1]);
                exit(0);
		//TODO
		//fill in code below

        }
	//TODO
	//fill in code below

        int pd3[2];
        //pipe creation
        if(pipe(pd3) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd4[2];
        //pipe creation
        if(pipe(pd4) < 0)
        {
                perror("Error.");
                exit(-1);
        }
        pid_t childB = fork();
        if(childB == 0)
        {
		//fill in code below
		//note this is process B
                close(pd1[0]);
                close(pd1[1]);
                close(pd2[0]);
                close(pd2[1]);
                close(pd3[0]);
                close(pd4[1]);
		srand(3504);

                //now generate array B

                int B[n];
                B[0] = rand() % 10 +1;
                for(int i = 1; i < n; i++)
                {
                        B[i] = B[i-1] + rand() % 10 + 1; 
                }
                int v;
                //TODO
                //complete the following line of code
                while(read_int(pd4[0], &v)!=0)
                {
                        //TODO
                        //fill in code below
                    for(int i = 0; i < n; i++) {
                        write_int(pd3[1], B[i]);
                    }

                }
                close(pd3[1]);
                close(pd4[0]);
                exit(0);


		//fill in code below
	
	}
        //TODO
        //fill in code below

        close(pd1[1]);
        close(pd2[0]);
        close(pd3[1]);
        close(pd4[0]);

	int v1, v2;
        int count = 0;
        for(int i = 0; i < n; i++)
        {
		write_int(pd2[1], 1);
                read_int(pd1[0], &v1);
		write_int(pd4[1], m - v1);
		read_int(pd3[0], &v2);

                if(v2)
                {
                        printf("%d + %d = %d\n", v1, m - v1, m);
                        count ++;
                }
        }
	printf("There are %d pairs that add up to %d.\n", count, m);
	//TODO
	//fill in code below
        close(pd1[0]);
        close(pd2[1]);
        close(pd3[0]);
        close(pd4[1]);

}