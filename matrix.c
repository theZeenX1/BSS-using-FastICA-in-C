#include <stdio.h>
#include "definitions.h"
#include "headers.h"

mat diag(mat d, int m)
{
	mat D = zeros(m, m);
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < m; ++j)
		{
			D[i][j] = (i == j) ? d[0][j] : 0;
		}
	}
	return D;
}

mat transpose(mat A, int m, int n)
{
	mat AT = zeros(n, m);
	int i, j;
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < m; ++j)
		{
			AT[i][j] = A[j][i];
		}
	}
	return AT;
}

mat matrix_scalar_multiply(mat A, dd alpha, int m, int n)
{
	mat B = ones(m, n);
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			B[i][j] = alpha * A[i][j];
		}
	}
	return B;
}

mat matrix_add(mat A, mat B, int m, int n)
{
	mat C = zeros(m, n);
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	return C;
}

mat matrix_multiply(mat A, mat B, int M, int c, int N)
{
	mat C = zeros(M, N);
	int i, j, k;
	for (i = 0; i < M; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			dd sum = 0.0;
			for (k = 0; k < c; ++k)
			{
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
		}
	}
	return C;
}

mat matrix_subtract(mat A, mat B, int m, int n)
{
	mat C = zeros(m, n);
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
	return C;
}

mat zeros(int m, int n)
{
	mat A = mat_alloc(m, n);
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			A[i][j] = 0.0;
		}
	}
	return A;
}

mat ones(int m, int n)
{
	mat A = mat_alloc(m, n);
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			A[i][j] = 1.0;
		}
	}
	return A;
}

void print_mat(mat matrix, int m, int n) {
	printf("[\n");
	int i, j;
	for (i = 0; i < m; ++i)
	{
		printf("COMPONENT #%02d:\n", i);
		printf("[ ");
		for (j = 0; j < n; ++j)
		{
			printf("%g", matrix[i][j]);
			if (j == n - 1) printf(" ");
			else printf(", ");
		}
		if (i == m - 1) printf("]\n");
		else printf("],\n");
	}
	printf("]\n");
}

mat mat_alloc(int m, int n)
{
	mat A = malloc(sizeof(dd*) * m);
	int i;
	for (i = 0; i < m; ++i) {
		A[i] = malloc(sizeof(dd) * n);
	}
	return A;
}

void mat_free(mat A, int m)
{
	int i;
	for (i = 0; i < m; ++i)
	{
		free(A[i]);
	}
	free(A);
}