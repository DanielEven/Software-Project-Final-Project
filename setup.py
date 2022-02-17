# Setup file.

from setuptools import setup, Extension

# Code from lecture.

"""
    Calling
    $python setup.py build_ext --inplace
    will build the extension library in the current file.

    Calling
    $python setup.py build
    will build a file that looks like ./build/lib*, where
    lib* is a file that begins with lib. The library will
    be in this file and end with a C library extension,
    such as .so

    Calling
    $python setup.py install
    will install the module in your site-packages file.

    See the distutils section of
    'Extending and Embedding the Python Interpreter'
    at docs.python.org for more information.
"""

# setup() parameters - https://packaging.python.org/guides/distributing-packages-using-setuptools/
setup(
    name='spkmeansmodule',
    author="Daniel Even & Liam Mohr",
    description="Normalized Spectral Clustering Algorithm ++",
    install_requires=['invoke'],
    ext_modules=[
        Extension(
            # the qualified name of the extension module to build
            'spkmeansmodule',
            # the files to compile into our module relative to ``setup.py``
            ['spkmeansmodule.c'],
        ),
    ]
)
