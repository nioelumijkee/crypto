#include <stdlib.h>
#include <Python.h>
#include "hash.c"
#include "add.c"
#include "crypt.c"

#define DIS(x) if(x) {} /* disable */

// -------------------------------------------------------------------------- //
// hash
// -------------------------------------------------------------------------- //
#define MAX_HASH_R 1024
static PyObject * m_hash_r(PyObject *self, PyObject *args)
{
  PyObject  *returnobj = NULL;
  PyObject  *in_data;
  int        size_hash;
  int        size_data;
  char      *buf_data;
  char       buf_hash[MAX_HASH_R];

  if (! PyArg_Parse(args, "(Oi)", &in_data, &size_hash))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int");
    }
  else 
    {
      if (PyBytes_Check(in_data) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  buf_data  = PyBytes_AsString(in_data);

	  if      (size_data < 1)           size_data = 1;
	  if      (size_hash < 1)           size_hash = 1;
	  else if (size_hash > MAX_HASH_R)  size_hash = MAX_HASH_R;

	  hash_r(size_data, size_hash, buf_data, buf_hash);

	  returnobj = PyBytes_FromStringAndSize(buf_hash, size_hash);
	  returnobj = Py_BuildValue("O", returnobj); 
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
// add
// -------------------------------------------------------------------------- //
static PyObject * m_reverse(PyObject *self, PyObject *args)
{
  PyObject  *in_data;
  int        size_data;
  int        start;
  int        len;
  char      *buf_data;

  if (! PyArg_Parse(args, "(Oii)", &in_data, &start, &len))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int int");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  buf_data = PyBytes_AsString(in_data);

	  if      (size_data < 1)           size_data = 1;

	  validate_ssl(size_data, &start, &len);
	  reverse(buf_data, start, len);
	  in_data = PyBytes_FromStringAndSize(buf_data, size_data);
	  in_data = Py_BuildValue("O", in_data);
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return (Py_BuildValue("i", 0));
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_shift(PyObject *self, PyObject *args)
{
  PyObject  *in_data;
  int        size_data;
  int        start;
  int        len;
  int        sh;
  char      *buf_data;

  if (! PyArg_Parse(args, "(Oiii)", &in_data, &start, &len, &sh))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int int int");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  buf_data = PyBytes_AsString(in_data);
	  validate_ssl(size_data, &start, &len);
	  shift(buf_data, size_data, start, len, sh);
	  in_data = PyBytes_FromStringAndSize(buf_data, size_data);
	  in_data = Py_BuildValue("O", in_data);
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return (Py_BuildValue("i", 0));
  DIS(self);
}


// -------------------------------------------------------------------------- //
// crypt
// -------------------------------------------------------------------------- //
static PyObject * m_encoder_bits(PyObject *self, PyObject *args)
{
  PyObject  *in_data;
  PyObject  *in_key;
  int        size_data;
  int        size_key;
  int        start;
  int        len;
  char      *buf_data;
  char      *buf_key;

  if (! PyArg_Parse(args, "(OOii)", &in_data, &in_key, &start, &len))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes int int");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1 && PyBytes_Check(in_key) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  size_key = PyBytes_Size(in_key);
	  buf_data = PyBytes_AsString(in_data);
	  buf_key = PyBytes_AsString(in_key);
	  validate_ssl(size_data, &start, &len);
	  encoder_bits(buf_data, buf_key, size_data, size_key, start, len);
	  in_data = PyBytes_FromStringAndSize(buf_data, size_data);
	  in_data = Py_BuildValue("O", in_data);
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
	}
    }
  return (Py_BuildValue("i", 0));
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_decoder_bits(PyObject *self, PyObject *args)
{
  PyObject  *in_data;
  PyObject  *in_key;
  int        size_data;
  int        size_key;
  int        start;
  int        len;
  char      *buf_data;
  char      *buf_key;

  if (! PyArg_Parse(args, "(OOii)", &in_data, &in_key, &start, &len))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes int int");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1 && PyBytes_Check(in_key) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  size_key = PyBytes_Size(in_key);
	  buf_data = PyBytes_AsString(in_data);
	  buf_key = PyBytes_AsString(in_key);
	  validate_ssl(size_data, &start, &len);
	  decoder_bits(buf_data, buf_key, size_data, size_key, start, len);
	  in_data = PyBytes_FromStringAndSize(buf_data, size_data);
	  in_data = Py_BuildValue("O", in_data);
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
	}
    }
  return (Py_BuildValue("i", 0));
  DIS(self);
}


// -------------------------------------------------------------------------- //
// setup
// -------------------------------------------------------------------------- //
// table registration
static PyMethodDef ncp_methods[] = 
  {
    /* name address format desc */
    {"hash_r",                 m_hash_r,                  METH_VARARGS, ""},
    {"reverse",                m_reverse,                 METH_VARARGS, ""},
    {"shift",                  m_shift,                   METH_VARARGS, ""},
    {"encoder_bits",           m_encoder_bits,            METH_VARARGS, ""},
    {"decoder_bits",           m_decoder_bits,            METH_VARARGS, ""},
    {NULL, NULL, 0, NULL} 
  };


// -------------------------------------------------------------------------- //
// struct modul
static struct PyModuleDef ncp_module = 
  {
    PyModuleDef_HEAD_INIT,
    "ncp",                                // name
    "crypto lib by nio elumijke",         // desc or NULL 
    -1,                                   // size struct for everyone
    ncp_methods,                          // methods table
    NULL,                                 // m_slots
    NULL,                                 // m_traverse
    NULL,                                 // m_clear
    NULL                                  // m_free
  };


// -------------------------------------------------------------------------- //
// init
PyMODINIT_FUNC PyInit_ncp()
{
  return PyModule_Create(&ncp_module);
}
