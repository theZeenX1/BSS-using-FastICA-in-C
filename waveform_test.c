#include <stdio.h>
#include <math.h>
#include "headers.h"
#include "definitions.h"

void waveform_test()
{

	const int M = 3, N = (int)1e2;
	mat actual_signal = zeros(M, N);
	mat input_signal = zeros(M, N);
	mat mixing_matrix = ones(M, M);

	dd alpha = 0.3;

	int i, j;
	for (j = 0; j < N; ++j)
	{
		actual_signal[0][j] = signum(cos(0.3 * j));
		actual_signal[1][j] = sin(0.2 * j);
		actual_signal[2][j] = (j * 0.1) - floor(j * 0.1);
	}

	dd MM[][3] = {
		{1, 1, 1},
		{0.5, 2, 1},
		{1.5, 1, 2}
	};
	for (i = 0; i < M; ++i)
	{
		for (j = 0; j < M; ++j)
		{
			mixing_matrix[i][j] = MM[i][j];
		}
	}

	input_signal = matrix_multiply(mixing_matrix, actual_signal, M, M, N);

	printf("INPUT:\n");
	//print_mat(input_signal, M, N);
	ENDL;

	mat W = zeros(M, M);
	mat output_signal = fastICA(input_signal, W, 200, M, N);
	ENDL;
	printf("OUTPUT:\n");
	//print_mat(output_signal, M, N);

	char* ip_data_path = "logs\\test";
	char* op_data_path = "logs\\test";

	write_data(actual_signal, ip_data_path, "actual_signal", M, N, 0);
	write_data(output_signal, op_data_path, "output_signal", M, N, 0);

	mat_free(W, M);
	mat_free(output_signal, M);
	mat_free(mixing_matrix, M);
	mat_free(input_signal, M);
	mat_free(actual_signal, M);
}
