#include <Python.h>

PyObject* version(PyObject*, PyObject* o)
{
    return PyUnicode_FromString("0.1.0");
}

static PyMethodDef wmpython_methods[] = {
    { "version", (PyCFunction)version, METH_NOARGS, nullptr }
    , { nullptr, nullptr, 0, nullptr }
};

static PyModuleDef wmpython_module = {
    PyModuleDef_HEAD_INIT,
    "wmpython",                             // Module name to use with Python import statements
    "Provides some functions, but faster",  // Module description
    0,
    wmpython_methods                        // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_wmpython()
{
    return PyModule_Create(&wmpython_module);
}