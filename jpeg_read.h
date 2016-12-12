#ifndef JPEG_READ_H
#define JPEG_READ_H
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct jpegobj{
  int image_width;
  int image_height;
  int image_components;
  int image_color_space;
	int quant_nums;
	int coef_array_shape[4][2];
  double *quant_tables;  // n*dctsize*dctsize
  double **coef_arrays; // num_component * each dimension size
} jpegobj;

jpegobj read_jpeg(const char *);

void freeJpegObj(jpegobj obj);

#ifdef __cplusplus
}
#endif

#endif
