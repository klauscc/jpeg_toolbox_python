#include <iostream>
#include <boost/python.hpp>
#include "jpeg_read.h"

namespace bp = boost::python;

static bp::list cArray2List(double *data, int length){
	bp::list l;
	for (int i=0;i!= length;++i)
		l.append(data[i]);
	return l;
}

bp::dict _read_jpeg(const char * image){
	jpegobj obj = read_jpeg(image);
	bp::dict jpegDict;
	int i;

	jpegDict["image_width"] = obj.image_width;
	jpegDict["image_height"] = obj.image_height;
	jpegDict["image_components"] = obj.image_components;
	jpegDict["image_color_space"] = obj.image_color_space;
	bp::list quantable = cArray2List(obj.quant_tables, 64*obj.quant_nums);
	jpegDict["quant_nums"] = obj.quant_nums;
	jpegDict["quant_tables"] = quantable;
	bp::list coef_arrays;
	bp::list coef_shape;
	int (*coef_array_shape)[2];
	coef_array_shape = obj.coef_array_shape;
	for(i=0;i!= obj.image_components;++i){
		coef_arrays.append(cArray2List(obj.coef_arrays[i], coef_array_shape[i][0]*coef_array_shape[i][1]));
		coef_shape.append(bp::make_tuple(coef_array_shape[i][0], coef_array_shape[i][1]));
	}
	jpegDict["coef_array_shape"] = coef_shape;
	jpegDict["coef_arrays"] = coef_arrays;
	
    freeJpegObj(obj);
	return jpegDict;
}



BOOST_PYTHON_MODULE(_jpegtools) {
	bp::def("read_jpeg", &_read_jpeg);
}
