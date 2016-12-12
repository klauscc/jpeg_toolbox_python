import sys
sys.path.append('./python')
import jpegtools

jpeginfo = jpegtools.read_jpeg('./demo.jpg')
print jpeginfo
