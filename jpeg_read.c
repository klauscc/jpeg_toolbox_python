#include "jpeg_read.h"
#include <stdlib.h>

jpegobj read_jpeg(const char *image)
{  

	jpegobj obj;
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  jpeg_component_info *compptr;
  jvirt_barray_ptr *coef_arrays;
  jpeg_saved_marker_ptr marker_ptr;
  FILE *infile;
  JDIMENSION blk_x,blk_y;
  JBLOCKARRAY buffer;
  JCOEFPTR bufptr;
  JQUANT_TBL *quant_ptr;
  JHUFF_TBL *huff_ptr;
  int strlen, c_width, c_height, ci, i, j, n, dims[2];

	infile = fopen(image, "rb");
	cinfo.err = jpeg_std_error(&jerr);

  /* initialize JPEG decompression object */
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);

  /* save contents of markers */
  jpeg_save_markers(&cinfo, JPEG_COM, 0xFFFF);

  /* read header and coefficients */
	(void) jpeg_read_header(&cinfo, TRUE);
 
  /* for some reason out_color_components isn't being set by
     jpeg_read_header, so we will infer it from out_color_space: */
  switch (cinfo.out_color_space) {
    case JCS_GRAYSCALE:
      cinfo.out_color_components = 1;
      break;
    case JCS_RGB:
      cinfo.out_color_components = 3;
      break;
    case JCS_YCbCr:
      cinfo.out_color_components = 3;
      break;
    case JCS_CMYK:
      cinfo.out_color_components = 4;
      break;
    case JCS_YCCK:
      cinfo.out_color_components = 4;
      break;
  }

	obj.image_width = cinfo.image_width;
	obj.image_height = cinfo.image_height;
	obj.image_components = cinfo.out_color_components;
	obj.image_color_space = cinfo.out_color_space;

	/* copy the quantization tables*/
  for (n = 0; n < NUM_QUANT_TBLS && cinfo.quant_tbl_ptrs[n] != NULL; n++) {}
	int num_quantable = n;
	obj.quant_nums = num_quantable;
	obj.quant_tables = malloc(sizeof(double)*num_quantable*DCTSIZE*DCTSIZE);
  for (n = 0; n < num_quantable; n++) {
      quant_ptr = cinfo.quant_tbl_ptrs[n];
      for (i = 0; i < DCTSIZE; i++) 
        for (j = 0; j < DCTSIZE; j++)
          obj.quant_tables[n*DCTSIZE*DCTSIZE+i*DCTSIZE+j] = (double) quant_ptr->quantval[i*DCTSIZE+j];
	}

  /* creation and population of the DCT coefficient arrays */
	obj.coef_arrays = malloc(sizeof(double *)*cinfo.num_components);

	/* copy coefficients from virtual block arrays */
	double *coef_ci;
  coef_arrays = jpeg_read_coefficients(&cinfo);
  for (ci = 0; ci < cinfo.num_components; ci++) {
    compptr = cinfo.comp_info + ci;
    c_height = compptr->height_in_blocks * DCTSIZE;
    c_width = compptr->width_in_blocks * DCTSIZE;
		/*malloc array of ci component*/
		obj.coef_array_shape[ci][0] = c_height;
		obj.coef_array_shape[ci][1] = c_width;
		obj.coef_arrays[ci]= malloc((size_t)sizeof(double)*c_height * c_width);
		coef_ci = obj.coef_arrays[ci];


    /* copy coefficients from virtual block arrays */
		for (blk_y = 0; blk_y < compptr->height_in_blocks; blk_y++) {
			buffer = (cinfo.mem->access_virt_barray)((j_common_ptr) &cinfo, coef_arrays[ci], blk_y, 1, FALSE);
			for (blk_x = 0; blk_x < compptr->width_in_blocks; blk_x++) {
				bufptr = buffer[0][blk_x];
        for (i = 0; i < DCTSIZE; i++)        /* for each row in block */
          for (j = 0; j < DCTSIZE; j++)      /* for each column in block */
						coef_ci[(blk_y*DCTSIZE+i)*c_width+blk_x*DCTSIZE+j] = (double) bufptr[i*DCTSIZE+j];
      }
		}
	}

  /* done with cinfo */
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  /* close input file */
  fclose(infile);
	return obj;
}

void freeJpegObj(jpegobj obj)
{
    free(obj.quant_tables);
    double *coef;
    int ci;
    int num_components = obj.image_components;
    for (ci = 0; ci < num_components; ci++) {
        coef = obj.coef_arrays[ci];
        free(coef);
    }
    free(obj.coef_arrays);
}
