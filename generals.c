#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "definitions.h"
#include "headers.h"

int signum(dd X)
{
	if (X > 0) return 1;
	if (X < 0) return -1;
	return 0;
}

void transfer_values(mat from, mat to, int m, int n)
{
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			to[i][j] = from[i][j];
		}
	}
}

void gsl_mat_to_mat(gsl_matrix* gsl_mat, mat A, int m, int n) {
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			A[i][j] = gsl_matrix_get(gsl_mat, i, j);
		}
	}
}

void gsl_vec_to_mat(gsl_vector* gsl_vec, mat A, int m) {
	int i;
	for (i = 0; i < m; ++i)
	{
		A[0][i] = gsl_vector_get(gsl_vec, i);
	}
}

void mat_to_gsl_mat(mat A, gsl_matrix* gsl_mat, int m, int n) {
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			gsl_matrix_set(gsl_mat, i, j, A[i][j]);
		}
	}
}

void write_data(mat X, char* path_to_dir, char* file_name, int m, int n, int flag)
{
	char cwd[512];
	getcwd(cwd, 512);

	char filename[1024];
	sprintf(filename, "%s\\%s\\%s.txt", cwd, path_to_dir, file_name);

	FILE* file = fopen(filename, "wb");
	if (file == NULL)
	{
		printf("FILE COULDN'T BE CREATED\n");
		return;
	}
	printf("Writing file: %s", filename);
	ENDL;
	int i, j;
	for (i = 0; i < m; ++i)
	{
		if(flag == 1) fprintf(file, "COMPONENT #%02d", i + 1);
		fprintf(file, "[ ");
		for (j = 0; j < n; ++j)
		{
			if(j == n - 1) fprintf(file, "%f", X[i][j]);
			else fprintf(file, "%f, ", X[i][j]);
		}
		fprintf(file, " ]");
		if (i != m - 1) fprintf(file, ",");
		fprintf(file, "\n");
	}
}
