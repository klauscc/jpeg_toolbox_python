##jpeg toolbox

this toolbox was written to extract the dct coefficient of jpeg images.
The python interface is wrapped via boost-python.


### 1. dependencies

    cmake
    boost-python
    python-devel
    libjpeg

### 2. compilation

    
```
mkdir build
cd build
cmake ..
make
```

### 3. usage

#### 3.1 c/c++ interface

the struct `jpegobj` 
```c    
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
```

in `test_jpeg_read.c`:
    
```c
const char *image = "../demo.jpg";
printf("%s\n",image);
jpegobj obj = read_jpeg(image);
```

#### 3.2 python interface
it returns a dict, which has the same properties as struct `jpegobj`

usage example:

```python
import sys
sys.path.append('./python')
import jpegtools

jpeginfo = jpegtools.read_jpeg('./demo.jpg')
print jpeginfo
```
