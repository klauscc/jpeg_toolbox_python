#include <stdio.h>
#include "jpeg_read.h"

void main(int argc, const char* argv[])
{
	const char *image = "../demo.jpg";
	printf("%s\n",image);
  jpegobj obj = read_jpeg(image);
	printf("image_width: %d\n image_height: %d\n", obj.image_width, obj.image_height );

	int i,j,k;

	//print coef_array
	for (i = 0; i != obj.quant_nums; ++i){
		printf("quantable %d:\n",i);
		for (j=0;j !=8; ++j){
			for (k=0;k!=8;++k){
				printf("%f ",obj.quant_tables[i*64 + j*8 + k]);
			}
			printf("\n");
		}
	}

	double *coef_ci;
	for (i = 0; i != obj.image_components; ++i){
		printf("coef %d:\n",i);
		coef_ci = obj.coef_arrays[i];
		for (j=64;j != 80; ++j){
			for (k=64;k!=80;++k){
				printf("%-5.0f ",coef_ci[j*obj.coef_array_shape[i][1]+k]);
			}
			printf("\n");
		}
	}

    freeJpegObj(obj);
	
}
