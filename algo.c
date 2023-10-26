#include <stdio.h>
#include <math.h>
#include "definitions.h"
#include "headers.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
mat one_unit(mat X, mat wp, int m, int n);
mat othogonalize(mat W, mat wp, int I, int m);
mat g(mat X, int n);
dd dg(mat X, int n);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

mat fastICA(mat input_signal, mat unmixing_matrix, int ITER, int m, int n)
{
	mat X = whiten(input_signal, m, n);

	mat W = zeros(m, m);
	int i;
	for (i = 0; i < m; ++i)
	{
		mat wp = ones(1, m);
		int cnt = 0;
		while (cnt < ITER)
		{
			mat wp1 = one_unit(X, wp, m, n);
			transfer_values(wp1, wp, 1, m);
			mat_free(wp1, 1);

			if (i > 0)
			{
				mat wp1 = othogonalize(W, wp, i, m);
				transfer_values(wp1, wp, 1, m);
				mat_free(wp1, 1);
			}

			norm(wp, 1, m);

			++cnt;
		}
		int j;
		for (j = 0; j < m; ++j)
		{
			W[i][j] = wp[0][j];
		}
		mat_free(wp, 1);
		printf("component #%02d done\n", i);
	}
	transfer_values(W, unmixing_matrix, m, m);
	mat_free(W, m);

	mat srcs = matrix_multiply(unmixing_matrix, X, m, m, n);
	mat_free(X, m);
	return srcs;
}

mat one_unit(mat X, mat wp, int m, int n)
{
	// wp <- E{X * g(wp * X).T} - E{dg(wp * X)} * wp
	mat para = matrix_multiply(wp, X, 1, m, n);

	//E1:
	mat g_ = g(para, n);
	mat gt = transpose(g_, 1, n);
	mat_free(g_, 1);
	mat E1_T = matrix_multiply(X, gt, m, n, 1);
	mat E1 = transpose(E1_T, m, 1);
	mat_free(E1_T, m);
	mat_free(gt, n);

	//E2:
	dd dg_ = dg(para, n);
	mat E2 = matrix_scalar_multiply(wp, dg_, 1, m);
	mat_free(para, 1);

	mat wp1 = matrix_subtract(E1, E2, 1, m);
	mat_free(E1, 1);
	mat_free(E2, 1);
	return wp1;
}

mat othogonalize(mat W, mat wp, int I, int m)
{
	mat t = zeros(I, m);
	transfer_values(W, t, I, m);
	mat tt = transpose(t, I, m);

	mat t1 = matrix_multiply(wp, tt, 1, m, I);
	mat_free(tt, m);
	mat t2 = matrix_multiply(t1, t, 1, I, m);
	mat_free(t, I);
	mat_free(t1, 1);

	mat wp1 = matrix_subtract(wp, t2, 1, m);
	mat_free(t2, 1);

	return wp1;
}

mat g(mat X, int n)
{
	mat A = zeros(1, n);
	int i;
	for (i = 0; i < n; ++i)
	{
		A[0][i] = tanh(X[0][i]);
	}
	return A;
}

dd dg(mat X, int n)
{
	dd A = 0.0;
	int i;
	for (i = 0; i < n; ++i)
	{
		A += 1.0 - pow(tanh(X[0][i]), 2.0);
	}
	return A / (dd)n;
}