#include <stdio.h>
#include <math.h>
#include "headers.h"
#include "definitions.h"

int main()
{
	printf("WAVEFORM TEST:\n");
	waveform_test();
	ENDL;

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	printf("AUDIO TEST:\n");
	audio_test();
	ENDL;

	return 0;
}