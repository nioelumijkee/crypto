#include <Python.h>
#include "crypt.c"
#include "hash.c"

#define DIS(x) if(x) {} /* disable */

// -------------------------------------------------------------------------- //
static PyObject * m_hash_r(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *inobj;
  int a;
  char *buf;
  char h[1024];
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

	  if (a > 1024)
	    a = 1024;

	  hash_r(size, a, buf, h);

	  inobj = PyBytes_FromStringAndSize(h, a);
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
static PyObject * m_random512_init_by_time(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = Py_BuildValue("i", 1);
  random512_init_by_time();
  return returnobj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_random512_init(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  int a;

  if (! PyArg_Parse(args, "(i)", &a))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: int");
    }
  else 
    {
      random512_init_by_time();
      returnobj = Py_BuildValue("i", 1);
    }
  return returnobj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_random512_set_key(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *inobj;
  char *buf;
  int size;

  if (! PyArg_Parse(args, "(O)", &inobj))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes");
    }
  else 
    {
      if (PyBytes_Check(inobj) == 1)
	{
	  size = PyBytes_Size(inobj);
	  buf = PyBytes_AsString(inobj);

	  if (size != 512)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: size bytes != 512");
	    }
	  else
	    {
	      random512_set_key(buf);
	      returnobj = Py_BuildValue("i", 1);
	    }
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
static PyObject * m_gen_blend256(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *inobj;
  char buf[256];

  gen_blend256(buf);

  inobj = PyBytes_FromStringAndSize(buf, 256);
  returnobj = Py_BuildValue("O", inobj); 

  return returnobj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_gen_blend256_invert(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *inobj;
  char *buf;
  char buf_inv[256];
  int size;

  if (! PyArg_Parse(args, "(O)", &inobj))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes");
    }
  else 
    {
      if (PyBytes_Check(inobj) == 1)
	{
	  size = PyBytes_Size(inobj);
	  buf = PyBytes_AsString(inobj);

	  if (size != 256)
	    {
	    }
	  else
	    {
	      gen_blend256_invert(buf, buf_inv);
	      inobj = PyBytes_FromStringAndSize(buf_inv, 256);
	      returnobj = Py_BuildValue("O", inobj); 
	    }
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
static PyObject * m_gen_blend16(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *inobj;
  char buf[16];

  gen_blend16(buf);

  inobj = PyBytes_FromStringAndSize(buf, 16);
  returnobj = Py_BuildValue("O", inobj); 

  return returnobj;
  DIS(self);
  DIS(args);
}


// -------------------------------------------------------------------------- //
static PyObject * m_gen_var(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *inobj;
  char *buf = NULL;
  long int size;

  if (! PyArg_Parse(args, "(i)", &size))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: int");
    }
  else 
    {
      if (size < 1) size = 1;
      buf = calloc(size, sizeof(char));
      if (buf == NULL)
	{
	  PyErr_SetString(PyExc_SystemError, "Error: calloc");
	}
      else
	{
	  gen_var(buf, size);
	  inobj = PyBytes_FromStringAndSize(buf, size);
	  returnobj = Py_BuildValue("O", inobj);
	} 
    }
  return returnobj;
  DIS(self);
}


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
static PyObject * m_encoder_polybius(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *in_data;
  PyObject *in_key;
  PyObject *in_wordx;
  PyObject *in_wordy;
  long int size_data;
  int size_key;
  int size_wordx;
  int size_wordy;
  char *buf_data;
  char *buf_key;
  char *buf_wordx;
  char *buf_wordy;
  char *buf_data_out;

  if (! PyArg_Parse(args, "(OOOO)", &in_data, &in_key, &in_wordx, &in_wordy))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
    }
  else 
    {
      if (PyBytes_Check(in_data)    == 1 && 
	  PyBytes_Check(in_key)     == 1 &&
	  PyBytes_Check(in_wordx)   == 1 &&
	  PyBytes_Check(in_wordy)   == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  size_key = PyBytes_Size(in_key);
	  size_wordx = PyBytes_Size(in_wordx);
	  size_wordy = PyBytes_Size(in_wordy);

	  buf_data = PyBytes_AsString(in_data);
	  buf_key = PyBytes_AsString(in_key);
	  buf_wordx = PyBytes_AsString(in_wordx);
	  buf_wordy = PyBytes_AsString(in_wordy);

	  
	  if (size_data < 1) size_data = 1;
	  buf_data_out = calloc(size_data*2, sizeof(char));
	  if (buf_data_out == NULL)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: calloc");
	    }
	  else
	    {
	      if (size_key == 256 &&
		  size_wordx == 16 &&
		  size_wordy == 16)
		{
		  encoder_polybius(size_data, 
				   buf_wordx,
				   buf_wordy,
				   buf_key,
				   buf_data,
				   buf_data_out);
		  in_data = PyBytes_FromStringAndSize(buf_data_out, size_data*2);
		  returnobj = Py_BuildValue("O", in_data); 
		}
	      else
		{
		  PyErr_SetString(PyExc_SystemError, "Error: size key/word");
		}
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
static PyObject * m_decoder_polybius(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *in_data;
  PyObject *in_key;
  PyObject *in_wordx;
  PyObject *in_wordy;
  long int size_data;
  int size_key;
  int size_wordx;
  int size_wordy;
  char *buf_data;
  char *buf_key;
  char *buf_wordx;
  char *buf_wordy;
  char *buf_data_out;

  if (! PyArg_Parse(args, "(OOOO)", &in_data, &in_key, &in_wordx, &in_wordy))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes bytes");
    }
  else 
    {
      if (PyBytes_Check(in_data)    == 1 && 
	  PyBytes_Check(in_key)     == 1 &&
	  PyBytes_Check(in_wordx)   == 1 &&
	  PyBytes_Check(in_wordy)   == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  size_key = PyBytes_Size(in_key);
	  size_wordx = PyBytes_Size(in_wordx);
	  size_wordy = PyBytes_Size(in_wordy);

	  buf_data = PyBytes_AsString(in_data);
	  buf_key = PyBytes_AsString(in_key);
	  buf_wordx = PyBytes_AsString(in_wordx);
	  buf_wordy = PyBytes_AsString(in_wordy);

	  
	  if (size_data < 1) size_data = 1;
	  buf_data_out = calloc(size_data, sizeof(char));
	  if (buf_data_out == NULL)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: calloc");
	    }
	  else
	    {
	      if (size_key == 256 &&
		  size_wordx == 16 &&
		  size_wordy == 16)
		{
		  decoder_polybius(size_data, 
				   buf_wordx,
				   buf_wordy,
				   buf_key,
				   buf_data,
				   buf_data_out);
		  in_data = PyBytes_FromStringAndSize(buf_data_out, size_data);
		  returnobj = Py_BuildValue("O", in_data); 
		}
	      else
		{
		  PyErr_SetString(PyExc_SystemError, "Error: size key/word");
		}
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
static PyObject * m_encoder_insert_this(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *in_data;
  long int size_data;
  char *buf_data;
  char *buf_data_out;
  int a;

  if (! PyArg_Parse(args, "(Oi)", &in_data, &a))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int");
    }
  else 
    {
      if (PyBytes_Check(in_data) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  buf_data = PyBytes_AsString(in_data);

	  if (size_data < 1) size_data = 1;
	  buf_data_out = calloc(size_data*2, sizeof(char));
	  if (buf_data_out == NULL)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: calloc");
	    }
	  else
	    {
	      encoder_insert_this(a, size_data, buf_data, buf_data_out);
	      in_data = PyBytes_FromStringAndSize(buf_data_out, size_data*2);
	      returnobj = Py_BuildValue("O", in_data); 
	    }
	}
      else
	{
	  PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes");
	}
    }
  return returnobj;
  DIS(self);
}


// -------------------------------------------------------------------------- //
static PyObject * m_encoder_insert_rnd(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *in_data;
  long int size_data;
  char *buf_data;
  char *buf_data_out;
  int a;

  if (! PyArg_Parse(args, "(Oi)", &in_data, &a))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int");
    }
  else 
    {
      if (PyBytes_Check(in_data) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  buf_data = PyBytes_AsString(in_data);

	  if (size_data < 1) size_data = 1;
	  buf_data_out = calloc(size_data*2, sizeof(char));
	  if (buf_data_out == NULL)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: calloc");
	    }
	  else
	    {
	      encoder_insert_rnd(a, size_data, buf_data, buf_data_out);
	      in_data = PyBytes_FromStringAndSize(buf_data_out, size_data*2);
	      returnobj = Py_BuildValue("O", in_data); 
	    }
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
static PyObject * m_decoder_insert(PyObject *self, PyObject *args)
{    
  PyObject *returnobj = NULL;
  PyObject *in_data;
  long int size_data;
  char *buf_data;
  char *buf_data_out;
  int a;

  if (! PyArg_Parse(args, "(Oi)", &in_data, &a))
    {
      PyErr_SetString(PyExc_SystemError, "Error in arguments: bytes int");
    }
  else 
    {
      if (PyBytes_Check(in_data) == 1)
	{
	  size_data = PyBytes_Size(in_data);
	  buf_data = PyBytes_AsString(in_data);

	  if (size_data < 1) size_data = 1;
	  buf_data_out = calloc(size_data, sizeof(char));
	  if (buf_data_out == NULL)
	    {
	      PyErr_SetString(PyExc_SystemError, "Error: calloc");
	    }
	  else
	    {
	      decoder_insert(a, size_data, buf_data, buf_data_out);
	      in_data = PyBytes_FromStringAndSize(buf_data_out, size_data);
	      returnobj = Py_BuildValue("O", in_data); 
	    }
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
// table registration
static PyMethodDef ncryptpy_methods[] = 
  {
    /* name address format desc */
    {"hash_r",                  m_hash_r,                   METH_VARARGS, ""},
    {"random512_init_by_time",  m_random512_init_by_time,   METH_VARARGS, ""},
    {"random512_init",          m_random512_init,           METH_VARARGS, ""},
    {"random512_set_key",       m_random512_set_key,        METH_VARARGS, ""},
    {"gen_blend256",            m_gen_blend256,             METH_VARARGS, ""},
    {"gen_blend256_invert",     m_gen_blend256_invert,      METH_VARARGS, ""},
    {"gen_blend16",             m_gen_blend16,              METH_VARARGS, ""},
    {"gen_var",                 m_gen_var,                  METH_VARARGS, ""},
    {"encoder_caesar",          m_encoder_caesar,           METH_VARARGS, ""},
    {"decoder_caesar",          m_decoder_caesar,           METH_VARARGS, ""},
    {"encoder_affine",          m_encoder_affine,           METH_VARARGS, ""},
    {"decoder_affine",          m_decoder_affine,           METH_VARARGS, ""},
    {"deencoder_couple",        m_deencoder_couple,         METH_VARARGS, ""},
    {"encoder_swap",            m_encoder_swap,             METH_VARARGS, ""},
    {"decoder_swap",            m_decoder_swap,             METH_VARARGS, ""},
    {"encoder_bits",            m_encoder_bits,             METH_VARARGS, ""},
    {"decoder_bits",            m_decoder_bits,             METH_VARARGS, ""},
    {"encoder_polybius",        m_encoder_polybius,         METH_VARARGS, ""},
    {"decoder_polybius",        m_decoder_polybius,         METH_VARARGS, ""},
    {"encoder_insert_this",     m_encoder_insert_this,      METH_VARARGS, ""},
    {"encoder_insert_rnd",      m_encoder_insert_rnd,       METH_VARARGS, ""},
    {"decoder_insert",          m_decoder_insert,           METH_VARARGS, ""},
    {"deencoder_vernam",        m_deencoder_vernam,         METH_VARARGS, ""},
    {NULL, NULL, 0, NULL} 
  };


// -------------------------------------------------------------------------- //
// struct modul
static struct PyModuleDef ncryptpy_module = 
  {
    PyModuleDef_HEAD_INIT,
    "ncryptpy",                           // name
    "cryptographic lib by nio elumijke",  // desc, maybe NULL 
    -1,                                   // size struct for everyone
    ncryptpy_methods,                     // methods table
    NULL,                                 // m_slots
    NULL,                                 // m_traverse
    NULL,                                 // m_clear
    NULL                                  // m_free
  };


// -------------------------------------------------------------------------- //
// init
PyMODINIT_FUNC PyInit_ncryptpy()
{
  return PyModule_Create(&ncryptpy_module);
}
