#pragma once
#include <string>
#include <vector>
#include <memory>

#ifdef FLEXSIM_ENGINE_COMPILE

#define flexsimmalloc malloc
#define flexsimfree free
//extern int EX(const char *T, const char * M, int showsystemconsole);
#include "basicmacros.h"

#endif

class TreeNode;
class CallPoint;
extern int cpt(const char* );
extern int cpd(int );
extern int cpr();

enum class VariantType : unsigned char
{
	Null = 0,
	Int = 1,
	Double = 2,
	TreeNode = 3,
	String = 4,
	IntArray = 5,
	DoubleArray = 6,
	TreeNodeArray = 7,
	StringArray = 8
};

enum class WarningType : int
{
	None = 0,
	ImproperCast,
	LabelAssertion,
	LabelAbsence,
	LabelDataChange
};

enum class WarningPolicy : int
{
	None = 0,
	SilentConsoleMessage,
	AssertiveConsoleMessage,
	ThrowException
};

class FlexSimPrivateTypes
{
	template <class, VariantType>
	friend class FlexSimArray;
	friend class Variant;
	friend class TreeNode;
	friend class SimpleDataType;

public:
	class NewDelete
	{
	public:
		void * operator new (size_t x)
		{
			void* p = flexsimmalloc(x);
			if (!p)
				throw std::bad_alloc();
			return p;
		}
			void * operator new [](size_t x) {
			void* p = flexsimmalloc(x);
			if (!p)
				throw std::bad_alloc();
			return p;
		}
		void operator delete (void* p) { flexsimfree(p); }
		void operator delete [](void* p) { flexsimfree(p); }
	};
private:
	// union member classes: a method to get around Visual Studio's non-compliance with
	// c++11: declare a super-class that has all the same data but no constructors, and 
	// use that super class as the member of the union, then down-cast as needed to get
	// to the methods, constructors, destructors, etc.
	class StringUnionMember : public NewDelete
	{
	protected:
		char* buffer;
		size_t length;
	};
	class String : public StringUnionMember
	{
	public:
		inline void construct(const char* str, size_t strLen)
		{
			buffer = reinterpret_cast<char*>(flexsimmalloc(strLen + 1));
			length = strLen;
			buffer[0] = 0;
			strncat(buffer, str, strLen + 1);
		}
		inline void move(String& from)
		{
			buffer = from.buffer;
			length = from.length;
			from.buffer = 0;
			from.length = 0;
		}
		inline void cleanup()
		{
			if (buffer)
				flexsimfree(buffer);
		}
		explicit String() { buffer = 0; length = 0; }
		explicit String(const char* str) { construct(str, strlen(str)); }
		explicit String(const char* str, bool isWeak) { buffer = const_cast<char*>(str); length = -1; }
		String(const std::string& str) { construct(str.c_str(), str.length()); }
		String(const String& str) { construct(str.buffer, str.length); }
		String(String&& str) { move(str); }
		String& operator=(String&& str)
		{
			cleanup();
			move(str);
			return *this;
		}
		~String() { cleanup(); }

		String& operator=(const String& str)
		{
			cleanup();
			construct(str.buffer, str.length);
			return *this;
		}
		String& operator=(std::string& str)
		{
			cleanup();
			construct(str.c_str(), str.length());
			return *this;
		}
		String& operator=(const char* str)
		{
			cleanup();
			construct(str, strlen(str));
			return *this;
		}

		operator const char*() const { return buffer; }
		const char* c_str() const { return buffer; }
		size_t getLength() const { return length != -1 ? length : strlen(buffer); }
		operator std::string() const { return std::string(buffer, length); }

		inline bool operator == (const std::string& other) const { return strcmp(other.c_str(), buffer) == 0; }
		inline bool operator == (const char* other) const { return strcmp(other, buffer) == 0; }
		inline bool operator != (const std::string& other) const { return strcmp(other.c_str(), buffer) != 0; }
		inline bool operator != (const char* other) const { return strcmp(other, buffer) != 0; }
	};

	template <class T>
	class SharedPtrUnionMember : public NewDelete
	{
	protected:
		T* ptr;
	};
	template <class T>
	class SharedPtr : public SharedPtrUnionMember<T>
	{
	public:
		explicit SharedPtr(T* newPtr)
		{
			ptr = newPtr;
			ptr->refCount++;
		}
		explicit SharedPtr(const SharedPtr<T>& other)
		{
			ptr = other.ptr;
			ptr->refCount++;
		}
		inline void cleanup()
		{
			ptr->refCount--;
			if (ptr->refCount == 0) {
				ptr->~T();
				flexsimfree(ptr);
			}
		}
		SharedPtr& operator = (const SharedPtr<T>& other)
		{
			if (other.ptr != ptr) {
				cleanup();
				::new (this) SharedPtr(other);// re-call the constructor on other
			}
			return *this;
		}
		SharedPtr& operator = (T* other)
		{
			if (other != ptr) {
				cleanup();
				::new (this) SharedPtr(other);// re-call the constructor on other
			}
			return *this;
		}
		~SharedPtr()
		{
			cleanup();
		}
		T* operator->() const
		{
			return ptr;
		}
	};

	template<class T>
	class Vector : public NewDelete
	{
	public:
		size_t refCount;
	private:
		T* elements;
		size_t vectorSize;
		size_t bufferCapacity;
	public:
		Vector() : elements(0), bufferCapacity(0), vectorSize(0), refCount(0)
		{}
		Vector(size_t n) : refCount(0)
		{
			bufferCapacity = vectorSize = n;
			if (n > 0) {
				elements = reinterpret_cast<T*>(flexsimmalloc(n * sizeof(T)));
				if (!elements)
					throw std::bad_alloc();
				for (size_t i = 0; i < n; i++) {
					::new (&(elements[i])) T();
				}
			}
		}
		void cleanup()
		{
			if (elements) {
				for (size_t i = 0; i < vectorSize; i++)
					elements[i].~T();
				flexsimfree(elements);
			}
		}
		~Vector()
		{
			cleanup();
		}
		template<typename Indexer>
		inline T& operator[](Indexer n)
		{
			_ASSERTE(n >= 0 && static_cast<size_t>(n) < size());
			return elements[static_cast<size_t>(n)];
		}
		inline void reserve(size_t n)
		{
			if (n > bufferCapacity) {
				bufferCapacity = n;
				T* oldElements = elements;
				elements = (T*)flexsimmalloc(bufferCapacity * sizeof(T));
				if (!elements)
					throw std::bad_alloc();
				// copy to new buffer
				for (size_t i = 0; i < vectorSize; i++) {
					elements[i] = std::move(oldElements[i]);
				}
				// delete old buffer
				if (oldElements) {
					for (size_t i = 0; i < vectorSize; i++)
						oldElements[i].~T(); // call destructor on old stuff
					flexsimfree(oldElements);
				}
			}
		}
		void push_back(T&& n)
		{
			if (vectorSize >= bufferCapacity)
				reserve(16 > bufferCapacity * 2 ? 16 : bufferCapacity * 2);
			T& element = elements[vectorSize++];
			::new (&element) T(n);
		}
		void push_back(const T& n)
		{
			if (vectorSize >= bufferCapacity)
				reserve(16 > bufferCapacity * 2 ? 16 : bufferCapacity * 2);
			T& element = elements[vectorSize++];
			::new (&element) T(n);
		}
		void pop_back()
		{
			_ASSERTE(size() > 0);
			elements[vectorSize - 1].~T();
			vectorSize--;
		}
		T& back()
		{
			_ASSERTE(size() > 0);
			return elements[vectorSize - 1];
		}
		const T& back() const
		{
			_ASSERTE(size() > 0);
			return elements[vectorSize - 1];
		}
		T& front()
		{
			_ASSERTE(size() > 0);
			return elements[0];
		}
		const T& front() const
		{
			_ASSERTE(size() > 0);
			return elements[0];
		}
		void resize(size_t n)
		{
			if (n > vectorSize) {
				if (n > bufferCapacity)
					reserve(n);
				for (size_t i = vectorSize; i < n; i++)
					::new (&(elements[i])) T();
			} else if (n < vectorSize) {
				for (size_t i = vectorSize - 1; i >= n; i--)
					elements[i].~T();
			}
			vectorSize = n;
		}
		inline void clear() { resize(0); }
		inline size_t size() const { return vectorSize; }
	};

	template<class ElementType = int, VariantType TypeId = VariantType::Int>
	class FlexSimArrayUnionMember : public NewDelete
	{
	protected:
		FlexSimPrivateTypes::SharedPtrUnionMember<FlexSimPrivateTypes::Vector<ElementType>> theArrayUnionMember;
	};
};

template<class ElementType = int, VariantType TypeId = VariantType::Int>
class FlexSimArray : public FlexSimPrivateTypes::FlexSimArrayUnionMember<ElementType, TypeId>
{
private:
	typedef FlexSimArray<ElementType, TypeId> MyType;
	typedef FlexSimPrivateTypes::Vector<ElementType> MyVecType;
	typedef FlexSimPrivateTypes::SharedPtr<MyVecType> MySharedPtrType;

#define FLEXSIM_ARRAY_DEF \
	private:\
	inline const MySharedPtrType& theArray() const\
		{ return reinterpret_cast<const MySharedPtrType&>(theArrayUnionMember); }\
	inline MySharedPtrType& theArray()\
		{ return reinterpret_cast<MySharedPtrType&>(theArrayUnionMember); }\
public:\
	VariantType elementType;\
	FlexSimArray() : elementType(TypeId) \
	{\
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(new MyVecType);\
	}\
	FlexSimArray(size_t size) : elementType(TypeId) {\
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(new MyVecType(size + 1));\
	}\
	FlexSimArray(const MyType& other) : elementType(TypeId) {\
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(other.theArray());\
	}\
	~FlexSimArray() {\
		theArray().~MySharedPtrType();\
	}\
	template <typename T> ElementType& operator[](T n) { return theArray()->operator[]((size_t)n); }\
	template <typename T> const ElementType& operator[] (T n) const { return theArray()->operator[](n); }\
	MyType& operator=(const MyType& other) { theArray() = other.theArray(); return *this; }\
	void operator=(size_t n) { theArray()->resize(n + 1); }\
	void resize(size_t n) { theArray()->resize(n + 1); }\
	size_t size() const { return theArray()->size() < 1 ? 0 : theArray()->size() - 1; }\
	void push(const ElementType& val) { \
		theArray()->push_back(val);\
		if (theArray()->size() == 1)\
			theArray()->push_back(val);\
	}\
	void pop() { theArray()->pop_back(); }\
	\
	MyType clone(const MyType& original) \
	{ \
		MyType copy(original.size()); \
		if (copy.size() > 0) {\
			for (size_t i = 0; i <= copy.size(); i++)\
				copy[i] = original[i];\
		}\
		return copy;\
	}\

	FLEXSIM_ARRAY_DEF


	typedef FlexSimArray<int, VariantType::Int> IntArray;
	typedef FlexSimArray<double, VariantType::Double> DoubleArray;
	typedef FlexSimArray<TreeNode*, VariantType::TreeNode> TreeNodeArray;
	typedef FlexSimArray<FlexSimPrivateTypes::String, VariantType::String> StringArray;
	typedef FlexSimArrayUnionMember<int, VariantType::Int> IntArrayUnionMember;
	typedef FlexSimArrayUnionMember<double, VariantType::Double> DoubleArrayUnionMember;
	typedef FlexSimArrayUnionMember<TreeNode*, VariantType::TreeNode> TreeNodeArrayUnionMember;
	typedef FlexSimArrayUnionMember<FlexSimPrivateTypes::String, VariantType::String> StringArrayUnionMember;
};

template <> 
class FlexSimArray<FlexSimPrivateTypes::String, VariantType::String> 
	: public FlexSimPrivateTypes::FlexSimArrayUnionMember<FlexSimPrivateTypes::String, VariantType::String>
{
public:
	typedef FlexSimPrivateTypes::String ElementType;
private:
	static const VariantType TypeId = VariantType::String;
	typedef FlexSimArray<ElementType, TypeId> MyType;
	typedef FlexSimPrivateTypes::Vector<ElementType> MyVecType;
	typedef FlexSimPrivateTypes::SharedPtr<MyVecType> MySharedPtrType;

	FLEXSIM_ARRAY_DEF

	void push(const char* val)
	{
		push(FlexSimPrivateTypes::String(val));
	}
	void push(const std::string& val)
	{
		push(FlexSimPrivateTypes::String(val));
	}
};

inline bool operator == (const std::string& left, const FlexSimArray<>::StringArray::ElementType& right) { return right == left; }
inline bool operator != (const std::string& left, const FlexSimArray<>::StringArray::ElementType& right) { return right != left; }

template<class ElementType, VariantType TypeId>
void fillarray(FlexSimArray<ElementType, TypeId>& a, ElementType p1, ...);

typedef FlexSimArray<>::IntArray intarray;
typedef FlexSimArray<>::DoubleArray doublearray;
typedef FlexSimArray<>::TreeNodeArray treenodearray;
typedef FlexSimArray<>::StringArray stringarray;

template<class ArrayType, VariantType TypeId>
void fillarray(FlexSimArray<ArrayType, TypeId>& a, ArrayType p1, ...)
{
	va_list marker;
	va_start(marker, p1);

	int size = a.size();
	a[1] = p1;
	for(int i=2; i <= size; i++)
	{
		ArrayType val = va_arg(marker, ArrayType);
		a[i] = val;
	}
	va_end(marker);
}

class Variant : public FlexSimPrivateTypes::NewDelete
{
public:
	VariantType type;
private:
	// a weak str ptr is one that's not owned by me, so I shouldn't deallocate it
	static const unsigned char WEAK_STR = 0x1;
	unsigned char flags;
	short reserved;// reserved for future use
	union
	{
		// union x86/x64 bytes = 8/16
		TreeNode* asTreeNode; // 4/8 bytes
		double asDouble; // 8 bytes
		int asInt; // 4 bytes
		FlexSimPrivateTypes::StringUnionMember asStringUnionMember; // 8/16 bytes 

		FlexSimArray<>::IntArrayUnionMember asIntArrayUnionMember; // 4/8 bytes
		FlexSimArray<>::DoubleArrayUnionMember asDoubleArrayUnionMember; // 4/8 bytes
		FlexSimArray<>::TreeNodeArrayUnionMember asTreeNodeArrayUnionMember; // 4/8 bytes
		FlexSimArray<>::StringArrayUnionMember asStringArrayUnionMember; // 4/8 bytes
	};

	// casters to get around Visual Studio's non-compliance with C++11 unrestricted unions
	inline const FlexSimPrivateTypes::String& asString() const
		{ return reinterpret_cast<const FlexSimPrivateTypes::String&>(asStringUnionMember); }
	inline FlexSimPrivateTypes::String& asString()
		{ return reinterpret_cast<FlexSimPrivateTypes::String&>(asStringUnionMember); }

	inline const intarray& asIntArray() const
		{ return reinterpret_cast<const intarray&>(asIntArrayUnionMember); }
	inline intarray& asIntArray()
		{ return reinterpret_cast<intarray&>(asIntArrayUnionMember); }

	inline const doublearray& asDoubleArray() const
		{ return reinterpret_cast<const doublearray&>(asDoubleArrayUnionMember); }
	inline doublearray& asDoubleArray()
		{ return reinterpret_cast<doublearray&>(asDoubleArrayUnionMember); }

	inline const treenodearray& asTreeNodeArray() const
		{ return reinterpret_cast<const treenodearray&>(asTreeNodeArrayUnionMember); }
	inline treenodearray& asTreeNodeArray()
		{ return reinterpret_cast<treenodearray&>(asTreeNodeArrayUnionMember); }

	inline const stringarray& asStringArray() const
		{ return reinterpret_cast<const stringarray&>(asStringArrayUnionMember); }
	inline stringarray& asStringArray()
		{ return reinterpret_cast<stringarray&>(asStringArrayUnionMember); }


public:
	// constructors
	Variant() : type(VariantType::Null), asInt(0), flags(0), reserved(0) {}
	Variant(const Variant& copyFrom) : flags(copyFrom.flags), reserved(0)
	{
		type = copyFrom.type;
		switch (type) {
			case VariantType::Int: asInt = copyFrom.asInt; break;
			case VariantType::Double: asDouble = copyFrom.asDouble; break;
			case VariantType::TreeNode: asTreeNode = copyFrom.asTreeNode; break;
			case VariantType::String: 
				if (copyFrom.flags & WEAK_STR)
					::new (&asString()) FlexSimPrivateTypes::String(copyFrom.asString(), true);
				else ::new (&asString()) FlexSimPrivateTypes::String(copyFrom.asString());
				break;

			case VariantType::IntArray: ::new (&asIntArray()) intarray(copyFrom.asIntArray()); break;
			case VariantType::DoubleArray: ::new (&asDoubleArray()) doublearray(copyFrom.asDoubleArray()); break;
			case VariantType::TreeNodeArray: ::new (&asTreeNodeArray()) treenodearray(copyFrom.asTreeNodeArray()); break;
			case VariantType::StringArray: ::new (&asStringArray()) stringarray(copyFrom.asStringArray()); break;
			default: asInt = 0; break;
		}
	}
	Variant(Variant&& from) : flags(from.flags), reserved(0)
	{
		type = from.type;
		switch (type) {
			case VariantType::Int: asInt = from.asInt; break;
			case VariantType::Double: asDouble = from.asDouble; break;
			case VariantType::TreeNode: asTreeNode = from.asTreeNode; break;
			case VariantType::String: ::new (&asString()) FlexSimPrivateTypes::String(std::move(from.asString())); break;
			case VariantType::IntArray: 
				::new (&asIntArray()) intarray(std::move(from.asIntArray())); 
				from.asIntArray().~intarray(); break;
			case VariantType::DoubleArray: 
				::new (&asDoubleArray()) doublearray(std::move(from.asDoubleArray()));  
				from.asDoubleArray().~doublearray(); break;
			case VariantType::TreeNodeArray: 
				::new (&asTreeNodeArray()) treenodearray(std::move(from.asTreeNodeArray())); 
				from.asTreeNodeArray().~treenodearray(); break;
			case VariantType::StringArray: 
				::new (&asStringArray()) stringarray(std::move(from.asStringArray()));  
				from.asStringArray().~stringarray(); break;
			default: asInt = 0; break;
		}
		from.type = VariantType::Null;
		from.asInt = 0;
	}

	Variant(bool val) : type(VariantType::Int), asInt(val), flags(0), reserved(0) {}
	Variant(int val) : type(VariantType::Int), asInt(val), flags(0), reserved(0) {}
	Variant(double val) : type(VariantType::Double), asDouble(val), flags(0), reserved(0) {}
	Variant(TreeNode* val) : type(VariantType::TreeNode), asTreeNode(val), flags(0), reserved(0) {}
	Variant(const std::string& val) : type(VariantType::String), flags(0), reserved(0)
	{
		::new (&asString()) FlexSimPrivateTypes::String(val);
	}
	Variant(const char* val) : type(VariantType::String), flags(0), reserved(0)
	{
		::new (&asString()) FlexSimPrivateTypes::String(val);
	}
	Variant(const FlexSimPrivateTypes::String& val) : type(VariantType::String), flags(0), reserved(0)
	{
		::new (&asString()) FlexSimPrivateTypes::String(val);
	}
	Variant(const intarray& val) : type(VariantType::IntArray), flags(0), reserved(0)
	{
		::new (&asIntArray()) intarray(val);
	}
	Variant(const doublearray& val) : type(VariantType::DoubleArray), flags(0), reserved(0)
	{
		::new (&asDoubleArray()) doublearray(val);
	}
	Variant(const treenodearray& val) : type(VariantType::TreeNodeArray), flags(0), reserved(0)
	{
		::new (&asTreeNodeArray()) treenodearray(val);
	}
	Variant(const stringarray& val) : type(VariantType::StringArray), flags(0), reserved(0)
	{
		::new (&asStringArray()) stringarray(val);
	}
private:
	Variant(const char* val, unsigned char flags) : type(VariantType::String), flags(flags), reserved(0)
	{
		::new (&asString()) FlexSimPrivateTypes::String(val, true);
	}
	void cleanup()
	{
		switch (type) {
			case VariantType::Null: case VariantType::TreeNode: case VariantType::Double: case VariantType::Int:
				break;
			case VariantType::String: 
				if (!(flags & WEAK_STR))
					asString().~String(); 
				break;
			case VariantType::IntArray: asIntArray().~intarray(); break;
			case VariantType::DoubleArray: asDoubleArray().~doublearray(); break;
			case VariantType::TreeNodeArray: asTreeNodeArray().~treenodearray(); break;
			case VariantType::StringArray: asStringArray().~stringarray(); break;
			default: {
				char errorStr[100];
				sprintf(errorStr, "Unrecognized Variant type %d. You must update headers to properly destruct this type.", static_cast<int>(type));
				//EX("Error in Variant destructor", errorStr, 1);
				break;
			}
		}
	}
public:

	~Variant()
	{
		cleanup();
	}
	
	// assignment operators
	Variant& operator = (Variant&& copyFrom)
	{
		cleanup();
		::new (this) Variant(copyFrom);
		return *this;
	}
	Variant& operator = (const Variant& copyFrom)
	{
		cleanup();
		::new (this) Variant(copyFrom);
		return *this;
	}

	Variant& operator = (int val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}
	Variant& operator = (double val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}
	Variant& operator = (TreeNode* val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}
	Variant& operator = (const std::string& val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}
	Variant& operator = (const FlexSimPrivateTypes::String& val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}
	Variant& operator = (const char* val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}

	Variant& operator = (const intarray& val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}
	Variant& operator = (const doublearray& val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}
	Variant& operator = (const treenodearray& val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}
	Variant& operator = (const stringarray& val)
	{
		cleanup();
		::new (this) Variant(val);
		return *this;
	}

	// casting operators
	operator double() const
	{
		switch (type) {
			case VariantType::Double: return asDouble;
			case VariantType::Int: return static_cast<double>(asInt);
			default: return 0.0;
		}
	}
	operator int() const
	{
		switch (type) {
			case VariantType::Double: return static_cast<int>(asDouble);
			case VariantType::Int: return asInt;
			default: return 0;
		}
	}
	operator TreeNode*() const { return type == VariantType::TreeNode ? asTreeNode : 0; }
	operator std::string() const
	{
		switch (type) {
			case VariantType::String: return std::string(asString().c_str(), asString().getLength());
			default: return std::string("");
		}
	}
	operator intarray() const
	{
		switch (type) {
			case VariantType::IntArray: return intarray(asIntArray());
			default: return intarray(0);
		}
	}
	operator doublearray() const
	{
		switch (type) {
			case VariantType::DoubleArray: return doublearray(asDoubleArray());
			default: return doublearray();
		}
	}
	operator treenodearray() const
	{
		switch (type) {
			case VariantType::TreeNodeArray: return treenodearray(asTreeNodeArray());
			default: return treenodearray(0);
		}
	}
	operator stringarray() const
	{
		switch (type) {
			case VariantType::StringArray: return stringarray(asStringArray());
			default: return stringarray(0);
		}
	}

	static Variant createWeakStr(const char* str)
	{
		return Variant(str, WEAK_STR);
	}

	bool isNumberType() const { return type == VariantType::Double || type == VariantType::Int; };
	EXPLICIT operator bool() const
	{
		switch (type) {
			case VariantType::Int: return asInt != 0;
			case VariantType::Double: return asDouble != 0;
			case VariantType::TreeNode: return asTreeNode != 0;
			case VariantType::Null: return false;
			default: return true;
		}
	}
	bool operator < (const Variant& other) const
	{
		bool isNumType = isNumberType();
		bool isOtherNumType = other.isNumberType();
		if (isNumType != isOtherNumType)
			return false;
		if (isNumType)
			return operator double() < other.operator double();
		else if (type == VariantType::String) {
			if (other.type != VariantType::String)
				return false;
			return strcmp(asString(), other.asString()) < 0;
		}
		return false;
	}
	bool operator <= (const Variant& other) const
	{
		return !operator > (other);
	}
	bool operator > (const Variant& other) const
	{
		bool isNumType = isNumberType();
		bool isOtherNumType = other.isNumberType();
		if (isNumType != isOtherNumType)
			return false;
		if (isNumType)
			return operator double() > other.operator double();
		else if (type == VariantType::String) {
			if (other.type != VariantType::String)
				return false;
			return strcmp(asString(), other.asString()) > 0;
		}
		return false;
	}
	bool operator >= (const Variant& other) const
	{
		return !operator < (other);
	}
	bool operator == (const Variant& other) const
	{
		bool isNumType = isNumberType();
		bool isOtherNumType = other.isNumberType();
		if (isNumType != isOtherNumType)
			return false;
		if (isNumType)
			return operator double() == other.operator double();
		else if (type == VariantType::String) {
			if (other.type != VariantType::String)
				return false;
			return strcmp(asString(), other.asString()) == 0;
		}
		return false;
	}
	bool operator != (const Variant& other) const
	{
		return !operator == (other);
	}
	Variant operator -() const
	{
		switch (type) {
			case VariantType::Int: return -asInt;
			case VariantType::Double: return -asDouble;
			default: return Variant();
		}
	}

#define COMPARE_NUMBER(op, numberType) \
	bool operator op (numberType& theNum) const \
	{\
		if (type == VariantType::Double) return asDouble op theNum;\
		else if (type == VariantType::Int) return asInt op static_cast<int>(theNum);\
		return false;\
	}\

#define COMPARE_NUMBER_TYPES(op)\
	COMPARE_NUMBER(op, float)\
	COMPARE_NUMBER(op, double)\
	COMPARE_NUMBER(op, char)\
	COMPARE_NUMBER(op, short)\
	COMPARE_NUMBER(op, int)\
	COMPARE_NUMBER(op, __int64)\
	COMPARE_NUMBER(op, unsigned char)\
	COMPARE_NUMBER(op, unsigned short)\
	COMPARE_NUMBER(op, unsigned int)\
	COMPARE_NUMBER(op, unsigned __int64)

	COMPARE_NUMBER_TYPES(<)
	COMPARE_NUMBER_TYPES(>)
	COMPARE_NUMBER_TYPES(<= )
	COMPARE_NUMBER_TYPES(>= )
	COMPARE_NUMBER_TYPES(== )




#ifdef FLEXSIM_ENGINE_COMPILE
	double forceLegacyDouble() const
	{
		switch (type) {
			case VariantType::Double: return asDouble;
			case VariantType::Int: return static_cast<double>(asInt);
			case VariantType::TreeNode: return ptrtodouble(asTreeNode);
			case VariantType::String: return ptrtodouble((void*)asString().c_str());
			default: return 0;
		}
	}
#endif

	// only return my pointer if it's a non-owned cstr, i.e. it won't
	// go out of scope if I'm destructed.
	const char* getWeakStr() const { return (type == VariantType::String && (flags & WEAK_STR)) ? asString().operator const char*() : 0; }
	const char* c_str() const { return (type == VariantType::String) ? asString().operator const char*() : ""; }
};

class VariantParams
{
public:
	const Variant& getParam(size_t paramNum);

#ifdef FLEXSIM_ENGINE_COMPILE
	VariantParams() : numParams(0) {}
	VariantParams(const Variant& p1) : numParams(1) {
		params[0] = &p1;
	}
	VariantParams(const Variant& p1, const Variant& p2) : numParams(2)
	{
		params[0] = &p1;
		params[1] = &p2;
	}
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3) : numParams(3)
	{
		params[0] = &p1;
		params[1] = &p2;
		params[2] = &p3;
	}
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4) : numParams(4)
	{
		params[0] = &p1;
		params[1] = &p2;
		params[2] = &p3;
		params[3] = &p4;
	}
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5) : numParams(5)
	{
		params[0] = &p1;
		params[1] = &p2;
		params[2] = &p3;
		params[3] = &p4;
		params[4] = &p5;
	}
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5,
		const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10) : numParams(10)
	{
		params[0] = &p1;
		params[1] = &p2;
		params[2] = &p3;
		params[3] = &p4;
		params[4] = &p5;
		params[5] = &p6;
		params[6] = &p7;
		params[7] = &p8;
		params[8] = &p9;
		params[9] = &p10;
	}

	void dumpToCallPoint(CallPoint& cp);

private:
	size_t numParams;
	const Variant* params[10];
#endif
};

#ifdef FLEXSIM_ENGINE_COMPILE
#undef flexsimmalloc
#undef flexsimfree
#endif