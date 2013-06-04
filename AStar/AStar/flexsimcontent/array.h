#pragma once

#ifndef ARRAY
#define ARRAY

class TreeNode;
extern int cpt(const char* );
extern int cpd(int );
extern int cpr();

enum localvartype
{
	TYPE_INT = 1,
	TYPE_DOUBLE = 2,
	TYPE_NODE = 3,
	TYPE_STR = 4,
	TYPE_INTARRAY = 5,
	TYPE_DOUBLEARRAY = 6,
	TYPE_NODEARRAY = 7,
	TYPE_STRARRAY = 8
};

template< class ArrayType, localvartype TypeID>
class array 
{
private:
	int size;
	ArrayType* elements;
public:
	int arraytype;
	array();
	array(int);
	~array();
	ArrayType& operator[]( int n );
	void operator=(array<ArrayType, TypeID> setto);
	void operator=(array<ArrayType, TypeID>* setto);
	void operator=(size_t _size);
	void setsize(size_t n);
	int getsize();
	void fill(ArrayType* copyfrom);
};

template<class ArrayType, localvartype TypeID>
void fillarray(array<ArrayType, TypeID>& a, ArrayType p1, ...);

typedef array<double, TYPE_DOUBLE> doublearray;
typedef array<std::string, TYPE_STR> stringarray;
typedef array<TreeNode*, TYPE_NODE> treenodearray;
typedef array<int, TYPE_INT> intarray;

template<class ArrayType, localvartype TypeID>
array<ArrayType, TypeID>::array()
{
	//cpt("array constructor no args\n");
	size = 0;
	elements = NULL;
	arraytype = TypeID;
}

template<class ArrayType, localvartype TypeID>
array<ArrayType, TypeID>::array(int _size)
{
	size = _size;
	if(size>0) elements = new ArrayType[size+1];
	else elements = NULL;
	arraytype = TypeID;
}

template<class ArrayType, localvartype TypeID>
array<ArrayType, TypeID>::~array()
{
	if(size > 0 && elements != NULL)
		delete [] elements;
}

template<class ArrayType, localvartype TypeID>
ArrayType& array<ArrayType, TypeID>::operator[]( int n )
{
	if(n >= 1 && n <= size)
		return elements[n];
	else return elements[0];
}

template<class ArrayType, localvartype TypeID>
int array<ArrayType, TypeID>::getsize(){return size;}
template<class ArrayType, localvartype TypeID>
void array<ArrayType, TypeID>::setsize(size_t _size)
{
	try{
		//cpt("array setsize method: size = ");cpd(size);cpt(" _size = ");cpd(_size);
	ArrayType* oldelements = elements;
	if(_size > 0)
		elements = new ArrayType[_size+1];
	else elements = NULL;
	int copyn= size>_size?_size:size;
	for(int i = 1; i <= copyn; i++)
		elements[i] = oldelements[i];
	if(size>0 && oldelements != NULL) delete [] oldelements;
	size = _size;
	}catch(...){cpt("Exception caught in array setsize");}
}

template<class ArrayType, localvartype TypeID>
void array<ArrayType, TypeID>::fill(ArrayType* copyfrom)
{
	try{
	for(int i = 1; i <= size; i++)
	{
		elements[i] = copyfrom[i-1];
	}
	}catch(...){;}
}

template<class ArrayType, localvartype TypeID>
void array<ArrayType, TypeID>::operator=(array<ArrayType, TypeID> setto)
{
	//cpt("Copying elements from other array ");cpr();
	setsize(setto.getsize());
	for(int i = 1; i <= size; i++)
	{
		elements[i] = setto[i];
		//cpt("Copied ");cpr();
	}
}

template<class ArrayType, localvartype TypeID>
void array<ArrayType, TypeID>::operator=(array<ArrayType, TypeID>* setto)
{
	//cpt("array operator= ");
	if(((size_t) (void*) setto) < 1000000) // if the pointer value is less that 10,000, I'm going to assume it's an integer
	{
		//cpt("size value = ");cpd((size_t) setto);cpr();
		setsize( (size_t) (void*) setto);
		//cpt("Finished resizing");

	}
	else
	{
		//cpt("Copying elements from other array ");cpr();
		setsize(setto->getsize());
		for(int i = 1; i <= size; i++)
		{
			elements[i] = (*setto)[i];
			//cpt("Copied ");cpr();
		}
	}
	//cpr();
}


template<class ArrayType, localvartype TypeID>
void array<ArrayType, TypeID>::operator=(size_t _size)
{
	if(_size <= 1000000)
		setsize(_size);
	else this->operator = ((array<ArrayType, TypeID> *) _size);
}

template<class ArrayType, localvartype TypeID>
void fillarray(array<ArrayType, TypeID>& a, ArrayType p1, ...)
{
	va_list marker;
	va_start(marker, p1);

	int size = a.getsize();
	a[1] = p1;
	for(int i=2; i <= size; i++)
	{
		ArrayType val = va_arg(marker, ArrayType);
		a[i] = val;
	}
	va_end(marker);
}

#endif