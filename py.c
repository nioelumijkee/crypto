/* 
 * python c extension example
 */
#include <Python.h>
#include "crypt.c"

// -------------------------------------------------------------------------- //
static PyObject * m_encoder_caesar(PyObject *self, PyObject *args)
{    
  PyObject *pyobj;
  int a;
  PyObject *returnobj = NULL;  /* null = ex */
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(Oi)", &pyobj, &a))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int");
    }
  else 
    {
      if (PyBytes_Check(pyobj) == 1)
	{
	  size = PyBytes_Size(pyobj);
	  buf = PyBytes_AsString(pyobj);
	  encoder_caesar(buf, a, size);
	  pyobj = PyBytes_FromStringAndSize(buf, size);
	  returnobj = Py_BuildValue("O", pyobj); 
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return returnobj;
}


// -------------------------------------------------------------------------- //
static PyObject * m_decoder_caesar(PyObject *self, PyObject *args)
{    
  PyObject *pyobj;
  int a;
  PyObject *returnobj = NULL;  /* null = ex */
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(Oi)", &pyobj, &a))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int");
    }
  else 
    {
      if (PyBytes_Check(pyobj) == 1)
	{
	  size = PyBytes_Size(pyobj);
	  buf = PyBytes_AsString(pyobj);
	  decoder_caesar(buf, a, size);
	  pyobj = PyBytes_FromStringAndSize(buf, size);
	  returnobj = Py_BuildValue("O", pyobj); 
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return returnobj;
}


// -------------------------------------------------------------------------- //
// table registrtion
static PyMethodDef crypt_methods[] = 
  {
    /* name address format desc */
    {"encoder_caesar", m_encoder_caesar, METH_VARARGS, "encoder caesar alg"},
    {"decoder_caesar", m_decoder_caesar, METH_VARARGS, "decoder caesar alg"},
    {NULL, NULL, 0, NULL} 
  };


// -------------------------------------------------------------------------- //
// struct modul
static struct PyModuleDef cryptmodule = 
  {
    PyModuleDef_HEAD_INIT,
    "crypt",                   // name
    "crypto lib by nuil kem",  // desc, maybe NULL 
    -1,                        // size struct for everyone
    crypt_methods,             // methods table
    NULL,                      // m_slots
    NULL,                      // m_traverse
    NULL,                      // m_clear
    NULL                       // m_free
  };


// -------------------------------------------------------------------------- //
// init
PyMODINIT_FUNC PyInit_crypt()
{
  return PyModule_Create(&cryptmodule);
}
