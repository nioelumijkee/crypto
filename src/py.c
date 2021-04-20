#include <Python.h>
#include "crypt.c"

#define DIS(x) if(x) {} /* disable */

// -------------------------------------------------------------------------- //
static PyObject * m_encoder_caesar(PyObject *self, PyObject *args)
{    
  PyObject *inobj;
  int a;
  PyObject *returnobj = NULL;  /* null = ex */
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(Oi)", &inobj, &a))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int");
    }
  else 
    {
      if (PyBytes_Check(inobj) == 1)
	{
	  size = PyBytes_Size(inobj);
	  buf = PyBytes_AsString(inobj);
	  encoder_caesar(buf, a, size);
	  inobj = PyBytes_FromStringAndSize(buf, size);
	  returnobj = Py_BuildValue("O", inobj); 
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_decoder_caesar(PyObject *self, PyObject *args)
{    
  PyObject *inobj;
  int a;
  PyObject *returnobj = NULL;  /* null = ex */
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(Oi)", &inobj, &a))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int");
    }
  else 
    {
      if (PyBytes_Check(inobj) == 1)
	{
	  size = PyBytes_Size(inobj);
	  buf = PyBytes_AsString(inobj);
	  decoder_caesar(buf, a, size);
	  inobj = PyBytes_FromStringAndSize(buf, size);
	  returnobj = Py_BuildValue("O", inobj); 
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_encoder_affine(PyObject *self, PyObject *args)
{    
  PyObject *inobj;
  int a;
  int b;
  PyObject *returnobj = NULL;  /* null = ex */
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(Oii)", &inobj, &a, &b))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int int");
    }
  else 
    {
      if (PyBytes_Check(inobj) == 1)
	{
	  size = PyBytes_Size(inobj);
	  buf = PyBytes_AsString(inobj);
	  encoder_affine(buf, a, b, size);
	  inobj = PyBytes_FromStringAndSize(buf, size);
	  returnobj = Py_BuildValue("O", inobj); 
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_decoder_affine(PyObject *self, PyObject *args)
{    
  PyObject *inobj;
  int a;
  int b;
  PyObject *returnobj = NULL;  /* null = ex */
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(Oii)", &inobj, &a, &b))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int int");
    }
  else 
    {
      if (PyBytes_Check(inobj) == 1)
	{
	  size = PyBytes_Size(inobj);
	  buf = PyBytes_AsString(inobj);
	  decoder_affine(buf, a, b, size);
	  inobj = PyBytes_FromStringAndSize(buf, size);
	  returnobj = Py_BuildValue("O", inobj); 
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
// table registrtion
static PyMethodDef crypt_methods[] = 
  {
    /* name address format desc */
    {"encoder_caesar", m_encoder_caesar, METH_VARARGS, "encoder caesar alg"},
    {"decoder_caesar", m_decoder_caesar, METH_VARARGS, "decoder caesar alg"},
    {"encoder_affine", m_encoder_affine, METH_VARARGS, "encoder affine alg"},
    {"decoder_affine", m_decoder_affine, METH_VARARGS, "decoder affine alg"},
    {NULL, NULL, 0, NULL} 
  };


// -------------------------------------------------------------------------- //
// struct modul
static struct PyModuleDef cryptmodule = 
  {
    PyModuleDef_HEAD_INIT,
    "crypt",                       // name
    "crypto lib by nio elumijke",  // desc, maybe NULL 
    -1,                            // size struct for everyone
    crypt_methods,                 // methods table
    NULL,                          // m_slots
    NULL,                          // m_traverse
    NULL,                          // m_clear
    NULL                           // m_free
  };


// -------------------------------------------------------------------------- //
// init
PyMODINIT_FUNC PyInit_crypt()
{
  return PyModule_Create(&cryptmodule);
}
