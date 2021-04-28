#include <stdlib.h>
#include <Python.h>
#include "hash.c"
#include "random.c"
#include "add.c"
#include "crypt.c"

#define DIS(x) if(x) {} /* disable */

// -------------------------------------------------------------------------- //
// hash
// -------------------------------------------------------------------------- //
#define MAX_HASH_R 1024

static PyObject * m_hash_r(PyObject *self, PyObject *args)
{    
  PyObject *in_data;
  PyObject *out_data = NULL;
  int size_hash;
  char *buf_data;
  char buf_hash[MAX_HASH_R];
  long int size_data;

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

	  if      (size_hash < 1)           size_hash = 1;
	  else if (size_hash > MAX_HASH_R)  size_hash = MAX_HASH_R;

	  hash_r(size_data, size_hash, buf_data, buf_hash);

	  out_data = PyBytes_FromStringAndSize(buf_hash, size_hash);
	  out_data = Py_BuildValue("O", out_data); 
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return out_data;
  DIS(self);
}


// -------------------------------------------------------------------------- //
// random
// -------------------------------------------------------------------------- //
static PyObject * m_random512(PyObject *self, PyObject *args)
{    
  PyObject *out_obj = NULL;
  random512();
  out_obj = Py_BuildValue("i", 0);
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_random512_set(PyObject *self, PyObject *args)
{    
  PyObject *out_obj = NULL;
  int s;

  if (! PyArg_Parse(args, "(i)", &s))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: int");
    }
  else 
    {
      random512_set(s);
      out_obj = Py_BuildValue("i", 0);
    }
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_random512_set_count(PyObject *self, PyObject *args)
{    
  PyObject *out_obj = NULL;
  int s;

  if (! PyArg_Parse(args, "(i)", &s))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: int");
    }
  else 
    {
      random512_set_count(s);
      out_obj = Py_BuildValue("i", 0);
    }
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_random512_set_by_time(PyObject *self, PyObject *args)
{    
  PyObject *out_obj = NULL;
  random512_set_by_time();
  out_obj = Py_BuildValue("i", 0);
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_random512_set_key(PyObject *self, PyObject *args)
{    
  PyObject *in_obj;
  PyObject *out_obj = NULL;
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(O)", &in_obj))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes");
    }
  else 
    {
      if (PyBytes_Check(in_obj) == 1)
	{
	  size  = PyBytes_Size(in_obj);
	  buf   = PyBytes_AsString(in_obj);

	  if (size != 512)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: size key != 512");
	    }
	  else
	    {
	      random512_set_key(buf);
	      out_obj = Py_BuildValue("i", 0);
	    }
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return out_obj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_random512_get(PyObject *self, PyObject *args)
{    
  PyObject *out_obj = NULL;
  int s = random512_get();
  out_obj = Py_BuildValue("i", s);
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_random512_get_count(PyObject *self, PyObject *args)
{    
  PyObject *out_obj = NULL;
  int s = random512_get_count();
  out_obj = Py_BuildValue("i", s);
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
// additional
// -------------------------------------------------------------------------- //
static PyObject * m_gen_blend256(PyObject *self, PyObject *args)
{
  PyObject *out_obj;
  char buf_data[256];
  gen_blend256(buf_data);
  out_obj   = PyBytes_FromStringAndSize(buf_data, 256);
  out_obj   = Py_BuildValue("O", out_obj);
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_gen_blend16(PyObject *self, PyObject *args)
{
  PyObject *out_obj;
  char buf_data[16];
  gen_blend16(buf_data);
  out_obj   = PyBytes_FromStringAndSize(buf_data, 16);
  out_obj   = Py_BuildValue("O", out_obj);
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_gen_blend256_invert(PyObject *self, PyObject *args)
{
  PyObject *in_data;
  PyObject *out_data = NULL;
  char *buf_data;
  char buf_data_inv[256];
  int size;

  if (! PyArg_Parse(args, "(O)", &in_data))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1)
	{
	  size       = PyBytes_Size(in_data);
	  buf_data   = PyBytes_AsString(in_data);

	  if (size != 256)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: size bytes != 256");
	    }
	  else
	    {
	      gen_blend256_invert(buf_data, buf_data_inv);
	      out_data = PyBytes_FromStringAndSize(buf_data_inv, 256);
	      out_data = Py_BuildValue("O", out_data);
	    }
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in argument 1: bytes");
	}
    }
  return out_data;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_gen1024(PyObject *self, PyObject *args)
{
  PyObject *out_obj;
  char buf_data[1024];
  gen_var(buf_data, 1024);
  out_obj   = PyBytes_FromStringAndSize(buf_data, 1024);
  out_obj   = Py_BuildValue("O", out_obj);
  return out_obj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
// crypt
// -------------------------------------------------------------------------- //
static PyObject * m_encoder_caesar(PyObject *self, PyObject *args)
{
  PyObject *returnobj = NULL;
  PyObject *inobj;
  int a;
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
  PyObject *returnobj = NULL;
  PyObject *inobj;
  int a;
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
  PyObject *returnobj = NULL;
  PyObject *inobj;
  int a;
  int b;
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
  PyObject *returnobj = NULL;
  PyObject *inobj;
  int a;
  int b;
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
static PyObject * m_deencoder_couple(PyObject *self, PyObject *args)
{
  PyObject *returnobj = NULL;
  PyObject *in_data;
  PyObject *in_key;
  long int size_data;
  int size_key;
  char *buf_data;
  char *buf_key;

  if (! PyArg_Parse(args, "(OO)", &in_data, &in_key))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1 && PyBytes_Check(in_key) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  size_key = PyBytes_Size(in_key);
	  buf_data = PyBytes_AsString(in_data);
	  buf_key = PyBytes_AsString(in_key);

	  if (size_key != 256)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: key size != 256");
	    }
	  else
	    {
	      deencoder_couple(buf_data, buf_key, size_data);
	      in_data = PyBytes_FromStringAndSize(buf_data, size_data);
	      returnobj = Py_BuildValue("O", in_data);
	    }

	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_encoder_swap(PyObject *self, PyObject *args)
{
  PyObject *returnobj = NULL;
  PyObject *inobj;
  int a;
  int b;
  int c;
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(Oiii)", &inobj, &a, &b, &c))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int int int");
    }
  else
    {
      if (PyBytes_Check(inobj) == 1)
	{
	  size = PyBytes_Size(inobj);
	  buf = PyBytes_AsString(inobj);
	  encoder_swap(buf, a, b, c, size);
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
static PyObject * m_decoder_swap(PyObject *self, PyObject *args)
{
  PyObject *returnobj = NULL;
  PyObject *inobj;
  int a;
  int b;
  int c;
  char *buf;
  long int size;

  if (! PyArg_Parse(args, "(Oiii)", &inobj, &a, &b, &c))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int int int");
    }
  else
    {
      if (PyBytes_Check(inobj) == 1)
	{
	  size = PyBytes_Size(inobj);
	  buf = PyBytes_AsString(inobj);
	  decoder_swap(buf, a, b, c, size);
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
static PyObject * m_encoder_bits(PyObject *self, PyObject *args)
{
  PyObject *returnobj = NULL;
  PyObject *in_data;
  PyObject *in_key;
  long int size_data;
  long int size_key;
  char *buf_data;
  char *buf_key;

  if (! PyArg_Parse(args, "(OO)", &in_data, &in_key))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1 && PyBytes_Check(in_key) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  size_key = PyBytes_Size(in_key);
	  buf_data = PyBytes_AsString(in_data);
	  buf_key = PyBytes_AsString(in_key);

	  encoder_bits(buf_data, buf_key, size_data, size_key);
	  in_data = PyBytes_FromStringAndSize(buf_data, size_data);
	  returnobj = Py_BuildValue("O", in_data);
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_decoder_bits(PyObject *self, PyObject *args)
{
  PyObject *returnobj = NULL;
  PyObject *in_data;
  PyObject *in_key;
  long int size_data;
  long int size_key;
  char *buf_data;
  char *buf_key;

  if (! PyArg_Parse(args, "(OO)", &in_data, &in_key))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1 && PyBytes_Check(in_key) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  size_key = PyBytes_Size(in_key);
	  buf_data = PyBytes_AsString(in_data);
	  buf_key = PyBytes_AsString(in_key);

	  decoder_bits(buf_data, buf_key, size_data, size_key);
	  in_data = PyBytes_FromStringAndSize(buf_data, size_data);
	  returnobj = Py_BuildValue("O", in_data);
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_deencoder_vernam(PyObject *self, PyObject *args)
{
  PyObject *returnobj = NULL;
  PyObject *in_data;
  PyObject *in_key;
  long int size_data;
  long int size_key;
  char *buf_data;
  char *buf_key;

  if (! PyArg_Parse(args, "(OO)", &in_data, &in_key))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
    }
  else
    {
      if (PyBytes_Check(in_data) == 1 && PyBytes_Check(in_key) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  size_key = PyBytes_Size(in_key);
	  buf_data = PyBytes_AsString(in_data);
	  buf_key = PyBytes_AsString(in_key);

	  deencoder_vernam(buf_data, buf_key, size_data, size_key);
	  in_data = PyBytes_FromStringAndSize(buf_data, size_data);
	  returnobj = Py_BuildValue("O", in_data);
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
// setup
// -------------------------------------------------------------------------- //
// table registration
static PyMethodDef ncp_methods[] = 
  {
    /* name address format desc */
    {"hash_r",                  m_hash_r,                   METH_VARARGS, ""},
    {"random512",               m_random512,                METH_VARARGS, ""},
    {"random512_set",           m_random512_set,            METH_VARARGS, ""},
    {"random512_set_count",     m_random512_set_count,      METH_VARARGS, ""},
    {"random512_set_by_time",   m_random512_set_by_time,    METH_VARARGS, ""},
    {"random512_set_key",       m_random512_set_key,        METH_VARARGS, ""},
    {"random512_get",           m_random512_get,            METH_VARARGS, ""},
    {"random512_get_count",     m_random512_get_count,      METH_VARARGS, ""},
    {"gen_blend256",            m_gen_blend256,             METH_VARARGS, ""},
    {"gen_blend16",             m_gen_blend16,              METH_VARARGS, ""},
    {"gen_blend256_invert",     m_gen_blend256_invert,      METH_VARARGS, ""},
    {"gen1024",                 m_gen1024,                  METH_VARARGS, ""},
    {"encoder_caesar",          m_encoder_caesar,           METH_VARARGS, ""},
    {"decoder_caesar",          m_decoder_caesar,           METH_VARARGS, ""},
    {"encoder_affine",          m_encoder_affine,           METH_VARARGS, ""},
    {"decoder_affine",          m_decoder_affine,           METH_VARARGS, ""},
    {"deencoder_couple",        m_deencoder_couple,         METH_VARARGS, ""},
    {"encoder_swap",            m_encoder_swap,             METH_VARARGS, ""},
    {"decoder_swap",            m_decoder_swap,             METH_VARARGS, ""},
    {"encoder_bits",            m_encoder_bits,             METH_VARARGS, ""},
    {"decoder_bits",            m_decoder_bits,             METH_VARARGS, ""},
    /* {"encoder_polybius",        m_encoder_polybius,         METH_VARARGS, ""}, */
    /* {"decoder_polybius",        m_decoder_polybius,         METH_VARARGS, ""}, */
    /* {"encoder_insert_this",     m_encoder_insert_this,      METH_VARARGS, ""}, */
    /* {"encoder_insert_rnd",      m_encoder_insert_rnd,       METH_VARARGS, ""}, */
    /* {"decoder_insert",          m_decoder_insert,           METH_VARARGS, ""}, */
    {"deencoder_vernam",        m_deencoder_vernam,         METH_VARARGS, ""},
    {NULL, NULL, 0, NULL} 
  };


// -------------------------------------------------------------------------- //
// struct modul
static struct PyModuleDef ncp_module = 
  {
    PyModuleDef_HEAD_INIT,
    "ncp",                                // name
    "cryptographic lib by nio elumijke",  // desc, maybe NULL 
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
