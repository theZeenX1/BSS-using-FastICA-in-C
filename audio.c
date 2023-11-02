#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "definitions.h"
#define RANGE 127   

dd clip(dd X)
{
    if (X > 127.0) return 127.0;
    if (X < -128.0) return -128.0;
    return X;
}

mat load_wav_data(int n_sources, int* size, char* pathname)
{
    int BUFSIZE = 1;
    char cwd[512];
    getcwd(cwd, 512);

    dd** X = (dd**)malloc(sizeof(dd*) * n_sources);

    int ii;
    for (ii = 0; ii < n_sources; ++ii)
    {
        char filename[1024];
        sprintf(filename, "%s\\%s\\input%02d.txt", cwd, pathname, ii);
        int sz;
        FILE *file = fopen(filename, "rb");
        if (file == NULL)
        {
            printf("FILE COULDN'T BE OPENED\n");
            return NULL;
        }
        else
        {
            printf("READING FILE: input%02d.txt\n", ii);
        }

        fread_s(&sz, sizeof(int), sizeof(int), 1, file);
        printf("size of audio file: %d\n", sz);

        X[ii] = (dd*)malloc(sizeof(dd) * sz);
        int comp = 0;
        while (!feof(file))
        {
            comp += fread_s(&X[ii][comp], sizeof(dd), sizeof(dd), 1, file);
        }
        fclose(file);
        ENDL;
        *size = max(*size, sz);
    }

    return X;
}