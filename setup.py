# -*- coding: utf-8 -*-
#================================================================
#   God Bless You. 
#   
#   author: klaus
#   email: chengfeng2333@gmail.com
#   created date: 2020/05/08
#   description: 
#
#================================================================

from setuptools import setup, Extension

setup(
    name='jpegtools',
    version='0.0.1',
    packages=['jpegtools'],
    package_dir={'jpegtools': './python/jpegtools'},
    package_data={'jpegtools': ['_jpegtools.so', 'libextract_dct.so']},
    include_package_data=True,
)
