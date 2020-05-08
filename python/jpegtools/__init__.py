import os
import ctypes
import numpy as np

CURRENT_FILE_DIRECTORY = os.path.abspath(os.path.dirname(__file__))
ctypes.cdll.LoadLibrary(os.path.join(CURRENT_FILE_DIRECTORY, 'libextract_dct.so'))
from . import _jpegtools

def read_jpeg(image):
    jpegobj = _jpegtools.read_jpeg(image)
    quantable = np.array(jpegobj['quant_tables'])
    quantable = quantable.reshape([jpegobj['quant_nums'], 8, 8])
    jpegobj['quant_tables'] = quantable

    coef_arrays = []
    shape = jpegobj['coef_array_shape']
    for i in range(len(shape)):
        coef_array = jpegobj['coef_arrays'][i]
        coef_array = np.array(coef_array)
        coef_arrays = coef_arrays + [coef_array.reshape(shape[i])]
    jpegobj['coef_arrays'] = coef_arrays
    return jpegobj
