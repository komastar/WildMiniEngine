from setuptools import setup, Extension

wmpython_module = Extension('wmpython', sources = ['module.cpp'])

setup(
    name='wmpython',
    version='0.1.0',
    description='Python Package with wmpython C++ extension',
    ext_modules=[wmpython_module]
)