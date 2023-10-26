#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifndef dd
#define dd double
#endif

#ifndef ENDL
#define ENDL printf("\n")
#endif // !ENDL


#ifndef mat
#define mat double **
#endif

#include "headers.h"
#include <stdint.h>

/*~~~~~~~~~~~~~~ALGO~~~~~~~~~~~~~~~~~~*/
mat fastICA(mat input_signal, mat unmixing_matrix, int ITER, int m, int n);

/*~~~~~~~~~~~~~AUDIO~~~~~~~~~~~~~~~~~~~*/
/*
typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;			// sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;
typedef struct header_file* header_p;
header_p* meta;
*/

mat load_wav_data(int n_sources, int* size, char* pathname);



/*~~~~~~~~~~~~LINALG~~~~~~~~~~~~~~~~~~*/
void center(mat A, int m, int n);
void norm(mat A, int m, int n);
mat cov_matrix(mat A, int m, int n);
mat whiten(mat X, int m, int n);


/*~~~~~~~~~~~~~~MATRIX~~~~~~~~~~~~~~~*/
mat zeros(int m, int n);
mat ones(int m, int n);
mat mat_alloc(int m, int n);
void mat_free(mat A, int m);
mat matrix_subtract(mat A, mat B, int m, int n);
mat matrix_multiply(mat A, mat B, int M, int c, int N);
mat matrix_add(mat A, mat B, int m, int n);
mat matrix_scalar_multiply(mat A, dd alpha, int m, int n);
mat transpose(mat A, int m, int n);
mat diag(mat d, int m);
void print_mat(mat matrix, int m, int n);


/*~~~~~~~~~~~~~GENERALS~~~~~~~~~~~~~~~*/
void transfer_values(mat from, mat to, int m, int n);
void gsl_mat_to_mat(gsl_matrix* gsl_mat, mat A, int m, int n);
void gsl_vec_to_mat(gsl_vector* gsl_vec, mat A, int m);
void mat_to_gsl_mat(mat A, gsl_matrix* gsl_mat, int m, int n);
int signum(dd X);
void write_data(mat X, char* path_to_dir, char* file_name, int m, int n, int flag);

/*~~~~~~~~~~~~~~~~TEST~~~~~~~~~~~~~~~~~*/
void waveform_test();

/*~~~~~~~~~~~~~RUN_ALGO~~~~~~~~~~~~~~~~*/
void audio_test();

#endif
