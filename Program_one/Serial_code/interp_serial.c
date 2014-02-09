// Joshua Stevens
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

#define FILE_INPUT 0


//// Do not touch this function 
//// This function will be replaced
int input_generator(int n, int dim, double **M)
{
	int i, j;
	// Generating the X points
	for(i=0; i<n; i++){
		M[i][0] =0;
		for(j=0; j<dim-1; j++){
			M[i][j+1] = ((i+1)/(double)n)*(j+1); 
		}
	}
	return 0;
}

int main(int argc, char ** argv)
{
	FILE *fp;
    int i,j,k;
	int points, n;
	double sum;
	double sum_avg; 
	double mul;
	double x;

	int fn, fx;
	double fy;
	double *X, **M;

	struct timeval start_tv, end_tv;

	if (argc != 3){
		printf("Please use the format below to run the program\n");
		printf("interp <filename> <x>\n");
		return 1;
	}
	printf("\nInput File: %s\n", argv[1]);

	/* Opening the input file */
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Error in opening a file: %s", argv[1]);
		return 0;
	}

	x = (double)atof(argv[2]);
	printf("x= %f\n", x);

	/* Reading the maxtrix dimension */
	fscanf(fp, "%d %d\n",&points, &n);
	printf("points = %d, n= %d\n", points, n);

	M = (double**) malloc(n * sizeof(double*));
	for (i= 0; i<n; i++)
		M[i]= (double*) malloc(points * sizeof(double));
	X = (double*) malloc(n * sizeof(double));

	/* Set the X points */
    for(i=0;i<n;i++){
		X[i] = i;
    }
	/* Reading the input points */

#if FILE_INPUT
//    for(i=0;i<(n*points);i++){
//		fscanf(fp, "%d %d %lf\n", &fn, &fx, &fy);
//		Y[fn][fx] = fy;
//    }
#else
	input_generator(n, points, M);
#endif

	gettimeofday(&start_tv, NULL);

	sum_avg = 0;
	/* LOOP #1 */
	for(i=0;i<n;i++)
	{
		sum=0;
		/* LOOP #2 */
		for(j=0;j<points;j++)
		{
			mul =1;
			/* LOOP #3 */
			for(k=0;k<points;k++)
			{
				if(X[j]==X[k])
				continue;
				mul*=((x-X[k])/(X[j]-X[k]));
			}

			sum+=mul*M[i][j];
		}

		sum_avg += sum;
	}

	printf("sum_avg:(%f)=%f\n", x, sum_avg/(double)n);

	gettimeofday(&end_tv, NULL);
	printf("Elapsed time: %f sec\n", 
		(double)( (double)(end_tv.tv_sec - start_tv.tv_sec) + ( (double)(end_tv.tv_usec - start_tv.tv_usec)/1000000)) );

	fclose(fp);
}
