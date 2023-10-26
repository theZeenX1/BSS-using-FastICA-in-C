#include <stdio.h>
#include <math.h>
#include "headers.h"
#include "definitions.h"

void audio_test()
{
	const int M = 9, N = 0;

	char* load_data_path = "logs\\py output";
	char* op_sav_dat = "logs\\algo output";
	char* op_file = "output";

	int fs;
	mat input_signal = load_wav_data(M, &N, load_data_path);
	if (input_signal == NULL)
	{
		printf("COULDN'T READ THE FILES\n");
		return;
	}

	mat W = zeros(M, M);
	ENDL;
	mat output_signal = fastICA(input_signal, W, 200, M, N);
	ENDL;
	write_data(output_signal, op_sav_dat, op_file, M, N, 1);
	mat_free(W, M);
	mat_free(output_signal, M);
	mat_free(input_signal, M);
	/*
	for (int i = 0; i < M; ++i)
	{
		free(meta[i]);
	}
	free(meta); // meta data values
	*/
}
