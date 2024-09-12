// mdutils: C Python extension module

#include <Python.h>
#include <stdio.h>

static PyObject *
md_test(PyObject *self, PyObject *args)
{
    const char *command;
	int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    
	sts = printf( "md_test: %s\n", command );
	
    return Py_BuildValue("i", sts);
}

static PyObject *
md_clone(PyObject *self, PyObject *args)
{
    PyObject *type_arg;
	int clone_count;

    if (!PyArg_ParseTuple(args, "Oi", &type_arg, &clone_count))
        return NULL;
	
    if( type_arg )
	{
		if( PyType_Check(type_arg) )
		{
			//PyObject* result;
			PyObject* new_obj;
			//PyObject* bad_obj;
			PyTypeObject* type_object = (PyTypeObject*)type_arg;
			
			PyObject* dict_name  = PyString_FromString("__dict__");
			PyObject* attr1_name = PyString_FromString("attr1");
			PyObject* attr2_name = PyString_FromString("attr2");
			PyObject* attr3_name = PyString_FromString("attr3");
			PyObject* attr4_name = PyString_FromString("attr4");
			
			PyObject* attr1_value = PyBool_FromLong(1);
			PyObject* attr2_value = Py_BuildValue("i", 2);
			PyObject* attr3_value = Py_BuildValue("s", "3");
			PyObject* attr4_value = Py_BuildValue("i", 4);
			
			int i;
			
			//if( clone_count < 0 )
			//	printf( "mdutils.clone: type name '%s' passed, clone count: %d\n", type_object->tp_name, clone_count);
			
			if( clone_count > 0 )
			{
				PyObject* list = PyList_New( clone_count ); // сейчас все элементы == NULL
				PyObject* __dict__ = NULL;
				
				for( i=0; i<clone_count; i++)
				{
					new_obj = PyObject_CallObject((PyObject*)type_object, NULL);
					
					// увы, _PyObject_New создает только шкурку от объекта, GC и Heap с этим объектом дружить не будут; придетс€ делать call, как в питоне: x = Class()
					//~ if(i)
					//~ {
						//~ new_obj = PyObject_CallObject((PyObject*)type_object, NULL);
					//~ }
					//~ else
					//~ {
						//~ new_obj = _PyObject_New(type_object); //PyObject_New(PyObject, ); // первый объект создадим "плохой" :)
						//~ PyObject_Init(new_obj, type_object);
						//~ //new_obj = PyObject_CallObject((PyObject*)type_object, NULL);
					//~ }

					__dict__ = PyObject_GetAttr(new_obj, dict_name);
					if( __dict__ )
					{
						PyDict_SetItem(__dict__, attr1_name, attr1_value);
						PyDict_SetItem(__dict__, attr2_name, attr2_value);
						PyDict_SetItem(__dict__, attr3_name, attr3_value);
						PyDict_SetItem(__dict__, attr4_name, attr4_value);
						
						//PyObject_GenericSetAttr(new_obj, attr1_name, attr1_value);
						//PyObject_GenericSetAttr(new_obj, attr2_name, attr2_value);
						//PyObject_GenericSetAttr(new_obj, attr3_name, attr3_value);
						//PyObject_GenericSetAttr(new_obj, attr4_name, attr4_value);
					
						Py_DECREF(attr1_value); // а вот эти рефы "на константы", увы, никто кроме нас декрементить не будет
						Py_DECREF(attr2_value);
						Py_DECREF(attr3_value);
						Py_DECREF(attr4_value);
					}
					else
						printf("bad __dict__ for object [%d]\n", i);
					
					PyList_SetItem( list, i, new_obj );
					//Py_DECREF(new_obj); -- PyList_SetItem УstealsФ a reference to item and discards a reference to an item already in the list at the affected position.
				}
				
				//if( __dict__ )
				//	printf( "last obj __dict__=%08x, type %s\n", __dict__, __dict__->ob_type->tp_name );
				//else
				//	printf( "last obj __dict__=NULL\n" );
				
				//result = Py_BuildValue("O", list);
				//Py_DECREF( list );
				
				//printf( "list ob_refcnt = %d\n", list->ob_refcnt );
				//printf( "result ob_refcnt = %d\n", result->ob_refcnt );
				
				//printf( "new_obj ob_refcnt = %d\n", new_obj->ob_refcnt );
				//printf( "type_object ob_refcnt = %d\n", type_object->ob_refcnt );
				
				//~ printf( "attr1_name ob_refcnt = %d\n",  attr1_name->ob_refcnt );
				//~ printf( "attr1_value ob_refcnt = %d\n", attr1_value->ob_refcnt );
				//~ printf( "attr2_name ob_refcnt = %d\n",  attr2_name->ob_refcnt );
				//~ printf( "attr2_value ob_refcnt = %d\n", attr2_value->ob_refcnt );
				//~ printf( "attr3_name ob_refcnt = %d\n",  attr3_name->ob_refcnt );
				//~ printf( "attr3_value ob_refcnt = %d\n", attr3_value->ob_refcnt );
				//~ printf( "attr4_name ob_refcnt = %d\n",  attr4_name->ob_refcnt );
				//~ printf( "attr4_value ob_refcnt = %d\n", attr4_value->ob_refcnt );
				
				return list; 
			}
			
		}
		else
		{
			PyTypeObject* type_object = type_arg->ob_type;
			printf( "mdutils.clone ERROR: not a type obj passed (ob_type name is '%s')\n", type_object->tp_name );
		}
	}
	else printf( "mdutils.clone ERROR: NULL type obj passed\n" );
	
    return Py_BuildValue("O", NULL);
}


static PyObject *
md_convert_int_keys(PyObject *self, PyObject *args)
{
    PyObject *dict;

    if (!PyArg_ParseTuple(args, "O", &dict))
        return NULL;
	
    if( dict )
	{
		if ( PyDict_Check(dict) )
		{
			// тупой вариант: создаем новый пустой словарь, вставл€ем туда все отконвертированные пары
			PyObject* new_dict = PyDict_New(); 
			
			PyObject* key;
			PyObject* value;
			Py_ssize_t pos = 0;
			
			while( PyDict_Next(dict, &pos, &key, &value) )
			{
				if( key && PyString_Check(key) )
				{
					char* str_key = PyString_AsString(key);
					if( str_key )
					{
						int int_key = atoi(str_key);
						if( int_key )
						{
							PyObject* new_key = PyInt_FromLong( int_key );
							PyDict_SetItem(new_dict, new_key, value);
							Py_DECREF(new_key);
						}
						else
						{// ключ не приводитс€ к числу: ок, сразу нафиг (и возвращаем исходный словарь)
							int long_key = atol(str_key);
							if( long_key )
							{
								PyObject* new_key = PyLong_FromLong( long_key );
								PyDict_SetItem(new_dict, new_key, value);
								Py_DECREF(new_key);
							}
							else
							{
								printf( "mdutils.md_convert_int_keys ERROR: bad key conversion to int (was string key %s)\n", str_key );
								Py_DECREF(new_dict);
								return dict;
							}
						}
					}
					else
					{// плоха€ строка-ключ: ну нафиг (и возвращаем исходный словарь)
						printf( "mdutils.md_convert_int_keys ERROR: bad string from key (type %s)\n", key->ob_type->tp_name );
						Py_DECREF(new_dict);
						return dict;
					}
				}
				else
				{// ключ не €вл€етс€ строкой: ок, сразу нафиг (и возвращаем исходный словарь)
					printf( "mdutils.md_convert_int_keys ERROR: key is not a string (type %s)\n", key->ob_type->tp_name );
					Py_DECREF(new_dict);
					return dict;
				}
			}
			
			return new_dict;
		}
		else printf( "mdutils.md_convert_int_keys ERROR: not a dict obj passed (ob_type name is '%s')\n", dict->ob_type->tp_name );
	}
	
    return Py_BuildValue("O", NULL);
}


/////////////////////////////////////////////////////////////////

static PyMethodDef MDUtilsMethods[] = {
    {"test", md_test, METH_VARARGS, "Test func."},
    {"clone", md_clone, METH_VARARGS, "Create <count> clones of a given <obj_type>, return them packed into a list."},
    {"convert_int_keys", md_convert_int_keys, METH_VARARGS, "Convert dictionary string keys to int keys wherever possible."},
	//-------------------------------------------------
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


PyMODINIT_FUNC
initmdutils(void)
{
    (void) Py_InitModule( "mdutils", MDUtilsMethods );
}


