#include <stdio.h>
#include <math.h>
#include "definitions.h"
#include "headers.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void evec_eval(mat A, mat evec_, mat eval_, int m);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


mat whiten(mat X, int m, int n)
{
	center(X, m, n);
	mat evec = zeros(m, m);
	mat eval = zeros(1, m);

	mat X_cov = cov_matrix(X, m, n);
	evec_eval(X_cov, evec, eval, m);
	mat_free(X_cov, m);

	int i;
	for (i = 0; i < m; ++i)
	{
		eval[0][i] = 1.0 / sqrt(eval[0][i] + 1e-5);
	}
	mat D = diag(eval, m);
	mat ET = transpose(evec, m, m);
	mat_free(evec, m);
	mat_free(eval, 1);

	mat K = matrix_multiply(D, ET, m, m, m);
	mat_free(D, m);
	mat_free(ET, m);

	return matrix_multiply(K, X, m, m, n);
}

void evec_eval(mat A, mat evec_, mat eval_, int m)
{
	gsl_vector* eval = gsl_vector_alloc(m);
	gsl_matrix* evec = gsl_matrix_alloc(m, m);
	gsl_matrix* m_ = gsl_matrix_alloc(m, m);
	mat_to_gsl_mat(A, m_, m, m);

	gsl_eigen_symmv_workspace* w = gsl_eigen_symmv_alloc(m);
	gsl_eigen_symmv(m_, eval, evec, w);
	gsl_eigen_symmv_free(w);
	gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_DESC);

	gsl_mat_to_mat(evec, evec_, m, m);
	gsl_vec_to_mat(eval, eval_, m);

	gsl_matrix_free(m_);
	gsl_matrix_free(evec);
	gsl_vector_free(eval);
}

mat cov_matrix(mat A, int m, int n)
{
	mat cov = zeros(m, m);
	int i, j;
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < m; ++j)
		{
			cov[i][j] = cov[j][i] = gsl_stats_covariance(A[i], 1, A[j], 1, n);
		}
	}
	return cov;
}

void center(mat A, int m, int n)
{
	int i, j;
	for (i = 0; i < m; ++i)
	{
		dd sum = 0.0;
		for (j = 0; j < n; ++j)
		{
			sum += A[i][j];
		}
		sum /= (dd)n;
		for (j = 0; j < n; ++j)
		{
			A[i][j] -= sum;
		}
	}
}

void norm(mat A, int m, int n)
{
	int i, j;
	for (i = 0; i < m; ++i)
	{
		dd sum = 0.0;
		for (j = 0; j < n; ++j)
		{
			sum += pow(A[i][j], 2.);
		}
		sum = sqrt(sum + 1e-5);
		for (j = 0; j < n; ++j)
		{
			A[i][j] /= sum;
		}
	}
}
