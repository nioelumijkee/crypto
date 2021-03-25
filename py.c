/* 
 * python c extension example
 */
#include <Python.h>
#include <string.h>

// -------------------------------------------------------------------------- //
// function modul
static PyObject * message(PyObject *self, PyObject *args)
{    
  char *fromPython; 
  char result[1024];
  /* Python -> C                            */
  if (! PyArg_Parse(args, "(s)", &fromPython))
    {
      return NULL;
    }
  else 
    {
      strcpy(result, "Hello, ");
      strcat(result, fromPython);
      /* C -> Python                 */
      return Py_BuildValue("s", result); 
    }
}


// -------------------------------------------------------------------------- //
// function modul
static PyObject * posthello(PyObject *self, PyObject *args)
{ 
  printf("Hello\n");
  return Py_BuildValue("s", "ok");
}


// -------------------------------------------------------------------------- //
// table registrtion
static PyMethodDef hello_methods[] = 
  {
    /* name     address  format         desc    */
    {"message", message, METH_VARARGS, "add Hello"},
    {"posthello", posthello, METH_VARARGS, "post"},
    /* end */
    {NULL, NULL, 0, NULL} 
  };


// -------------------------------------------------------------------------- //
// struct modul
static struct PyModuleDef hellomodule = 
  {
    PyModuleDef_HEAD_INIT,
    "hello",  // name
    "mod doc",  // desc, maybe NULL 
    -1, // size struct for everyone
    hello_methods, // methods table
    NULL, // m_slots
    NULL, // m_traverse
    NULL, // m_clear
    NULL // m_free
  };


// -------------------------------------------------------------------------- //
// init
PyMODINIT_FUNC PyInit_hello()
{
  return PyModule_Create(&hellomodule);
}
