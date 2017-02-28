#pragma once

#include <string>
#include <vector>
#include <memory>
#include "basicclasses.h"

#ifdef FLEXSIM_ENGINE_COMPILE

	#define flexsimmalloc malloc
	#define flexsimfree free
	//extern int EX(const char *T, const char * M, int showsystemconsole);
	#include "basicmacros.h"

#endif

namespace Compiler {
	struct AbstractSyntaxTree;
	struct CompilerHelpers;
	struct ASTDeclareLocalVar;
	struct ClassInfo;
}
extern int cpt(const char*);
extern int cpd(int);
extern int cpr();

namespace FlexSim
{

enum class VariantType : unsigned char
{
	Null = 0,
	Number = 1,
	TreeNode = 2,
	String = 3,
	Array = 4,
	Pointer = 5,
	//IntArray = 4, No longer valid
	//DoubleArray = 5,
	//TreeNodeArray = 6,
	//StringArray = 7,
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

struct ZeroBased
{
	static const int rankOffset = 1;
};
struct OneBased
{
	static const int rankOffset = 0;
};

class FlexSimPrivateTypes
{
	template <class, VariantType>
	friend class FlexSimArray;
	friend class ::FlexSim::Variant;
	friend class ::FlexSim::TreeNode;
	friend class ::FlexSim::SimpleDataType;
	friend class ::FlexSim::NodeRef;
	friend struct Compiler::AbstractSyntaxTree;
	friend struct Compiler::CompilerHelpers;
	friend struct Compiler::ASTDeclareLocalVar;
	friend struct Compiler::ClassInfo;

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
public:
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
		void construct(const std::string& str)
		{
			construct(str.c_str(), str.length());
		}
		void construct(const char* str)
		{
			construct(str, strlen(str));
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
			if (str.buffer)
				construct(str.buffer, str.length);
			else {
				buffer = 0;
				length = 0;
			}
			return *this;
		}
		String& operator=(const std::string& str)
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

		String operator+(const String& other) const
		{
			std::string str(buffer, getLength());
			str.append(other.buffer, other.getLength());
			return String(str);
		}
		String operator+(const std::string& other) const
		{
			std::string str(buffer, getLength());
			str.append(other);
			return String(str);
		}
		String operator+(const char* other) const
		{
			std::string str(buffer, getLength());
			str.append(other);
			return String(str);
		}
		void bind(TreeNode* x);

		const char* c_str() const { return buffer; }
		size_t size() const { return getLength(); }
		size_t getLength() const { return length != -1 ? length : strlen(buffer); }
		operator std::string() const { return std::string(buffer, length); }
		Variant __getAsProperty(const char* name, unsigned index) const;
		void __setAsProperty(const char* name, unsigned index, const Variant& val);

#define COMPARE_STRING(op) \
	inline bool operator op (const std::string& other) const { return strcmp(other.c_str(), buffer) op 0; } \
	inline bool operator op (const char* other) const { return strcmp(other, buffer) op 0; } \
	inline bool operator op (const String& other) const { return strcmp(other.buffer, buffer) op 0; }

		COMPARE_STRING(==);
		COMPARE_STRING(!=);
		COMPARE_STRING(<);
		COMPARE_STRING(>);
		COMPARE_STRING(<=);
		COMPARE_STRING(>=);

#undef COMPARE_STRING
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


		template<class X>
		typename std::enable_if<std::is_move_constructible<X>::value || std::is_copy_constructible<X>::value>::type
		construct_elements(X* newElements, size_t start, size_t end)
		{
			// copy to new buffer
			for (size_t i = start; i < end; i++) {
				:: new (&newElements[i]) T();
			}
		}
		template<class X>
		typename std::enable_if<!std::is_move_constructible<X>::value && !std::is_copy_constructible<X>::value>::type
		construct_elements(X* elements, size_t start, size_t end)
		{}

		template<class X>
		typename std::enable_if<std::is_move_constructible<X>::value || std::is_copy_constructible<X>::value>::type
		move_elements(X* newElements, X* oldElements)
		{
			// copy to new buffer
			for (size_t i = 0; i < vectorSize; i++) {
				:: new (&newElements[i]) T(std::move(oldElements[i]));
			}
		}
		template<class X>
		typename std::enable_if<!std::is_move_constructible<X>::value && !std::is_copy_constructible<X>::value>::type
		move_elements(X* newElements, X* oldElements)
		{
			memcpy(newElements, oldElements, vectorSize * sizeof(T));
		}

		template<class X>
		typename std::enable_if<!std::is_trivially_destructible<X>::value>::type
		destruct_elements(X* oldElements, size_t start, size_t end)
		{
			for (size_t i = start; i < end; i++)
				oldElements[i].~T(); // call destructor on old stuff
		}

		template<class X>
		typename std::enable_if<std::is_trivially_destructible<X>::value>::type
		destruct_elements(X* oldElements, size_t start, size_t end)
		{}
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
			if (n >= 0 && static_cast<size_t>(n) < vectorSize)
				return elements[static_cast<size_t>(n)];
			else throw "Array index out of bounds";
		}

		inline void reserve(size_t n)
		{
			if (n > bufferCapacity) {
				bufferCapacity = n;
				T* oldElements = elements;
				elements = (T*)flexsimmalloc(bufferCapacity * sizeof(T));
				if (!elements)
					throw std::bad_alloc();
				if (oldElements)
					move_elements(elements, oldElements);
				// delete old buffer
				if (oldElements) {
					destruct_elements(oldElements, 0, vectorSize);
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
		T pop_back()
		{
			if (vectorSize <= 0)
				throw "Popping from empty array";
			T x = std::move(elements[vectorSize - 1]);
			elements[vectorSize - 1].~T();
			vectorSize--;
			return x;
		}
		T& back()
		{
			if (vectorSize <= 0)
				throw "Accessing element in empty array";
			return elements[vectorSize - 1];
		}
		const T& back() const
		{
			if (vectorSize <= 0)
				throw "Accessing element in empty array";
			return elements[vectorSize - 1];
		}
		T& front()
		{
			if (vectorSize <= 0)
				throw "Accessing element in empty array";
			return elements[0];
		}
		const T& front() const
		{
			if (vectorSize <= 0)
				throw "Accessing element in empty array";
			return elements[0];
		}
		void pop_front()
		{
			if (vectorSize <= 0)
				throw "Accessing element in empty array";
			for (int i = 0; i < vectorSize - 1; i++) {
				elements[i] = std::move(elements[i + 1]);
			}
			elements[vectorSize - 1].~T();
			vectorSize--;
		}
		void insert(const T& n, size_t atIndex)
		{
			if (vectorSize >= bufferCapacity)
				reserve(16 > bufferCapacity * 2 ? 16 : bufferCapacity * 2);
			::new (&(elements[vectorSize++])) T();
			for (size_t i = vectorSize - 1; i > atIndex; i--)
				elements[i] = std::move(elements[i - 1]);
			elements[atIndex] = n;
		}
		void insert(const T* n, size_t atIndex, size_t numElements)
		{
			if (vectorSize == 0)
				resize(1);

			if (atIndex < 1 || atIndex > vectorSize)
				throw "Array index out of bounds";
			
			if (vectorSize + numElements >= bufferCapacity)
				reserve(16 > bufferCapacity * 2 ? 16 : (bufferCapacity + numElements) * 2);
			// initialize new elements
			for (size_t i = 0; i < numElements; i++)
				::new (&(elements[vectorSize++])) T();

			// move existing elements into new space
			for (int i = (int)vectorSize - 1; i >= (int)atIndex + numElements; i--)
				elements[i] = std::move(elements[i - numElements]);

			// copy n to the created space
			for (int i = 0; i < numElements; i++)
				elements[atIndex + i] = n[i + 1];
		}
		void remove(size_t begin, size_t end)
		{
			if (begin >= end)
				return;
			if (end > vectorSize)
				throw "Array index out of bounds";
			size_t numToRemove = end - begin;
			for (size_t i = begin; i < vectorSize - numToRemove; i++)
				elements[i] = std::move(elements[i + numToRemove]);
			for (size_t i = vectorSize - numToRemove; i < vectorSize; i++)
				elements[i].~T();
			vectorSize -= numToRemove;
		}
		void resize(size_t n)
		{
			if (n > vectorSize) {
				if (n > bufferCapacity)
					reserve(n);
				construct_elements(elements, vectorSize, n);
			} else if (n < vectorSize) {
				destruct_elements(elements, n, vectorSize);
			}
			vectorSize = n;
		}
		T* data() { return elements; }
		inline void clear() { resize(0); }
		inline size_t size() const { return vectorSize; }
	};

	template<class ElementType = int, VariantType TypeId = VariantType::Number>
	class FlexSimArrayUnionMember : public NewDelete
	{
	protected:
		FlexSimPrivateTypes::SharedPtrUnionMember<FlexSimPrivateTypes::Vector<ElementType>> theArrayUnionMember;
	};

	struct NodeRefUnionMember
	{
		TreeNode* ref;
		NodeRef* next;
		// NodeRef is a quasi-doubly-linked list. The next member points to the next NodeRef in the list, 
		// but the prev member actually points to the address of the next member of the previous guy.
		// I do this because TreeNode has a NodeRef* refsToMe member that points to the head of the list,
		// and I want NodeRef to easily remove itself from the list, so by having prev be the address
		// of the next member of the previous NodeRef, the head's prev member can point to the node's 
		// refsToMe pointer. Then removal from the list is exactly the same if you are the head or not.
		NodeRef** prev;
	};

	struct DoubleStub
	{
		Variant __getAsProperty(const char* name, unsigned index) const;
		void __setAsProperty(const char* name, unsigned index, const Variant& val);
	};
};


/// <summary>	A class representing a "safe" pointer to a node. If a node is deleted, all NodeRef's pointing
/// 			to it will immediately be set to point to null. </summary>
/// <remarks>	Anthony.johnson, 3/18/2015. </remarks>
class NodeRef : private FlexSimPrivateTypes::NodeRefUnionMember {
	friend class TreeNode;
	friend struct Compiler::ClassInfo;
protected:
	engine_export void init(TreeNode* x);
	void cleanup()
	{
		if (prev) {
			*prev = next;
			if (next)
				next->prev = prev;
		}
		ref = nullptr;
		prev = nullptr;
		next = nullptr;
	}
public:
	~NodeRef() { cleanup(); }
	NodeRef()
	{
		ref = nullptr;
		prev = nullptr;
		next = nullptr;
	}
	NodeRef(TreeNode* x)
	{
		init(x);
	}
	NodeRef(const NodeRef& other)
	{
		init(other.ref);
	}
	NodeRef(NodeRef&& other)
	{
		ref = other.ref;
		prev = other.prev;
		next = other.next;
		if (prev) {
			*prev = this;
			if (next)
				next->prev = &next;
		} 
		other.prev = 0;
		other.next = 0;
		other.ref = 0;
	}
	NodeRef& operator=(TreeNode* x)
	{
		if (x != ref) {
			cleanup();
			init(x);
		}
		return *this;
	}
	NodeRef& operator=(const NodeRef& x) { return operator=(x.ref); }
	NodeRef& operator=(NodeRef&& x) { 
		cleanup();
		new (this) NodeRef(x);
		return *this;
	}
	engine_export NodeRef& operator=(const Variant&);
	engine_export NodeRef& operator=(const Property&);

	operator bool() const { return ref != 0; }
	bool operator !() const { return ref == 0; }
	bool operator ==(const TreeNode* other) const { return ref == other; }
	bool operator ==(const NodeRef& other) const { return ref == other.ref; }
	bool operator ==(TreeNode* other) const { return ref == other; }
	bool operator ==(NodeRef& other) const { return ref == other.ref; }
	bool operator ==(nullptr_t null) const { return ref == nullptr; }
	bool operator !=(const TreeNode* other) const { return ref != other; }
	bool operator !=(const NodeRef& other) const { return ref != other.ref; }
	bool operator !=(TreeNode* other) const { return ref != other; }
	bool operator !=(NodeRef& other) const { return ref != other.ref; }
	bool operator !=(nullptr_t null) const { return ref != nullptr; }
	operator TreeNode*() const { return ref; }
	TreeNode* get() const { return ref; }
	TreeNode* operator ->() const { return ref; }
	engine_export void bind(TreeNode* x);
	std::string toString() const;
	Variant __getAsProperty(const char* name, unsigned index) const;
	void __setAsProperty(const char* name, unsigned index, const Variant& val);

private:

	void destruct() { this->~NodeRef(); }
	void construct() { ::new(this)NodeRef(); }
	void construct(NodeRef&& other) { ::new(this)NodeRef(other); }
	void construct(const NodeRef& other) { ::new(this)NodeRef(other); }
	void construct(TreeNode* other) { ::new(this)NodeRef(other); }
};

template<class ObjType>
class ObjRef : public NodeRef
{
private:
	inline void init(ObjType* x)
	{
		if (x)
			NodeRef::init(x->holder);
		else NodeRef::init(nullptr);
	}
public:
	ObjRef() : NodeRef() {}
	ObjRef(ObjType* x) : NodeRef(x ? x->holder : 0) {}
	inline ObjRef& operator=(ObjType* x)
	{
		cleanup();
		init(x);
		return *this;
	}
	// when VS supports it, this should be explicit operator bool() {} (it's a C++0x standard but not supported as of VS2012)
	EXPLICIT operator bool() const { return get() != 0; }
	bool operator !() const { return get() == 0; }
	bool operator ==(const ObjType* other) const { return get() == other; }
	bool operator ==(const ObjRef<ObjType>& other) const { return get() == other.get(); }
	bool operator ==(ObjType* other) const { return get() == other; }
	bool operator ==(ObjRef<ObjType>& other) const { return get() == other.get(); }
	bool operator !=(const ObjType* other) const { return get() != other; }
	bool operator !=(const ObjRef<ObjType>& other) const { return get() != other.get(); }
	bool operator !=(ObjType* other) const { return get() != other; }
	bool operator !=(ObjRef<ObjType>& other) const { return get() != other.get(); }
	ObjType* operator->() const { return get(); };
	inline operator ObjType*() const
	{
		TreeNode* x = NodeRef::get();
		if (x)
			return &o(ObjType, x);
		else return 0;
	}
	inline ObjType* get() const { return operator ObjType*(); }
	void bind(TreeNode* x) { 
		switch (SimpleDataType::getBindMode()) {
		case 1: operator = (((TreeNode*)x->value)->objectAs(ObjType)); break;
		case 2: x->value = NodeRef::get(); break;
		case 4: SimpleDataType::appendToDisplayStr(nodetomodelpath(NodeRef::get(), 1)); break;
		}
		
	}
};

template<class Type = double, VariantType TypeId = VariantType::Number>
class FlexSimArray : public FlexSimPrivateTypes::FlexSimArrayUnionMember<Type, TypeId>
{
private:
	typedef FlexSimArray<Type, TypeId> ArrayType;
	typedef FlexSimPrivateTypes::Vector<Type> MyVecType;
	typedef FlexSimPrivateTypes::SharedPtr<MyVecType> MySharedPtrType;
	template <class ValType, class Enable = void>
	struct ParamTypeDefiner
	{
		typedef ValType type;
	};
	template <class ValType>
	struct ParamTypeDefiner<ValType, typename std::enable_if<!std::is_fundamental<ValType>::value>::type>
	{
		typedef const ValType& type;
	};

	typedef typename ParamTypeDefiner<Type>::type ParamType;


	public: 
	typedef Type ElementType; 
	typedef Type* iterator; 

	private:
	inline const MySharedPtrType& theArray() const
		{ return reinterpret_cast<const MySharedPtrType&>(theArrayUnionMember); }
	inline MySharedPtrType& theArray()
		{ return reinterpret_cast<MySharedPtrType&>(theArrayUnionMember); }
public:
	VariantType arrayType;
	FlexSimArray() : arrayType(TypeId) 
	{
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(new MyVecType);
	}
	FlexSimArray(size_t size) : arrayType(TypeId) {
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(new MyVecType(size + 1));
	}
	FlexSimArray(int arraySize) : arrayType(TypeId)
	{
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(new MyVecType(arraySize + 1));
	}
	FlexSimArray(const ArrayType& other) : arrayType(TypeId) {
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(other.theArray());
	}
	template <class OtherElementType, VariantType OtherTypeID>
	typename std::enable_if<std::is_convertible<OtherElementType, ElementType>::value && !std::is_same<OtherElementType, ElementType>::value>::type
		construct_generic(const FlexSimArray<OtherElementType, OtherTypeID>& other)
	{
		arrayType = TypeId;
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(new MyVecType(other.size() + 1));
		for (int i = 0; i < theArray()->size(); i++)
			operator[](i) = other[i];
	}
	template <class OtherElementType, VariantType OtherTypeID>
	FlexSimArray(typename std::enable_if<std::is_convertible<OtherElementType, ElementType>::value && !std::is_same<OtherElementType, ElementType>::value, const FlexSimArray<OtherElementType, OtherTypeID>&>::type other) : arrayType(TypeId)
	{
		construct_generic<OtherElementType, OtherTypeID>(other);
	}

	~FlexSimArray() {
		theArray().~MySharedPtrType();
	}
	void destruct() { this->~FlexSimArray(); } 
	void construct() { ::new(this)FlexSimArray(); }
	void construct(int size) { ::new(this)FlexSimArray((size_t)size); }
	void construct(const ArrayType& other) { ::new(this)FlexSimArray(other); }
	template <typename T> Type& operator[](T n) { return theArray()->operator[]((size_t)n); }
	template <typename T> const Type& operator[] (T n) const { return theArray()->operator[](n); }

	template <class OtherElementType, VariantType OtherTypeID>
	typename std::enable_if<std::is_convertible<OtherElementType, ElementType>::value && !std::is_same<OtherElementType, ElementType>::value, ArrayType&>::type
	operator =(const FlexSimArray<OtherElementType, OtherTypeID>& other)
	{
		this->~FlexSimArray();
		construct_generic<OtherElementType, OtherTypeID>(other);
		return *this;
	}
	ArrayType& operator=(const ArrayType& other) { theArray() = other.theArray(); return *this; }
	ArrayType& operator=(int n) { theArray()->resize(n + 1); return *this; }
	void resize(size_t n) { theArray()->resize(n + 1); }
	size_t size() const { return theArray()->size() < 1 ? 0 : theArray()->size() - 1; }
	ArrayType& push(ParamType val)
	{
		theArray()->push_back(val);
		if (theArray()->size() == 1)
			theArray()->push_back(val);
		return *this;
	}
	Type pop() { Type val = theArray()->back(); theArray()->pop_back(); return val; }
	Type shift() { Type val = theArray()->operator[](1); theArray()->pop_front(); return val; }
	ArrayType& unshift(ParamType val) { theArray()->insert(val, 1); return *this; }
	ArrayType& append(const ArrayType& val)
	{
		size_t startSize = size();
		size_t valSize = val.size();
		resize(startSize + val.size());
		for (int i = 1; i <= valSize; i++)
			operator[](i + startSize) = val[i];
		return *this;
	}

private:
	template <class OtherArrayType>
	static typename std::enable_if<std::is_same<OtherArrayType, ArrayType>::value && std::is_same<ElementType, Variant>::value, ArrayType>::type
	s_clone(const OtherArrayType& original)
	{ 
		ArrayType copy(original.size());
		if (copy.size() > 0) {
			for (size_t i = 0; i <= copy.size(); i++) {
				const Variant& val = original[i];
				if (val.type == VariantType::Array)
					copy[i] = ((ArrayType)original[i]).clone();
				else copy[i] = val;
			}
		}
		return copy;
	}

	template <class OtherArrayType>
	static typename std::enable_if<std::is_same<OtherArrayType, ArrayType>::value && !std::is_same<ElementType, Variant>::value, ArrayType>::type
	s_clone(const OtherArrayType& original)
	{
		ArrayType copy(original.size());
		if (copy.size() > 0) {
			for (size_t i = 0; i <= copy.size(); i++) {
				copy[i] = original[i];
			}
		}
		return copy;
	}
public:

	ArrayType clone()
	{
		return s_clone(*this);
	}
	ArrayType& splice(int from, int count)
	{
		theArray()->remove(from, from + count);
		return *this;
	}
	ArrayType& splice(int from, int count, const ArrayType& insert)
	{
		if (count > 0)
			theArray()->remove(from, from + count);
		if (insert.size() > 0)
			theArray()->insert(&insert[0], from, insert.size());
		return *this;
	}
	ArrayType slice(int begin, int end)
	{
		if (end < begin)
			return ArrayType();
		if (end > size() + 1)
			throw "Index out of bounds on array slice() method";

		int arraySize = end - begin;
		ArrayType newArray(arraySize);

		for (int i = 1; i <= arraySize; i++)
			newArray[i] = operator[](i + begin - 1);
		
		return newArray;
	}

	int indexOf(ParamType val) const
	{
		for (int i = 1; i <= size(); i++) {
			if (theArray()->operator[](i) == (Type)val)
				return i;
		}
		return -1;
	}

	ArrayType concat(const ArrayType& val)
	{
		ArrayType copy = clone();
		copy.append(val);
		return copy;
	}

	iterator begin() { return theArray()->data() + 1; } 
	iterator end() { return theArray()->data() + 1 + size(); } 

	template<class X>
	typename std::enable_if<std::is_same<Type, FlexSimPrivateTypes::String>::value && std::is_same<X, const char*>::value, ArrayType&>::type
	push(X val)
	{
		return push(FlexSimPrivateTypes::String(val));
	}
	template<class X>
	typename std::enable_if<std::is_same<Type, FlexSimPrivateTypes::String>::value && std::is_same<X, const char*>::value, ArrayType&>::type
	unshift(X val)
	{
		return unshift(FlexSimPrivateTypes::String(val));
	}

	template<class X>
	typename std::enable_if<std::is_same<Type, FlexSimPrivateTypes::String>::value && std::is_same<X, const std::string&>::value, ArrayType&>::type
	push(X val)
	{
		return push(FlexSimPrivateTypes::String(val));
	}
	template<class X>
	typename std::enable_if<std::is_same<Type, FlexSimPrivateTypes::String>::value && std::is_same<X, const std::string&>::value, ArrayType&>::type
	unshift(X val)
	{
		return unshift(FlexSimPrivateTypes::String(val));
	}
	template<class X>
	typename std::enable_if<std::is_same<Type, NodeRef>::value && std::is_same<X, TreeNode*>::value>::type
		push(X val)
	{
		push(NodeRef(val));
	}
	template<class X>
	typename std::enable_if<std::is_same<Type, NodeRef>::value && std::is_same<X, TreeNode*>::value>::type
	unshift(X val)
	{
		unshift(NodeRef(val));
	}

	int __getLength() { return (int)size(); }
	void __setLength(int size) { resize(size); }
	__declspec(property(get = __getLength, put = __setLength)) int length;

	Variant __getElementAsProperty(const char* name, unsigned index) const;
	void __setElementAsProperty(const char* name, unsigned index, const Variant& val);
	
	template<class X>
	std::string join(typename std::enable_if<std::is_same<ElementType, Variant>::value && std::is_same<X, const char*>::value, X>::type separator = nullptr)
	{
		std::string joined;
		for (int i = 1; i <= size(); i++) {
			Variant& val = operator [] (i);
			switch (val.type) {
				case VariantType::String:
					joined.append(val.c_str());
					break;
				case VariantType::Number: {
					double fVal = val;
					char buffer[200];
					if (frac(fVal) == 0)
						itoa((int)fVal, buffer, 10);
					else sprintf(buffer, "%f", fVal);
					joined.append(buffer);
					break;
				}
				case VariantType::TreeNode:{
					joined.append(((TreeNode*)val)->getPath());
					break;
				}
				case VariantType::Array:{
					joined.append("[");
					joined.append(((FlexSimArray<Variant, VariantType::Array>)val).join<const char*>(separator));
					joined.append("]");
					break;
				}
			}
			if (separator && i < size())
				joined.append(separator);
		}
		return joined;
	}

	ArrayType& reverse()
	{
		int forwardIter, backwardIter;
		for (forwardIter = 1, backwardIter = (int)size(); forwardIter < backwardIter; forwardIter++, backwardIter--) {
			ElementType temp = operator [](forwardIter);
			operator[](forwardIter) = operator[](backwardIter);
			operator[](backwardIter) = temp;
		}
		return *this;
	}

	template<class X>
	ArrayType& fill(typename std::enable_if<std::is_same<ElementType, Variant>::value && std::is_same<X, const Variant&>::value, X>::type filler)
	{
		for (int i = 0; i <= size(); i++) {
			switch (filler.type) {
				case VariantType::Number:
				case VariantType::TreeNode:
				case VariantType::String:
					operator[](i) = filler;
					break;
				case VariantType::Array: operator[](i) = ((FlexSimArray<Variant, VariantType::Array>)filler).clone(); break;
			}
		}
		return *this;
	}

	typedef FlexSimArray<Variant, VariantType::Array> VariantArray;
	typedef FlexSimArrayUnionMember<Variant, VariantType::Array> VariantArrayUnionMember;
};

template<class ElementType, VariantType TypeId>
void fillarray(FlexSimArray<ElementType, TypeId>& a, ElementType p1, ...);

typedef FlexSimArray<>::VariantArray intarray;
typedef FlexSimArray<>::VariantArray doublearray;
typedef FlexSimArray<>::VariantArray treenodearray;
typedef FlexSimArray<>::VariantArray stringarray;
typedef FlexSimArray<>::VariantArray Array;

template<class ArrayType, VariantType TypeId>
void fillarray(FlexSimArray<ArrayType, TypeId>& a, ArrayType p1, ...)
{
	va_list marker;
	va_start(marker, p1);

	int size = (int)a.size();
	a[1] = p1;
	for(int i=2; i <= size; i++)
	{
		ArrayType val = va_arg(marker, ArrayType);
		a[i] = val;
	}
	va_end(marker);
}

template<class ArrayType, VariantType TypeId>
int arraysize(FlexSimArray<ArrayType, TypeId>& a) { return (int)a.size(); }


struct engine_export PropertyBinding : public FlexSimPrivateTypes::NewDelete
{
	class UnknownClass{};
	typedef Variant(UnknownClass::*Getter)(const char*, unsigned, bool);
	typedef void (UnknownClass::*Setter)(const char*, unsigned, const Variant&);


	const char* name = nullptr;
	const char* typeName = nullptr;
	// version should be used in the future to update models from older versions to 
	// the latest version by updating code to use # property syntax for property 
	// name collisions when new properties are added.
	// major version times 100 plus minor version times 10 plus revision (18.3 should thus be 1830)
	unsigned int version = 0;
	unsigned int id = 0;
	Getter getter;
	Setter setter;
	bool dieHard = false;
	PropertyBinding() {}
	template<class GetterType, class SetterType>
	PropertyBinding(GetterType getter, SetterType setter)
		: getter(force_cast<Getter>(getter)), setter(force_cast<Setter>(setter))
	{}

	virtual Variant get(void* owner) const;
	virtual void set(void* owner, const Variant& val) const;

	static unsigned calculateNameHash(const char* name);

	virtual bool isStatic() { return false; }
};

struct engine_export Property
{
	void* owner;
	const PropertyBinding* binding;
	Property(const PropertyBinding* binding, void* owner) : binding(binding), owner(owner) {}

	const Variant& operator = (const Variant& val);
	int            operator = (int val);
	size_t            operator = (size_t val);
	double         operator = (double val);
	treenode       operator = (treenode val);
	const char*    operator = (const char* val);
	const std::string&    operator = (const std::string& val);
	Array		   operator = (const Array& val);
	const FlexSimPrivateTypes::String& operator =(const FlexSimPrivateTypes::String& val);

	operator Variant       () const;
	operator int() const;
	operator size_t() const;
	operator double() const;
	operator treenode      () const;
	operator const char*   () const;
	operator std::string() const;
	operator Array		   () const;
	operator FlexSimPrivateTypes::String() const;

	Variant& operator[](int index) const;

	Variant getProperty(const char* propName, unsigned nameHash, bool dieHard);
	void setProperty(const char* propName, unsigned nameHash, const Variant& val);

#define DEFINE_PROPERTY_COMPARE_OP(op) \
	template <class CompareType> \
	typename std::enable_if<std::is_fundamental<CompareType>::value || std::is_pointer<CompareType>::value, bool>::type \
	operator op (CompareType val) const { return ((CompareType)*this) op val; } \
	template <class CompareType> \
	typename std::enable_if<!std::is_fundamental<CompareType>::value && !std::is_pointer<CompareType>::value && !std::is_base_of<Property, CompareType>::value, bool>::type \
	operator op (const CompareType& val) const { return operator CompareType() op val; } \
	template <class CompareType> \
	typename std::enable_if<std::is_base_of<Property, CompareType>::value, bool>::type \
	operator op (const CompareType& val) const { return operator Variant() op val.operator Variant(); } \

	DEFINE_PROPERTY_COMPARE_OP(==)
	DEFINE_PROPERTY_COMPARE_OP(!=)
	DEFINE_PROPERTY_COMPARE_OP(<)
	DEFINE_PROPERTY_COMPARE_OP(<=)
	DEFINE_PROPERTY_COMPARE_OP(>)
	DEFINE_PROPERTY_COMPARE_OP(>=)

#define DEFINE_PROPERTY_MATH_OP(op) \
	template <class OperandType> \
	typename std::enable_if<std::is_fundamental<OperandType>::value || std::is_pointer<OperandType>::value, OperandType>::type \
	operator op (OperandType val) const { return ((OperandType)*this) op val; } \
	template <class OperandType> \
	typename std::enable_if<!std::is_fundamental<OperandType>::value && !std::is_pointer<OperandType>::value && !std::is_base_of<Property, OperandType>::value, OperandType>::type \
	operator op (const OperandType& val) const { return ((OperandType)*this) op val; } \
	template <class OperandType> \
	typename std::enable_if<std::is_base_of<Property, OperandType>::value, OperandType>::type \
	operator op (const OperandType& val) const { return operator Variant() op val.operator Variant(); } \

	DEFINE_PROPERTY_MATH_OP(+)
	DEFINE_PROPERTY_MATH_OP(-)
	DEFINE_PROPERTY_MATH_OP(*)
	DEFINE_PROPERTY_MATH_OP(/)


#define DEFINE_PROPERTY_MATH_ASSIGNMENT_OP(op, mathOp) \
	template <class OperandType> \
	typename std::enable_if<std::is_fundamental<OperandType>::value || std::is_pointer<OperandType>::value, void>::type \
	operator op (OperandType val) { operator = (((OperandType)*this) mathOp val); } \
	template <class OperandType> \
	typename std::enable_if<!std::is_fundamental<OperandType>::value && !std::is_pointer<OperandType>::value && !std::is_base_of<Property, OperandType>::value, void>::type \
	operator op (const OperandType& val) { operator = (((OperandType)*this) mathOp val); } \
	template <class OperandType> \
	typename std::enable_if<std::is_base_of<Property, OperandType>::value, void>::type \
	operator op (const OperandType& val) { operator = (operator Variant() mathOp val.operator Variant()); } \

	DEFINE_PROPERTY_MATH_ASSIGNMENT_OP(+=, +)
	DEFINE_PROPERTY_MATH_ASSIGNMENT_OP(-=, -)
	DEFINE_PROPERTY_MATH_ASSIGNMENT_OP(*=, *)
	DEFINE_PROPERTY_MATH_ASSIGNMENT_OP(/=, /)

	Variant operator ++();
	Variant operator --();

};

#define DEFINE_GLOBAL_PROPERTY_COMPARE_OP(op, otherOp) \
	template <class CompareType> \
	typename std::enable_if<std::is_fundamental<CompareType>::value || std::is_pointer<CompareType>::value, bool>::type \
	operator op (CompareType left, const Property& right) { return right. operator otherOp (left); } \
	template <class CompareType> \
	typename std::enable_if<!std::is_fundamental<CompareType>::value && !std::is_pointer<CompareType>::value && !std::is_base_of<Property, CompareType>::value, bool>::type \
	operator op (const CompareType& left, const Property& right) { return right.operator otherOp (left); }

DEFINE_GLOBAL_PROPERTY_COMPARE_OP(==, == )
DEFINE_GLOBAL_PROPERTY_COMPARE_OP(!=, != )
DEFINE_GLOBAL_PROPERTY_COMPARE_OP(<, >)
DEFINE_GLOBAL_PROPERTY_COMPARE_OP(<=, >= )
DEFINE_GLOBAL_PROPERTY_COMPARE_OP(>, <)
DEFINE_GLOBAL_PROPERTY_COMPARE_OP(>= , <=)


#define DEFINE_GLOBAL_PROPERTY_MATH_OP(op) \
	template <class OperandType> \
	typename std::enable_if<std::is_fundamental<OperandType>::value || std::is_pointer<OperandType>::value, OperandType>::type \
	operator op (OperandType left, const Property& right) { return right.operator op(left); } \
	template <class OperandType> \
	typename std::enable_if<!std::is_fundamental<OperandType>::value && !std::is_pointer<OperandType>::value && !std::is_base_of<Property, OperandType>::value, OperandType>::type \
	operator op (const OperandType& left, const Property& right) { return right.operator op(left); }

DEFINE_GLOBAL_PROPERTY_MATH_OP(+)
DEFINE_GLOBAL_PROPERTY_MATH_OP(*)


template <class OperandType>
typename std::enable_if<std::is_fundamental<OperandType>::value || std::is_pointer<OperandType>::value, bool>::type
operator - (OperandType left, const Property& right) { return -(right.operator -(left)); }
template <class OperandType>
typename std::enable_if<!std::is_fundamental<OperandType>::value && !std::is_pointer<OperandType>::value && !std::is_base_of<Property, OperandType>::value, bool>::type
operator - (const OperandType& left, const Property& right) { return right.operator -(left); }

template <class OperandType>
typename std::enable_if<std::is_fundamental<OperandType>::value || std::is_pointer<OperandType>::value, bool>::type
operator / (OperandType left, const Property& right) { return 1.0 / (right.operator /(left)); }
template <class OperandType>
typename std::enable_if<!std::is_fundamental<OperandType>::value && !std::is_pointer<OperandType>::value && !std::is_base_of<Property, OperandType>::value, bool>::type
operator / (const OperandType& left, const Property& right) { return 1.0 / (right.operator / (left)); }


struct engine_export SelfBoundProperty : public Property
{
	PropertyBinding localBinding;
	template<class GetterType, class SetterType>
	SelfBoundProperty(GetterType getter, SetterType setter, void* owner, unsigned id)
		: localBinding(getter, setter), Property(&localBinding, owner)
	{
		localBinding.id = id;
	}
};

class Variant : public FlexSimPrivateTypes::NewDelete
{
public:
	VariantType type;
	friend struct Compiler::ClassInfo;
	friend class TreeNode;
protected:
	// a weak str ptr is one that's not owned by me, so I shouldn't deallocate it
	static const unsigned char WEAK_STR = 0x1;
	unsigned char flags;
	short reserved;// reserved for future use
	TreeNode* boundToNode = nullptr;
	union
	{
		// union x86/x64 bytes = 12/24
		FlexSimPrivateTypes::NodeRefUnionMember asTreeNodeUnionMember; // 12/24 bytes
		double asNumber; // 8 bytes
		void* asPointer; // 4/8 bytes
		FlexSimPrivateTypes::StringUnionMember asStringUnionMember; // 8/16 bytes 
		FlexSimArray<>::VariantArrayUnionMember asVariantArrayUnionMember; // 4/8 bytes
	};
	// casters to get around Visual Studio's non-compliance with C++11 unrestricted unions
	inline const NodeRef& asTreeNode() const
		{ return reinterpret_cast<const NodeRef&>(asTreeNodeUnionMember); }
	inline NodeRef& asTreeNode()
		{ return reinterpret_cast<NodeRef&>(asTreeNodeUnionMember); }

	inline const FlexSimPrivateTypes::String& asString() const
		{ return reinterpret_cast<const FlexSimPrivateTypes::String&>(asStringUnionMember); }
	inline FlexSimPrivateTypes::String& asString()
		{ return reinterpret_cast<FlexSimPrivateTypes::String&>(asStringUnionMember); }
	inline const Array& asArray() const
		{ return reinterpret_cast<const Array&>(asVariantArrayUnionMember); }
	inline Array& asArray()
		{ return reinterpret_cast<Array&>(asVariantArrayUnionMember); }

	engine_export void applyToBoundNode();
	inline void checkApplyToBoundNode()
	{
		if (boundToNode)
			applyToBoundNode();
	}
public:
	engine_export void bind(TreeNode* x);

#pragma region constructors
	// constructors
	Variant() : type(VariantType::Null), asNumber(0.0), flags(0), reserved(0) {}
	Variant(const Variant& copyFrom) : flags(copyFrom.flags), reserved(0)
	{
		type = copyFrom.type;
		switch (type) {
			case VariantType::Number: asNumber = copyFrom.asNumber; break;
			case VariantType::TreeNode: new (&asTreeNode()) NodeRef(copyFrom.asTreeNode()); break;
			case VariantType::String: 
				if (copyFrom.flags & WEAK_STR)
					::new (&asString()) FlexSimPrivateTypes::String(copyFrom.asString().c_str(), true);
				else ::new (&asString()) FlexSimPrivateTypes::String(copyFrom.asString());
				break;

			case VariantType::Array: ::new (&asArray()) Array(copyFrom.asArray()); break;
			case VariantType::Pointer: asPointer = copyFrom.asPointer; break;
			default: asNumber = 0; break;
		}
	}
	Variant(Variant&& from) : flags(from.flags), reserved(0)
	{
		type = from.type;
		switch (type) {
			case VariantType::Number: asNumber = from.asNumber; break;
			case VariantType::TreeNode: 
				new (&asTreeNode()) NodeRef(std::move(from.asTreeNode()));
				from.asTreeNode().~NodeRef();
				break;
			case VariantType::String: ::new (&asString()) FlexSimPrivateTypes::String(std::move(from.asString())); break;
			case VariantType::Array:
				::new (&asArray()) Array(std::move(from.asArray()));
				from.asArray().~Array();
				break;
			case VariantType::Pointer: asPointer = from.asPointer; break;
			default: asNumber = 0; break;
		}
		from.type = VariantType::Null;
		from.asNumber = 0;
		boundToNode = from.boundToNode;
	}

	Variant(bool val) :				type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(int val) :				type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(unsigned int val) :		type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(short val) :			type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(unsigned short val) :	type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(char val) :				type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(unsigned char val) :	type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(unsigned __int64 val) :	type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(__int64 val) :			type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(double val) :			type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	Variant(float val) :			type(VariantType::Number), asNumber((double)val), flags(0), reserved(0) {}
	explicit Variant(void* val) :	type(VariantType::Pointer), asPointer(val), flags(0), reserved(0) {}

	Variant(TreeNode* val) : type(VariantType::TreeNode), flags(0), reserved(0) 
	{
		::new (&asTreeNode()) NodeRef(val);
	}
	Variant(const NodeRef& val) : type(VariantType::TreeNode), flags(0), reserved(0)
	{
		::new (&asTreeNode()) NodeRef(val);
	}
	Variant(const std::string& val) : type(VariantType::String), flags(0), reserved(0)
	{
		::new (&asString()) FlexSimPrivateTypes::String(val);
	}
	Variant(const char* val) : type(VariantType::String), flags(0), reserved(0)
	{
		::new (&asString()) FlexSimPrivateTypes::String(val);
	}
	engine_export Variant(const wchar_t * val);
	Variant(const FlexSimPrivateTypes::String& val) : type(VariantType::String), flags(0), reserved(0)
	{
		::new (&asString()) FlexSimPrivateTypes::String(val);
	}
	Variant(const Array& val) : type(VariantType::Array), flags(0), reserved(0)
	{
		::new (&asArray()) Array(val);
	}

	class engine_export Hash
	{
	public:
		size_t operator() (const Variant& pullerKey);
	};

	class engine_export KeyEqual
	{
	public:
		typedef Variant value_type;
		bool operator() (const Variant& a, const Variant& b);
	};
	class engine_export Less
	{
	public:
		typedef Variant value_type;
		bool operator() (const Variant& a, const Variant& b) { return a < b;};
	};
private:
	Variant(const char* val, unsigned char flags) : type(VariantType::String), flags(flags), reserved(0)
	{
		::new (&asString()) FlexSimPrivateTypes::String(val, true);
	}
	void cleanup()
	{
		switch (type) {
			case VariantType::Null: case VariantType::Number: case VariantType::Pointer:
				break;
			case VariantType::String: 
				if (!(flags & WEAK_STR))
					asString().~String(); 
				break;
			case VariantType::TreeNode: asTreeNode().~NodeRef(); break;
			case VariantType::Array: asArray().~Array(); break;
			default: {
				_ASSERT_EXPR(0, L"Variant being cleaned up has not been constructed");
				char errorStr[100];
				sprintf(errorStr, "Unrecognized Variant type %d. You must update headers to properly destruct this type.", static_cast<int>(type));
				//EX("Error in Variant destructor", errorStr, 1);
				break;
			}
		}
	}

#pragma endregion Contains both public and private constructors

public:

	~Variant()
	{
		cleanup();
	}
	
#pragma region assignment operators

	// I have to explicitly define the move assignment operator because I have to use std::move()
	Variant& operator = (Variant&& copyFrom)
	{
		cleanup();
		TreeNode* saveBound = boundToNode;
		::new (this) Variant(std::move(copyFrom));
		boundToNode = saveBound;
		checkApplyToBoundNode();
		return *this;
	}

#define DEFINE_ASSIGNMENT_OPERATOR(ValType) \
	Variant& operator = (ValType copyFrom) \
		{ \
			cleanup(); \
			TreeNode* saveBound = boundToNode; \
			::new (this) Variant(copyFrom); \
			boundToNode = saveBound; \
			checkApplyToBoundNode(); \
			return *this; \
		}\

	DEFINE_ASSIGNMENT_OPERATOR(const Variant&)
	DEFINE_ASSIGNMENT_OPERATOR(int)
	DEFINE_ASSIGNMENT_OPERATOR(unsigned int)
	DEFINE_ASSIGNMENT_OPERATOR(short)
	DEFINE_ASSIGNMENT_OPERATOR(unsigned short)
	DEFINE_ASSIGNMENT_OPERATOR(__int64)
	DEFINE_ASSIGNMENT_OPERATOR(unsigned __int64)
	DEFINE_ASSIGNMENT_OPERATOR(double)
	DEFINE_ASSIGNMENT_OPERATOR(float)
	DEFINE_ASSIGNMENT_OPERATOR(TreeNode*)
	DEFINE_ASSIGNMENT_OPERATOR(const NodeRef&)
	DEFINE_ASSIGNMENT_OPERATOR(const std::string&)
	DEFINE_ASSIGNMENT_OPERATOR(const FlexSimPrivateTypes::String&)
	DEFINE_ASSIGNMENT_OPERATOR(const char*)
	DEFINE_ASSIGNMENT_OPERATOR(const Array&)
	DEFINE_ASSIGNMENT_OPERATOR(void*)

	Variant& operator =(const Property& other) { operator = ((Variant)other); return *this; }

#pragma endregion Contains assignment operators for every VariantType and other Variants

#pragma region casting operators

#define DEFINE_NUMBER_CAST(NumberType) \
	operator NumberType() const \
		{ \
		switch (type) { \
			case VariantType::Number: return static_cast<NumberType>(asNumber); \
			case VariantType::Array: return static_cast<NumberType>(asArray().size() > 0 ? asArray()[1] : 0); \
			default: return static_cast<NumberType>(0.0); \
			} \
		} \

	DEFINE_NUMBER_CAST(double)
	DEFINE_NUMBER_CAST(float)
	DEFINE_NUMBER_CAST(int)
	DEFINE_NUMBER_CAST(unsigned int)
	DEFINE_NUMBER_CAST(unsigned char)
	DEFINE_NUMBER_CAST(short)
	DEFINE_NUMBER_CAST(unsigned short)
	DEFINE_NUMBER_CAST(__int64)
	DEFINE_NUMBER_CAST(unsigned __int64)

	operator TreeNode*() const
	{
		switch (type) {
			case VariantType::TreeNode: return asTreeNode();
			case VariantType::Array: return (asArray().size() > 0 ? asArray()[1] : 0);;
			default: return 0;
		}
	}
	operator NodeRef() const
	{
		switch (type) {
			case VariantType::TreeNode: return asTreeNode();
			case VariantType::Array: return (asArray().size() > 0 ? asArray()[1].operator NodeRef() : NodeRef());
			default: return 0;
		}
	}
	operator std::string() const
	{
		switch (type) {
			case VariantType::String: return std::string(asString().c_str(), asString().getLength());
			case VariantType::Array:
				if (asArray().size() > 0) {
					auto& element = asArray()[1];
					return std::string(element.c_str());
				} else return std::string("");
				break;
			default: return std::string("");
		}
	}
	operator FlexSimPrivateTypes::String() const
	{
		switch (type) {
		case VariantType::String: 
			if (flags & WEAK_STR)
				return FlexSimPrivateTypes::String(asString().c_str());
			else return asString();
		default: return FlexSimPrivateTypes::String("");
		}
	}
	operator Array() const
	{
		switch (type) {
			case VariantType::Null: return Array();
			default: {
				Array temp;
				temp.push(*this);
				return temp;
			}
			case VariantType::Array: return asArray();
		}
	}
	explicit operator void*() const
	{
		switch (type) {
		case VariantType::Pointer: return asPointer;
		default: return 0;
		}
	}

	int size() const
	{
		switch (type) {
		case VariantType::Array: return (int)asArray().size();
		case VariantType::Null: return 0;
		default: return 1;
		}
	}
	
	Variant& operator [] (int index)
	{
		switch (type) {
		case VariantType::Array:
			return asArray()[index];
		case VariantType::TreeNode:
		case VariantType::Number:
		case VariantType::String:
			if (index != 1)
				throw "Array index out of bounds";
			return *this;
		default: throw "Invalid variant type used with [] array operator";
		}
	}
	const Variant& operator [] (int index) const
	{
		return ((Variant*)this)->operator [](index);
	}
	

	EXPLICIT operator bool() const
	{
		switch (type) {
		case VariantType::Number: return asNumber != 0.0;
		case VariantType::TreeNode: return asTreeNode().get() != nullptr;
		case VariantType::Pointer: return asPointer != nullptr;
		case VariantType::Null: return false;
		default: return true;
		}
	}
	bool operator !() const { return !operator bool(); }
#pragma endregion

	static Variant createWeakStr(const char* str)
	{
		return Variant(str, WEAK_STR);
	}
	Variant& ownWeakStr()
	{
		if (type == VariantType::String && (flags & WEAK_STR))
			this->operator = (c_str());
		return *this;
	}

	inline bool isNumberType() const { return type == VariantType::Number; };
	

#pragma region Variant comparisons

	bool operator < (const Variant& other) const
	{
		if (type == VariantType::Number && other.type == VariantType::Number)
			return asNumber < other.asNumber;
		else if (type == VariantType::String && other.type == VariantType::String) {
			if (other.type != VariantType::String)
				return false;
			return strcmp(asString().c_str(), other.asString().c_str()) < 0;
		} else if (type == VariantType::Null && (other.type == VariantType::Number && other.asNumber != 0.0))
			return 0.0 < other.asNumber; 
		else if (other.type == VariantType::Null && (type == VariantType::Number && asNumber != 0.0))
			return asNumber < 0.0;
		return false;
	}
	bool operator <= (const Variant& other) const
	{
		return !operator > (other);
	}
	bool operator > (const Variant& other) const
	{
		return other.operator < (*this);
	}
	bool operator >= (const Variant& other) const
	{
		return !operator < (other);
	}
	bool operator == (const Variant& other) const
	{
		if (type != other.type) {
			if ((type == VariantType::Number || type == VariantType::TreeNode) 
					&& (other.type == VariantType::Number || other.type == VariantType::TreeNode))
				return forceLegacyDouble() == 0 && other.forceLegacyDouble() == 0;
			else return false;
		}

		switch (type) {
		case VariantType::Null: return true;
		case VariantType::Number: return asNumber == other.asNumber;
		case VariantType::String: return strcmp(asString().c_str(), other.asString().c_str()) == 0;
		case VariantType::TreeNode: return asTreeNode() == other.asTreeNode();
		case VariantType::Pointer: return asPointer == other.asPointer;
		}
		return false;
	}
	bool operator == (TreeNode* other) const
	{
		return operator TreeNode*() == other;
	}
	bool operator != (TreeNode* other) const
	{
		return operator TreeNode*() != other;
	}
	bool operator != (const Variant& other) const
	{
		return !operator == (other);
	}
	int operator &(int other) const
	{
		if (type == VariantType::Number)
			return operator int() & other;
		return 0;
	}
	int operator |(int other) const
	{
		if (type == VariantType::Number)
			return operator int() | other;
		return 0;
	}
	bool operator == (void* other) const
	{
		return operator void*() == other;
	}
	bool operator != (void* other) const
	{
		return operator void*() != other;
	}

#pragma endregion Variant compared to Variant

	Variant operator -() const
	{
		switch (type) {
			case VariantType::Number: return -asNumber;
			default: return Variant();
		}
	}
	Variant& operator +=(double val)
	{
		if (type == VariantType::Number)
			asNumber += val;
		return *this;
	}
	Variant& operator +=(const char* val)
	{
		if (type == VariantType::String) {
			std::string temp = asString();
			temp.append(val);
			asString() = temp;
		}
		return *this;
	}
	Variant& operator +=(const std::string& val)
	{
		if (type == VariantType::String) {
			std::string temp = asString();
			temp.append(val);
			asString() = temp;
		}
		return *this;
	}
	Variant& operator +=(const Variant& val)
	{
		if (val.type == VariantType::Number)
			return operator += ((double)val);
		else if (val.type == VariantType::String)
			return operator += (val.c_str());
		throw "Invalid operator type in Variant += assignment";
	}
	Variant& operator -=(double val)
	{
		if (type == VariantType::Number)
			asNumber -= val;
		return *this;
	}
	Variant& operator *=(double val)
	{
		if (type == VariantType::Number)
			asNumber *= val;
		return *this;
	}
	Variant& operator /=(double val)
	{
		if (type == VariantType::Number)
			asNumber /= val;
		return *this;
	}

#pragma region string comparisons

#define COMPARE_STRING(op, inType) \
	bool operator op (inType str) const \
	{\
		if (type == VariantType::String) \
			return asString() op str; \
		return false; \
	}\

#define COMPARE_STRING_PAIR(op) \
	COMPARE_STRING(op, const std::string&); \
	COMPARE_STRING(op, const char*);

	COMPARE_STRING_PAIR(== )
		COMPARE_STRING_PAIR(!= )
		COMPARE_STRING_PAIR(> )
		COMPARE_STRING_PAIR(< )
		COMPARE_STRING_PAIR(>= )
		COMPARE_STRING_PAIR(<= )

#undef COMPARE_STRING_PAIR
#undef COMPARE_STRING

#pragma endregion Variant compareOp stringType (char* or std::string)


#define FOR_ALL_NUMBER_TYPES(macro, p1)\
	macro(float, p1)\
	macro(double, p1)\
	macro(char, p1)\
	macro(short, p1)\
	macro(int, p1)\
	macro(__int64, p1)\
	macro(unsigned char, p1)\
	macro(unsigned short, p1)\
	macro(unsigned int, p1)\
	macro(unsigned __int64, p1)

#define FOR_ALL_NUMBER_TYPES_2(macro, p1, p2)\
	macro(float, p1, p2)\
	macro(double, p1, p2)\
	macro(char, p1, p2)\
	macro(short, p1, p2)\
	macro(int, p1, p2)\
	macro(__int64, p1, p2)\
	macro(unsigned char, p1, p2)\
	macro(unsigned short, p1, p2)\
	macro(unsigned int, p1, p2)\
	macro(unsigned __int64, p1, p2)

#pragma region number comparisons

#define COMPARE_NUMBER_1(numberType, op, defaultVal) \
	bool operator op (numberType theNum) const \
	{\
		if (type == VariantType::Number || (type == VariantType::Null && theNum != 0)) return asNumber op theNum; \
		return defaultVal; \
	}\

#define COMPARE_NUMBER_2(numberType, op, defaultVal) \
	bool operator op (numberType theNum) const \
	{\
		if (type == VariantType::Number) return asNumber op theNum; \
		if (type == VariantType::TreeNode && theNum == 0) return operator TreeNode*() op nullptr; \
		return defaultVal; \
	}\

#define COMPARE_NUMBER_TYPES_1(op, defaultVal)\
	FOR_ALL_NUMBER_TYPES_2(COMPARE_NUMBER_1, op, defaultVal)
#define COMPARE_NUMBER_TYPES_2(op, defaultVal)\
	FOR_ALL_NUMBER_TYPES_2(COMPARE_NUMBER_2, op, defaultVal)

		COMPARE_NUMBER_TYPES_1(<, false)
		COMPARE_NUMBER_TYPES_1(>, false)
		COMPARE_NUMBER_TYPES_1(<=, false)
		COMPARE_NUMBER_TYPES_1(>=, false)
		COMPARE_NUMBER_TYPES_2(==, false)
		COMPARE_NUMBER_TYPES_2(!=, true)

#undef COMPARE_NUMBER
#undef COMPARE_NUMBER_TYPES

#pragma endregion Variant compare numberType (float, double, etc)


#pragma region binary operators

#define BINARY_NUM_OP(numberType, op)\
	double operator op (numberType num) const\
	{\
		if (type == VariantType::Number)\
			return (double)(asNumber op num);\
		return (double)num;\
	}



	

	// Variant op numberType
	FOR_ALL_NUMBER_TYPES(BINARY_NUM_OP, +)
	FOR_ALL_NUMBER_TYPES(BINARY_NUM_OP, -)
	FOR_ALL_NUMBER_TYPES(BINARY_NUM_OP, *)
	FOR_ALL_NUMBER_TYPES(BINARY_NUM_OP, /)

	// Variant op Variant (+ operator deals with strings
	Variant operator + (const Variant& other) const
	{
		if (type == VariantType::Number && other.type == VariantType::Number) {
			return Variant(asNumber + other.asNumber);
		} else if (type == VariantType::String && other.type == VariantType::String) {
			return Variant(asString() + other.asString());
		}

		return Variant();
	}

#define BINARY_VARIANT_OP(op)\
	double operator op (const Variant& other) const\
	{\
		if (type == VariantType::Number) return asNumber op other.asNumber;\
		return Variant();\
	}

	// More Variant op Variant
	BINARY_VARIANT_OP(-)
	BINARY_VARIANT_OP(*)
	BINARY_VARIANT_OP(/)

	int operator % (int right) const { return operator int() % right; }
	int operator % (const Variant& right) const { return operator int() % right.operator int(); }

	// Variant op string
	Variant operator + (const std::string& other) const
	{
		if (type == VariantType::String)
			return Variant(asString() + other);
		return Variant();
	}

	Variant operator + (const char* other) const
	{
		if (type == VariantType::String)
			return Variant(asString() + other);
		return Variant();
	}

#undef BINARY_VARIANT_OP
#undef ALL_BINARY_NUM_OPS
#undef BINARY_NUM_OP

#pragma endregion Variant op numberType, Variant op Variant, Variant op stringType

#pragma region unary operators
	double operator ++()
	{
		if (type == VariantType::Number)
			return ++asNumber;
		return 0.0;
	}
	double operator ++(int)
	{
		if (type == VariantType::Number)
			return asNumber++;
		return 0.0;
	}
	double __postFixIncrement() { return (*this)++; }
	double operator --()
	{
		if (type == VariantType::Number)
			return --asNumber;
		return 0.0;
	}
	double operator --(int)
	{
		if (type == VariantType::Number)
			return asNumber--;
		return 0.0;
	}
	double __postFixDecrement() { return (*this)--; }
#undef UNARY_NUM_OP
#pragma endregion ++, --, pre and post

	TreeNode* operator ->() { return operator treenode(); }

	double forceLegacyDouble() const
	{
		switch (type) {
			case VariantType::Number: return asNumber;
			case VariantType::TreeNode: return ptrtodouble(asTreeNode().get());
			case VariantType::String: return ptrtodouble((void*)asString().c_str());
			case VariantType::Array: return asArray().size() > 0 ? asArray()[1].forceLegacyDouble() : 0.0;
			case VariantType::Pointer: return (double)(size_t)asPointer;
			default: return 0;
		}
	}
	engine_export static Variant interpretLegacyDouble(double val);
	engine_export static Variant interpretString(const char*);

	// only return my pointer if it's a non-owned cstr, i.e. it won't
	// go out of scope if I'm destructed.
	const char* getWeakStr() const { return (type == VariantType::String && (flags & WEAK_STR)) ? asString().c_str() : 0; }
	const char* c_str() const { return (type == VariantType::String) ? asString().c_str() : ""; }

private:
	std::string toStringInternal() const;
public:
	Variant getProperty(const char* propName, unsigned nameHash, bool dieHard);
	void setProperty(const char* propName, unsigned nameHash, const Variant& toVal);

	int __getType() { return (int)type; }
	engine_export const char* toString() const;

	Variant& append(const Variant& val)
	{
		if (val.type == VariantType::Null)
			throw "Appending a null variant to a variant is not allowed";
		switch (type) {
			default:
			case VariantType::Null: *this = val; break;
			case VariantType::Number:
			case VariantType::String:
			case VariantType::TreeNode:
				*this = operator Array();
				// continue into array case
			case VariantType::Array:
				if (val.type == VariantType::Array)
					asArray().append(val);
				else asArray().push(val);
				break;
		}
		return *this;
	}
	bool is(const char* className);
	protected:
	engine_export void checkArrayTypeForMethod(const char* funcName);
	public:
	engine_export Variant pop();
	engine_export Variant shift();
	engine_export Variant& push(const Variant& value);
	engine_export Variant& unshift(const Variant& value);
	engine_export Array concat(const Array& other) const;	
	Variant& splice(int begin, int removeCount) { if (type != VariantType::Array) *this = operator Array(); asArray().splice(begin, removeCount); checkApplyToBoundNode(); return *this; }
	Variant& splice(int begin, int removeCount, const Array& insert) { if (type != VariantType::Array) *this = operator Array(); asArray().splice(begin, removeCount, insert); checkApplyToBoundNode(); return *this; }
	Array slice(int begin, int end)
	{
		switch (type) {
			case VariantType::Array: return asArray().slice(begin, end);
				// case VariantType::String: return helper()->slice(from, to);
			default:
				return operator Array().slice(begin, end);
		}
	}


};

#pragma region number comparisons

#define COMPARE_NUMBER(numberType, op, oppositeOp)\
	inline bool operator op (numberType left, const Variant& right) {\
		return right oppositeOp left;\
	}\

#define COMPARE_NUMBER_TYPES(op, notOp)\
	FOR_ALL_NUMBER_TYPES_2(COMPARE_NUMBER, op, notOp)

	COMPARE_NUMBER_TYPES(<, >)
	COMPARE_NUMBER_TYPES(<=, >=)
	COMPARE_NUMBER_TYPES(>, <)
	COMPARE_NUMBER_TYPES(>=, <=)
	COMPARE_NUMBER_TYPES(==, ==)
	COMPARE_NUMBER_TYPES(!=, !=)


inline bool operator == (TreeNode* left, const Variant& right)
{
	return right == left;
}
inline bool operator != (TreeNode* left, const Variant& right)
{
	return right != left;
}
inline bool operator == (TreeNode* left, const NodeRef& right)
{
	return right == left;
}
inline bool operator != (TreeNode* left, const NodeRef& right)
{
	return right != left;
}

#undef COMPARE_NUMBER
#undef COMPARE_NUMBER_TYPES

#pragma endregion numberType compare Variant

#pragma region string comparisons
#define COMPARE_STRING(op, notOp, inType) \
	inline bool operator op (inType left, const Variant& right) { return !(right notOp left); }

#define COMPARE_STRING_PAIR(op, notOp) \
	COMPARE_STRING(op, notOp, const std::string&) \
	COMPARE_STRING(op, notOp, const char*)

	COMPARE_STRING_PAIR(<, >= )
	COMPARE_STRING_PAIR(<=, >)
	COMPARE_STRING_PAIR(>, <=)
	COMPARE_STRING_PAIR(>=, <)
	COMPARE_STRING_PAIR(==, !=)
	COMPARE_STRING_PAIR(!=, ==)

#undef COMPARE_STRING_PAIR
#undef COMPARE_STRING
#pragma endregion stringType compare Variant

#pragma region binary operators

	// For number types, return a Variant => cast left and right as doubles
	// This means double arithmetic will always be used with variants.
	// To do integer arithmetic, cast the Variant as an integer

#define BINARY_OP(numType, op)\
	inline double operator op (numType left, const Variant& right) {\
		return static_cast<double>(left) op static_cast<double>(right); \
	}
	FOR_ALL_NUMBER_TYPES(BINARY_OP, +)
	FOR_ALL_NUMBER_TYPES(BINARY_OP, -)
	FOR_ALL_NUMBER_TYPES(BINARY_OP, *)
	FOR_ALL_NUMBER_TYPES(BINARY_OP, /)

inline int operator % (int left, const Variant& right)
{
	return left % (int)right;
}

inline Variant operator + (const std::string& left, const Variant& right)
{
	return Variant(std::string(left).append(right));
}

inline Variant operator + (const char* left, const Variant& right)
{
	return Variant(std::string(left).append(right));
}

#undef BINARY_OP

#pragma endregion numberType op Variant, stringType op Variant


class VariantParams
{
	friend struct Compiler::ClassInfo;
public:
	engine_export const Variant& getParam(size_t paramNum) const;

	VariantParams() : numParams(0) {}
	VariantParams(const Variant& p1) : numParams(1) 
	             { params[0] = &p1; }
	VariantParams(const Variant& p1, const Variant& p2) : numParams(2)
	             { params[0] = &p1; params[1] = &p2; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3) : numParams(3)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4) : numParams(4)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5) : numParams(5)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6) : numParams(6)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7) : numParams(7)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7;}
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8) : numParams(8)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8;}
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9) : numParams(9)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10) : numParams(10)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11) : numParams(11)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12) : numParams(12)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12, const Variant& p13) : numParams(13)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; params[12] = &p13; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12, const Variant& p13, const Variant& p14) : numParams(14)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; params[12] = &p13; params[13] = &p14; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12, const Variant& p13, const Variant& p14, const Variant& p15) : numParams(15)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; params[12] = &p13; params[13] = &p14; params[14] = &p15; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12, const Variant& p13, const Variant& p14, const Variant& p15, const Variant& p16) : numParams(16)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; params[12] = &p13; params[13] = &p14; params[14] = &p15; params[15] = &p16; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12, const Variant& p13, const Variant& p14, const Variant& p15, const Variant& p16, const Variant& p17) : numParams(17)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; params[12] = &p13; params[13] = &p14; params[14] = &p15; params[15] = &p16; params[16] = &p17; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12, const Variant& p13, const Variant& p14, const Variant& p15, const Variant& p16, const Variant& p17, const Variant& p18) : numParams(18)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; params[12] = &p13; params[13] = &p14; params[14] = &p15; params[15] = &p16; params[16] = &p17; params[17] = &p18; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12, const Variant& p13, const Variant& p14, const Variant& p15, const Variant& p16, const Variant& p17, const Variant& p18, const Variant& p19) : numParams(19)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; params[12] = &p13; params[13] = &p14; params[14] = &p15; params[15] = &p16; params[16] = &p17; params[17] = &p18; params[18] = &p19; }
	VariantParams(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10, const Variant& p11, const Variant& p12, const Variant& p13, const Variant& p14, const Variant& p15, const Variant& p16, const Variant& p17, const Variant& p18, const Variant& p19, const Variant& p20) : numParams(20)
	             { params[0] = &p1; params[1] = &p2; params[2] = &p3; params[3] = &p4; params[4] = &p5; params[5] = &p6; params[6] = &p7; params[7] = &p8; params[8] = &p9; params[9] = &p10; params[10] = &p11; params[11] = &p12; params[12] = &p13; params[13] = &p14; params[14] = &p15; params[15] = &p16; params[16] = &p17; params[17] = &p18; params[18] = &p19; params[19] = &p20; }

	VariantParams(const CallPoint& cp);
	VariantParams(const std::vector<Variant>& v);

	size_t getNumParams() const { return numParams; }

private:
	size_t numParams;
	const Variant* params[20];

	void construct(const Variant& p1) { new (this) VariantParams(p1); }
	void construct(const Variant& p1, const Variant& p2) { new (this) VariantParams(p1, p2); }
	void construct(const Variant& p1, const Variant& p2, const Variant& p3) { new (this) VariantParams(p1, p2, p3); }
	void construct(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4) { new (this) VariantParams(p1, p2, p3, p4); }
	void construct(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5) 
		{ new (this) VariantParams(p1, p2, p3, p4, p5); }
	void construct(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5,
			const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10)
		{ new (this) VariantParams(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	void construct(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5,
			const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10,
			const Variant& p11, const Variant& p12, const Variant& p13, const Variant& p14, const Variant& p15,
			const Variant& p16, const Variant& p17, const Variant& p18, const Variant& p19, const Variant& p20)
		{ new (this) VariantParams(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20); }

};


template<class ArrayType, VariantType TypeId>
Variant FlexSimArray<ArrayType, TypeId>::__getElementAsProperty(const char* name, unsigned index) const
{
	return operator[](index);
}
template<class ArrayType, VariantType TypeId>
void FlexSimArray<ArrayType, TypeId>::__setElementAsProperty(const char* name, unsigned index, const Variant& val)
{
	operator[](index) = (ElementType)val;
}


inline Variant FlexSimPrivateTypes::DoubleStub::__getAsProperty(const char* name, unsigned index) const { return *((double*)this); }
inline void FlexSimPrivateTypes::DoubleStub::__setAsProperty(const char* name, unsigned index, const Variant& val) { *((double*)this) = val; }
inline Variant FlexSimPrivateTypes::String::__getAsProperty(const char* name, unsigned index) const { return *this; }
inline void FlexSimPrivateTypes::String::__setAsProperty(const char* name, unsigned index, const Variant& val) { *this = (String)val; }
inline Variant NodeRef::__getAsProperty(const char* name, unsigned index) const { return *this; }
inline void NodeRef::__setAsProperty(const char* name, unsigned index, const Variant& val) { *this = val; }

template<class PropertyType, class Enable = void>
struct TypedPropertyBinding : public PropertyBinding
{
	template<class GetterType, class SetterType>
	TypedPropertyBinding(const char* typeName, GetterType getter, SetterType setter, unsigned int version = 0) : PropertyBinding(getter, setter) { this->typeName = typeName; this->version = version; }
	virtual Variant get(void* owner) const override
	{
		typedef PropertyType(UnknownClass::*TypedGetter)();
		TypedGetter typedGetter = force_cast<TypedGetter>(getter);
		return (((UnknownClass*)owner)->*typedGetter)();
	}
	virtual void set(void* owner, const Variant& val) const override
	{
		typedef void*(UnknownClass::*TypedSetter)(PropertyType);
		TypedSetter typedSetter = force_cast<TypedSetter>(setter);
		(((UnknownClass*)owner)->*typedSetter)(val);
	}
};

template<class PropertyType>
struct TypedPropertyBinding<PropertyType, typename std::enable_if<
	std::is_compound<PropertyType>::value
	&& !std::is_pointer<PropertyType>::value
	&& (!std::is_convertible<PropertyType, Variant>::value
		|| !std::is_convertible<Variant, PropertyType>::value), void>::type> : public PropertyBinding
{
	template<class GetterType, class SetterType>
	TypedPropertyBinding(const char* typeName, GetterType getter, SetterType setter) : PropertyBinding(getter, setter) { this->typeName = typeName; }
};

template<class PropertyType>
struct TypedPropertyBinding<PropertyType, typename std::enable_if<
	std::is_compound<PropertyType>::value
	&& !std::is_pointer<PropertyType>::value
	&& !std::is_reference<PropertyType>::value
	&& ((std::is_convertible<PropertyType, Variant>::value
			&& std::is_convertible<Variant, PropertyType>::value)
		|| std::is_same<PropertyType, Variant>::value), void>::type> : public PropertyBinding
{
	template<class GetterType, class SetterType>
	TypedPropertyBinding(const char* typeName, GetterType getter, SetterType setter) : PropertyBinding(getter, setter) { this->typeName = typeName; }
	virtual Variant get(void* owner) const override
	{
		typedef PropertyType(UnknownClass::*TypedGetter)();
		TypedGetter typedGetter = force_cast<TypedGetter>(getter);
		return (((UnknownClass*)owner)->*typedGetter)();
	}
	virtual void set(void* owner, const Variant& val) const override
	{
		typedef void*(UnknownClass::*TypedSetter)(const PropertyType&);
		TypedSetter typedSetter = force_cast<TypedSetter>(setter);
		(((UnknownClass*)owner)->*typedSetter)(val);
	}
};

template<class PropertyType, class Enable = void>
struct StaticTypedPropertyBinding : public PropertyBinding
{
	template<class GetterType>
	StaticTypedPropertyBinding(const char* typeName, GetterType getter) : PropertyBinding(getter, nullptr) { this->typeName = typeName; }
	virtual bool isStatic() override { return true; }
	virtual Variant get(void* owner) const override
	{
		typedef PropertyType(*TypedGetter)();
		TypedGetter typedGetter = force_cast<TypedGetter>(getter);
		return typedGetter();
	}
};

template<class PropertyType>
struct StaticTypedPropertyBinding<PropertyType, typename std::enable_if<
	std::is_compound<PropertyType>::value
	&& !std::is_pointer<PropertyType>::value
	&& (!std::is_convertible<PropertyType, Variant>::value
	|| !std::is_convertible<Variant, PropertyType>::value), void>::type> : public PropertyBinding
{
	template<class GetterType>
	StaticTypedPropertyBinding(const char* typeName, GetterType getter) : PropertyBinding(getter, nullptr) { this->typeName = typeName; }
	virtual bool isStatic() override { return true; }
};

#ifdef FLEXSIM_ENGINE_COMPILE
#undef flexsimmalloc
#undef flexsimfree
#endif

class CharStrHash
{
public:
	size_t operator ()(const char* str)
	{
		size_t key = 0;
		for (int i = 0; *str; i++)
			key += *(str++) * i;
		return key;
	}
};

class CharStrEquals
{
public:
	bool operator() (const char* a, const char* b) { return strcmp(a, b) == 0; }
};

/// <summary> The NodeListArray class is 
/// meant to allow you, in c++, to treat a list of nodes with coupling data just
/// like a regular 0-based c++ array. So, instead of every time you have to do 
/// something like NetworkNode* nn = &o(NetworkNode, ownerobject(tonode(get(rank(node_v_myNetNodes, i)))));
/// you can just add the correct NodeListArray to your class, and do myNetNodes[i],
/// and bam, it handles all the rest.</summary>
/// 
/// <remarks> There are different ways that a list of coupling nodes may be set up, so
/// there are also several different types I've defined to represent these different
/// types of node list arrays. For example, you may have a list of just one-way 
/// pointers directly to the objects themselves. Or you may have a list of coupling nodes
/// where the other side of the coupling is created in the "stored" attribute
/// of the associated object, and so on. 
/// 
/// So, below are the basic defined ones that you can use out of the box. See the documentation of 
/// each one for more information
/// NodeListArray<YourClass>::ObjPtrType
/// NodeListArray<YourClass>::CouplingSdtPtrType
/// NodeListArray<YourClass>::ObjStoredAttCouplingType
/// NodeListArray<YourClass, YourAdder>::ObjCouplingType
/// NodeListArray<YourClass>::SdtSubNodeType
/// NodeListArray<YourClass>::SdtSubNodeBindingType
/// NodeListArray<YourClass>::CouplingSdtSubNodeType
/// NodeListArray<YourClass>::CouplingSdtSubNodeBindingType
/// NodeListArray<>::NodePtrType
/// NodeListArray<>::StoredAttCouplingType
/// NodeListArray<>::SubNodeCouplingType
/// NodeListArray<YourClass>::SdtSubNodeCouplingType
/// 
/// 
/// Also, usually you are going to initialize a NodeListArray in your bind()
/// or bindVariables() method, depending on if you're an odt or an sdt. </remarks>

static const int ZeroBasedRankOffset = 1;
static const int OneBasedRankOffset = 0;
template<class T = TreeNode, void(*Adder)(treenode x, T* obj) = nullptr, T* (*Getter)(treenode x) = nullptr, int rankOffset = 1>
class NodeListArray
{
	TreeNode* parent;
public:
	typedef T ElementType;

	NodeListArray() : parent(0) {}
	NodeListArray(treenode parent) : parent(parent) {}
	template <class OtherType>
	NodeListArray(treenode parent, const OtherType& copyFrom) : parent(parent)
	{
		*this = copyFrom;
	}
	template <class OtherType>
	NodeListArray(OtherType& copyFrom) : parent(copyFrom) {}
	void init(treenode parent) { this->parent = parent; }

	operator TreeNode*&() { return parent; }

	template <class OtherType>
	NodeListArray& operator = (const OtherType& copyFrom)
	{
		_ASSERTE(parent != 0)
			clear();
		for (int i = 1; i <= copyFrom.size(); i++)
			add(copyFrom[i - OtherType::rankOffset]);
		return *this;
	}

	int size() const { return content(parent); }
	int __getLength() { return size(); }
	__declspec(property(get = __getLength)) int length;

	T* operator[](int index) const
	{
		_ASSERTE(index >= 1 - rankOffset && index <= size() - rankOffset);
		treenode subNode = rank(parent, index + rankOffset);
		return Getter(subNode);
	}
	T* operator[](const char* name) const
	{
		treenode x = node(name, parent);
		if (objectexists(x))
			return operator[](getrank(x) - rankOffset);
		return NULL;
	}
	T* add(T* obj)
	{
		_ASSERTE(obj != 0);
		treenode tmp = nodeadddata(nodeinsertinto(parent), DATA_POINTERCOUPLING);
		Adder(tmp, obj);
		return obj;
	}

	T* add(T* obj, int atIndex)
	{
		_ASSERTE(obj != 0 && atIndex < size() - rankOffset);
		treenode tmp;
		if (atIndex > 0)
			tmp = nodeinsertafter(rank(parent, atIndex));
		else tmp = setrank(nodeinsertinto(parent), 1);
		nodeadddata(tmp, DATA_POINTERCOUPLING);
		Adder(tmp, obj);
		return obj;
	}

	void remove(int index)
	{
		_ASSERTE(index >= 1 - rankOffset && index <= size() - rankOffset);
		destroynode(rank(parent, index + rankOffset));
	}
	void clear() { clearcontents(parent); }
	void swap(int index1, int index2) { swapnoderanks(parent, index2 + rankOffset, index1 + rankOffset); }
	void setRank(int fromIndex, int toIndex) { setrank(rank(parent, fromIndex + rankOffset), toIndex + rankOffset); }
	int find(T* x) const
	{
		int tmpSize = size();
		for (int i = 1; i <= tmpSize; i++)
			if (operator[](i - rankOffset) == x)
				return i - rankOffset;
		return -1;
	}
private:
	template<class T, class Enable = void>
	struct ToNode
	{
		static TreeNode* get() { return nullptr; }
	};
	template<class T>
	struct ToNode<T, typename std::enable_if<!std::is_same<T, TreeNode>::value>::type>
	{
		static TreeNode* get(T* x) { return x->holder; }
	};
	template<class T>
	struct ToNode<T, typename std::enable_if<std::is_same<T, TreeNode>::value>::type>
	{
		static TreeNode* get(T* x) { return x; }
	};
public:

	Array toArray()
	{
		Array values;
		int tmpSize = size();
		values.resize(tmpSize);
		for (int i = 1; i <= tmpSize; i++)
			values[i] = ToNode<T>::get(Getter(rank(parent, i)));

		return values;
	}


	operator Array() { return toArray(); }

	void push(T* obj) { add(obj); }
	void pop() {if (!content(parent)) throw "pop() called on empty container";  destroyobject(last(parent)); }

	void unshift(T* obj) { add(obj); setrank(last(parent), 1); }
	void shift() { if (!content(parent)) throw "shift() called on empty container"; destroyobject(first(parent)); }

	static TreeNode* NodePtrGetter(treenode x) { return tonode(get(x)); }
	static void NodePtrAdder(treenode x, TreeNode* obj) { nodepoint(x, obj); }

	static TreeNode* StoredAttCouplingGetter(treenode x)
	{
		treenode partner = x->dataascoupling ? x->dataascoupling->partner().get() : 0;
		if (partner)
			return ownerobject(partner);
		return 0;
	}
	static void StoredAttCouplingAdder(treenode x, TreeNode* obj) { nodejoin(x, nodeadddata(nodeinsertinto(assertattribute(obj, "stored", 0)), DATA_POINTERCOUPLING)); }

	static TreeNode* SubNodeCouplingGetter(treenode x)
	{
		treenode partner = x->dataType == DATA_POINTERCOUPLING ? x->objectAs(CouplingDataType)->partner().get() : 0;
		if (partner)
			return up(partner);
		return 0;
	}
	static void SubNodeCouplingAdder(treenode x, TreeNode* obj) { nodejoin(x, nodeadddata(nodeinsertinto(obj), DATA_POINTERCOUPLING)); }
	static T* SdtSubNodeCouplingGetter(treenode x)
	{
		treenode partner = x->dataType == DATA_POINTERCOUPLING ? x->objectAs(CouplingDataType)->partner().get() : 0;
		if (partner)
			return up(partner)->objectAs(T);
		return 0;
	}
	static void SdtSubNodeCouplingAdder(treenode x, T* obj)
	{
		_ASSERTE(obj->holder != 0);
		nodejoin(x, nodeadddata(nodeinsertinto(obj->holder), DATA_POINTERCOUPLING));
	}

	static T* SdtSubSubNodeCouplingGetter(treenode x)
	{
		treenode partner = x->dataType == DATA_POINTERCOUPLING ? x->objectAs(CouplingDataType)->partner().get() : 0;
		if (partner)
			return up(up(partner))->objectAs(T);
		return 0;
	}

	template <TreeNode* (*ContainerGetter)(T* obj)>
	static void CustomCouplingAdder(treenode x, T* obj)
	{
		_ASSERTE(obj->holder != 0);
		nodejoin(x, nodeadddata(nodeinsertinto(ContainerGetter(obj)), DATA_POINTERCOUPLING));
	}


	static TreeNode* SubNodeGetter(treenode x) { return x; }
	static void SubNodeAdder(treenode x, TreeNode* obj) {}
	static T* SdtSubNodeGetter(treenode x) { return &o(T, x); }
	static void SdtSubNodeAdder(treenode x, T* obj) { nodeaddsimpledata(x, obj, 0); }
	static void SdtSubNodeBindingAdder(treenode x, T* obj) { nodeaddsimpledata(x, obj, 1); }
	static void CouplingSdtSubNodeAdder(treenode x, T* obj) { nodeaddcouplingdata(x, obj, 0); }
	static void CouplingSdtSubNodeBindingAdder(treenode x, T* obj) { nodeaddcouplingdata(x, obj, 1); }
	static void ObjSubNodeAdder(treenode x, T* obj) { transfernode(obj->holder, up(x)); destroyobject(x); }

	static T* ObjPtrGetter(treenode x)
	{
		treenode partner = x->dataType == DATA_POINTERCOUPLING ? x->object<CouplingDataType>()->partner().get() : 0;
		if (partner)
			return &o(T, partner);
		return 0;
	}
	static void ObjPtrAdder(treenode x, T* obj)
	{
		_ASSERTE(obj->holder != 0);
		nodepoint(x, obj->holder);
	}
	static void CouplingSdtPtrAdder(treenode x, T* obj)
	{
		_ASSERTE(obj->holder != 0);
		nodejoin(x, obj->holder);
	}

	static T* ObjCouplingGetter(treenode x)
	{
		treenode partner = x->dataType == DATA_POINTERCOUPLING ? x->object<CouplingDataType>()->partner().get() : 0;
		if (partner)
			return &o(T, ownerobject(partner));
		return 0;
	}
	static void ObjCouplingAdder(treenode x, T* obj)
	{
		_ASSERTE(obj->holder != 0);
		nodejoin(x, nodeadddata(nodeinsertinto(assertattribute(obj->holder, "stored", 0)), DATA_POINTERCOUPLING));
	}
	static void PortAdder(treenode x, T* obj, treenode otherList)
	{
		nodeadddata(nodeinsertinto(x), DATA_FLOAT);
		nodeadddata(nodeinsertinto(x), DATA_POINTERCOUPLING);
		if (obj) {
			treenode other = nodeadddata(nodeinsertinto(otherList), DATA_POINTERCOUPLING);
			nodeadddata(nodeinsertinto(other), DATA_FLOAT);
			nodeadddata(nodeinsertinto(other), DATA_POINTERCOUPLING);
			nodejoin(x, other);
		}
	}
	static void InPortAdder(treenode x, T* obj)
	{
		_ASSERTE(obj == nullptr || obj->holder != 0);
		PortAdder(x, obj, obj ? connectionsin(obj->holder) : nullptr);
	}
	static void OutPortAdder(treenode x, T* obj)
	{
		_ASSERTE(obj == nullptr || obj->holder != 0);
		PortAdder(x, obj, obj ? connectionsout(obj->holder) : nullptr);
	}
	static void CenterPortAdder(treenode x, T* obj)
	{
		_ASSERTE(obj == nullptr || obj->holder != 0);
		PortAdder(x, obj, obj ? connectionscenter(obj->holder) : nullptr);
	}


	/*********************************************************************
	OK, Here are the list of classes that this header file sets up for you.
	**********************************************************************/

	/*********************************************************************
	NodeListArray<TheClass>::SubNodeType
	This one represents a simple list of sub-nodes
	**********************************************************************/
	typedef NodeListArray<TreeNode, SubNodeAdder, SubNodeGetter, rankOffset> SubNodeType;

	/*********************************************************************
	NodeListArray<TheClass>::ObjPtrType
	This one represents a list of direct one-way pointers to odt or sdt objects,
	For example, you may do:
	NodeListArray<NetworkNode>::ObjPtrType myNetNodes;
	Then dereferencing myNetNodes[arrayIndex] will get you back a NetworkNode*
	**********************************************************************/
	typedef NodeListArray<T, ObjPtrAdder, ObjPtrGetter, rankOffset> ObjPtrType;

	/*********************************************************************
	NodeListArray<TheClass>::CouplingSdtPtrType
	This one represents a list of two-way pointers to coupling sdt objects. It is like
	ObjPtrType in that each item in the list is a coupling node that points to an
	object, but it also assumes the other side of the reference is a coupling sdt, so
	when adding, it will join the nodes together with a two-way pointer instead of just
	a one-way pointer to the object. This is useful when you have coupling nodes where
	one side of the coupling is your custom coupling class (you would use the
	CouplingSdtSubNodeType for that side), and the other is just a vanilla coupling node
	bound to that class. On the vanilla side, you would use CouplingSdtPtrType. Note that when
	using this and adding connections to the list, you should add the
	CouplingSdtSubNodeType first, then add the CouplingSdtPtrType (the vanilla side)
	last to properly establish the connection.
	**********************************************************************/
	typedef NodeListArray<T, CouplingSdtPtrAdder, ObjPtrGetter, rankOffset> CouplingSdtPtrType;
	typedef NodeListArray<T, CouplingSdtPtrAdder, ObjPtrGetter, OneBasedRankOffset> CouplingSdtPtrTypeOneBased;

	/*********************************************************************
	NodeListArray<TheClass>::ObjStoredAttCouplingType
	This one represents a list of two-way couplings to odt objects. The other side of the
	coupling will be stored in the "stored" attribute of each object.
	NodeListArray<NetworkNode>::ObjStoredAttCouplingType myNetNodes;
	myNetNodes[arrayIndex] will then retrieve a NetworkNode*
	**********************************************************************/
	typedef NodeListArray<T, ObjCouplingAdder, ObjCouplingGetter, rankOffset> ObjStoredAttCouplingType;

	/*********************************************************************
	NodeListArray<TheClass, YourAdder>::ObjCouplingType
	This one represents a list of two-way couplings to odt objects. It's like
	ObjStoredAttCouplingType except the other side of the
	coupling is stored where you want it to be stored, so you have to add the adder yourself

	NodeListArray<NetworkNode, myAddToNetNodesVar>::ObjCouplingType myNetNodes;
	myNetNodes[arrayIndex] will then retrieve a NetworkNode*. Note you have to define
	the function myAddToNetNodesVar, which in this example should look like this:
	void myAddToNetNodesVar(treenode x, NetworkNode* y) {
	nodejoin(x, nodeadddata(nodeinsertinto(y->node_v_backpointer), DATATYPE_COUPLING);
	}

	Or for simplicity, you can instead just define the container for adding on the other side of the coupling by using the
	CustomCouplingAdder to do this:
	class MyType {
	static TreeNode* GetOtherContainer(OtherType* other) {return other->myTypeList;}
	NodeListArray<OtherType, NodeListArray<OtherType>::CustomCouplingAdder<GetOtherContainer>>::SdtSubSubNodeType otherTypeList;
	};
	**********************************************************************/
	typedef NodeListArray<T, Adder, ObjCouplingGetter, rankOffset> ObjCouplingType;

	/*********************************************************************
	NodeListArray<TheClass>::OutObjectType
	This one represents a list of objects connected to an object's output ports (zero-based)
	**********************************************************************/
	typedef NodeListArray<T, InPortAdder, ObjCouplingGetter, rankOffset> OutObjectType;
	typedef NodeListArray<T, InPortAdder, ObjCouplingGetter, OneBasedRankOffset> OutObjectTypeOneBased;

	/*********************************************************************
	NodeListArray<TheClass>::InObjectType
	This one represents a list of objects connected to an object's input ports (zero-based)
	**********************************************************************/
	typedef NodeListArray<T, OutPortAdder, ObjCouplingGetter, rankOffset> InObjectType;
	typedef NodeListArray<T, OutPortAdder, ObjCouplingGetter, OneBasedRankOffset> InObjectTypeOneBased;

	/*********************************************************************
	NodeListArray<TheClass>::CenterObjectType
	This one represents a list of objects connected to an object's input ports (zero-based)
	**********************************************************************/
	typedef NodeListArray<T, CenterPortAdder, ObjCouplingGetter, rankOffset> CenterObjectType;
	typedef NodeListArray<T, CenterPortAdder, ObjCouplingGetter, OneBasedRankOffset> CenterObjectTypeOneBased;

	/*********************************************************************
	NodeListArray<TheClass>::SdtSubNodeType
	This one represents a straight list of sdt's.

	NodeListArray<MySdt>::SdtSubNodeType mySdts;
	myNetNodes[arrayIndex] will then retrieve the MySdt* stored directly in the given sub-node.
	**********************************************************************/
	typedef NodeListArray<T, SdtSubNodeAdder, SdtSubNodeGetter, rankOffset> SdtSubNodeType;
	typedef NodeListArray<T, SdtSubNodeBindingAdder, SdtSubNodeGetter, rankOffset> SdtSubNodeBindingType;

	/*********************************************************************
	NodeListArray<TheClass>::CouplingSdtSubNodeType
	This one represents a straight list of coupling sdt's. It's just like SdtSubNodeType, except
	the adder will use nodeaddcouplingdata() instead of nodeaddsimpledata().

	NodeListArray<MySdt>::CouplingSdtSubNodeType mySdts;
	myNetNodes[arrayIndex] will then retrieve the MySdt* stored directly in the given sub-node.
	**********************************************************************/
	typedef NodeListArray<T, CouplingSdtSubNodeAdder, SdtSubNodeGetter, rankOffset> CouplingSdtSubNodeType;
	typedef NodeListArray<T, CouplingSdtSubNodeBindingAdder, SdtSubNodeGetter, rankOffset> CouplingSdtSubNodeBindingType;

	/*********************************************************************
	NodeListArray<TheClass>::ObjSubNodeType
	This one represents a straight list of odt's.

	NodeListArray<MyObj>::ObjSubNodeType myObjs;
	myObjs[arrayIndex] will then retrieve the MyObj* stored directly in the given sub-node.
	to add, you do myObjs.add(&o(MyObj, createinstance(theClass, model())));
	**********************************************************************/
	typedef NodeListArray<T, ObjSubNodeAdder, SdtSubNodeGetter, rankOffset> ObjSubNodeType;
	typedef NodeListArray<T, ObjSubNodeAdder, SdtSubNodeGetter, OneBasedRankOffset> ObjSubNodeTypeOneBased;

	/*********************************************************************
	NodeListArray::NodePtrType:
	This one represents a list of one-way pointers to nodes. This is just like the
	NodeListArray::ObjPtrType, except it returns a TreeNode*, i.e. the node itself instead of the odt/sdt.
	This can be used if you're pointing to nodes that don't necessarily have object data.
	NodeListArray::NodePtrType myNetNodes;
	myNetNodes[arrayIndex] will then get back a treenode that is the network node.
	**********************************************************************/
	typedef NodeListArray<TreeNode, NodePtrAdder, NodePtrGetter, rankOffset> NodePtrType;

	/*********************************************************************
	NodeListArray::StoredAttCouplingType:
	This one represents a list of two-way couplings to objects. This is just like the
	NodeListArray::ObjStoredAttCouplingType, except it returns a TreeNode*, i.e. the node itself instead of the odt/sdt.
	Like ObjListArray, the other side of the coupling will be stored in the "stored" attribute
	of the object.
	NodeListArray::StoredAttCouplingType myNetNodes;
	myNetNodes[arrayIndex] will then get back a treenode that is the network node.
	**********************************************************************/
	typedef NodeListArray<TreeNode, StoredAttCouplingAdder, StoredAttCouplingGetter, rankOffset> StoredAttCouplingType;
	typedef NodeListArray<TreeNode, StoredAttCouplingAdder, StoredAttCouplingGetter, OneBasedRankOffset> StoredAttCouplingTypeOneBased;

	/*********************************************************************
	NodeListArray::SubNodeCouplingType:
	This one represents a list of two-way couplings to nodes. This will store the other side of the
	coupling as a sub-node of the node referenced, and when dereferenced it will return the node that
	contains the coupling sub-node.
	**********************************************************************/
	typedef NodeListArray<TreeNode, SubNodeCouplingAdder, SubNodeCouplingGetter, rankOffset> SubNodeCouplingType;

	/*********************************************************************
	NodeListArray<MyObj>::SdtSubNodeCouplingType:
	This one represents a list of two-way couplings to objects. This will store the other side of the
	coupling as a sub-node of the object referenced, and when dereferenced it will return the object
	whose holder node contains the coupling sub-node. It's just like SubNodeCouplingType, except it returns
	an object reference instead of a node reference.
	**********************************************************************/
	typedef NodeListArray<T, SdtSubNodeCouplingAdder, SdtSubNodeCouplingGetter, rankOffset> SdtSubNodeCouplingType;

	/*********************************************************************
	NodeListArray<OtherType, OtherTypeAdder>::SdtSubSubNodeCouplingType:
	This one represents a list of two-way couplings to objects. This will store the other side of the
	coupling as a sub-sub-node of the object referenced, and when dereferenced it will return the object
	whose holder node contains the parent of the coupling sub-node. It's just like SdtSubNodeCouplingType,
	except it returns up(up(theCouplingPartner)) instead of just one up(). Also, in this case you must
	define the adder, or just the container for the other side of the coupling by using the
	CustomCouplingAdder to do this:
	class MyType {
	static TreeNode* GetOtherContainer(OtherType* other) {return other->myTypeList;}
	NodeListArray<OtherType, NodeListArray<OtherType>::CustomCouplingAdder<GetOtherContainer>>::SdtSubSubNodeType otherTypeList;
	};

	class OtherType {
	NodeListArray<MyType>::ObjCouplingType myTypeList;
	}
	**********************************************************************/
	typedef NodeListArray<T, Adder, SdtSubSubNodeCouplingGetter, rankOffset> SdtSubSubNodeCouplingType;

	class IteratorElement
	{
		NodeListArray* list;
		TreeNode::IteratorElement nodeElement;
		int curIndex;
	public:
		IteratorElement() : arrayAddress(0), curIndex(0), nodeElement() {}
		IteratorElement(NodeListArray* list, int curIndex) : list(list), curIndex(curIndex), nodeElement(list->parent, curIndex + 1) {}
		IteratorElement(IteratorElement& other) : list(other.list), curIndex(other.curIndex), nodeElement(other.nodeElement) {}
		T* operator ->() const { return Getter(nodeElement.element); }
		T* operator * () const { return Getter(nodeElement.element); }
		operator T*() const { return Getter(nodeElement.element); }
		IteratorElement& operator = (IteratorElement& other)
		{
			nodeElement = other.nodeElement;
			return *this;
		}
	};

	// Iterator for NodeListArray: for use with std iterator algorithms
	class Iterator : public std::iterator<std::random_access_iterator_tag, IteratorElement, ptrdiff_t, IteratorElement*, IteratorElement>
	{
		NodeListArray * list;
		ptrdiff_t curIndex;
	public:
		Iterator() : list(0), curIndex(-1) {}
		Iterator(NodeListArray* list, int curIndex) : list(list), curIndex(curIndex) {}
		Iterator(Iterator& other) : list(other.list), curIndex(other.curIndex) {}
		Iterator& operator = (Iterator& other) { list = other.list; curIndex = other.curIndex; return *this; }
		bool operator == (Iterator& other) { return list == other.list && curIndex == other.curIndex; }
		bool operator != (Iterator& other) { return !(operator == (other)); }
		//T* operator * () const {return list->operator[](curIndex);}
		//T* operator ->() {return list->operator[](curIndex);}
		IteratorElement operator * () { return IteratorElement(list, curIndex); }
		Iterator& operator ++() { curIndex++; return *this; }
		Iterator& operator ++(int x) { curIndex++; return *this; }
		Iterator& operator --() { curIndex--; return *this; }
		Iterator& operator --(int x) { curIndex--; return *this; }
		Iterator operator +(ptrdiff_t n) { return Iterator(list, curIndex + n); }
		Iterator operator -(ptrdiff_t n) { return Iterator(list, curIndex - n); }
		ptrdiff_t operator -(Iterator& other) { return curIndex - other.curIndex; }
		bool operator <(Iterator& other) { return curIndex < other.curIndex; }
		bool operator <=(Iterator& other) { return curIndex <= other.curIndex; }
		bool operator >(Iterator& other) { return curIndex > other.curIndex; }
		bool operator >=(Iterator& other) { return curIndex > other.curIndex; }
		Iterator& operator +=(ptrdiff_t n) { curIndex -= n; return *this; }
		Iterator& operator -=(ptrdiff_t n) { curIndex -= n; return *this; }
		T* operator [](ptrdiff_t n) { return list[curIndex + n]; }
	};
	// container iteration methods
	Iterator begin() { return Iterator(this, 0); }
	Iterator end() { return Iterator(this, size()); }
	Iterator rbegin() { return Iterator(this, size() - 1); }
	Iterator rend() { return Iterator(this, -1); }
	// vector-esque methods
	void push_back(T* obj) { add(obj); }
	void pop_back() { remove(size() - rankOffset); }
	Iterator insert(Iterator position, const T*& obj)
	{
		add(obj, position.curIndex);
		return position;
	}
	T* back() const
	{
		if (size() == 0)
			return 0;
		return Getter(last(parent));
	}
	T* front() const
	{
		if (size() == 0)
			return 0;
		return Getter(first(parent));
	}
};

class engine_export SubnodesArray
{
protected:
	TreeNode* holder = nullptr;
public:
	SubnodesArray(TreeNode* holder = nullptr) : holder(holder) {}
	SubnodesArray(const SubnodesArray& other) : holder(other.holder) {}
	void construct(const SubnodesArray& other) { ::new(this)SubnodesArray(other); }
	SubnodesArray& operator =(const SubnodesArray& other) { holder = other.holder; return *this; }

	int length();
	TreeNode* _assert(const char* name);
	TreeNode* _assert(const char* name, const Variant& val);
	void clear();
	TreeNode* operator[](int r);
	TreeNode* operator[](const char* name);
	TreeNode* operator[](const Variant& index);
};

class engine_export LabelsArray
{
private:
	static bool dieHard;
protected:
	TreeNode* holder = nullptr;
public:
	LabelsArray(TreeNode* holder = nullptr) : holder(holder) {}
	LabelsArray(const LabelsArray& other) : holder(other.holder) {}
	void construct(const LabelsArray& other) { ::new(this)LabelsArray(other); }
	LabelsArray& operator =(const LabelsArray& other) { holder = other.holder; return *this; }

	TreeNode* _assert(const char* name);
	TreeNode* _assert(const char* name, const Variant& val);

	TreeNode* operator[](const char* name);
};

struct portinfo
{
	TreeNode* object;
	int portnr;
	short portopen;
	short metaopen;
};

template <class Number>
class Vec4Generic
{
public:
	union {
		struct {
			Number x;
			Number y;
			Number z;
			Number w;
		};
		struct {
			Number r;
			Number g;
			Number b;
			Number a;
		};
		Number loc[4];
	};
	template <class OtherVec>
	Vec4Generic(const OtherVec& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
	template <class OtherNumber>
	Vec4Generic(const OtherNumber* other) : x(other[0]), y(other[1]), z(other[2]), w(other[3]) {}
	template <class OtherNumber>
	Vec4Generic(OtherNumber* other) : x(other[0]), y(other[1]), z(other[2]), w(other[3]) {}
	Vec4Generic(Number x, Number y, Number z, Number w) : x(x), y(y), z(z), w(w) {}
	Vec4Generic() {}
#if _MSC_VER >= 1800
	template <class OtherNumber>
	Vec4Generic(std::initializer_list<OtherNumber> list)
	{
		int index = 0;
		for (auto x = list.begin(); x != list.end() && index < 4; x++, index++)
			this->operator [] (index) = (Number)*x;
	}
	template <class OtherNumber>
	Vec4Generic& operator = (std::initializer_list<OtherNumber> list) { ::new (this) (list); return *this; }
#endif

	operator Number* () { return loc; }
	const Vec4Generic operator + (const Vec4Generic& a) const { return Vec4Generic(x + a.x, y + a.y, z + a.z, w + a.w); }
	const Vec4Generic operator - (const Vec4Generic& a) const { return Vec4Generic(x - a.x, y - a.y, z - a.z, w - a.w); }
	const Vec4Generic operator - () const { return Vec4Generic(-x, -y, -z, -w); }
	const Vec4Generic operator / (const Vec4Generic& other) const { return Vec4Generic(x / other.x, y / other.y, z / other.z, w / other.w); }
	const Vec4Generic operator / (Number mult) const { return Vec4Generic(x / mult, y / mult, z / mult, w / mult); }
	const Vec4Generic operator * (const Vec4Generic& other) const { return Vec4Generic(x * other.x, y * other.y, z * other.z, w * other.w); }
	const Vec4Generic operator * (Number mult) const { return Vec4Generic(x * mult, y * mult, z * mult, w * mult); }
	Vec4Generic& operator += (const Vec4Generic& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	Vec4Generic& operator -= (const Vec4Generic& other) { x -= other.x; y -= other.y; z -= other.z; w += other.w; return *this; }
	const bool operator == (const Vec4Generic& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
	const bool operator != (const Vec4Generic& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }

	template <class OtherNumber>
	Vec4Generic& operator = (const Vec4Generic<OtherNumber>& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
	Number& operator [] (int index) { return loc[index]; }
	Number const& operator [] (int index) const { return loc[index]; }

	Number getLength() const { return sqrt(x * x + y * y + z * z + w * w); }
	Number getDistanceTo(const Vec4Generic& other) const { return Vec3(x - other.x, y - other.y, z - other.z, w - other.w).getLength(); }
	Number getDotProduct(const Vec4Generic& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }
	Number getXYAngle() const { return radianstodegrees(atan2(y, x)); }
	Number getYZAngle() const { return radianstodegrees(atan2(z, y)); }
	Number getZXAngle() const { return radianstodegrees(atan2(x, z)); }
	template <class OtherNumber>
	void copyTo(OtherNumber* dest) const { dest[0] = (OtherNumber)x; dest[1] = (OtherNumber)y; dest[2] = (OtherNumber)z; dest[3] = (OtherNumber)w; }
	void normalize()
	{
		Number length = getLength();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}
#define VEC4_ROTATE_A_B(degs, a, b) \
		Number rads = degreestoradians(degrees); \
		Number cosRads = cos(rads); \
		Number sinRads = sin(rads); \
		Vec4Generic temp = *this; \
		a = cosRads * temp.a - sinRads * temp.b; \
		b = sinRads * temp.a + cosRads * temp.b;

	void rotateXY(Number degrees)
	{
		VEC4_ROTATE_A_B(degrees, x, y)
	}
	void rotateYZ(Number degrees)
	{
		VEC4_ROTATE_A_B(degrees, y, z)
	}
	void rotateZX(Number degrees)
	{
		VEC4_ROTATE_A_B(degrees, z, x)
	}
	static Vec4Generic fromRotAndDist(Number degs, Number length, Number zComp = 0)
	{
		Number rads = degreestoradians(degs);
		return Vec4Generic(length * cos(rads), length * sin(rads), zComp);
	}
};


template <class Number>
class Vec3Generic
{
public:
	union {
		struct {
			Number x;
			Number y;
			Number z;
		};
		struct {
			Number r;
			Number g;
			Number b;
		};
		Number loc[3];
	};
	template <class OtherVec>
	Vec3Generic(const OtherVec& other) : x(other.x), y(other.y), z(other.z) {}
	template <class OtherNumber>
	Vec3Generic(const OtherNumber* other) : x(other[0]), y(other[1]), z(other[2]) {}
	template <class OtherNumber>
	Vec3Generic(OtherNumber* other) : x(other[0]), y(other[1]), z(other[2]) {}
	Vec3Generic(Number x, Number y, Number z) : x(x), y(y), z(z) {}
	Vec3Generic() {}
#if _MSC_VER >= 1800
	template <class OtherNumber>
	Vec3Generic(std::initializer_list<OtherNumber> list)
	{
		int index = 0;
		for (auto x = list.begin(); x != list.end() && index < 3; x++, index++)
			this->operator [] (index) = (Number)*x;
	}
	template <class OtherNumber>
	Vec3Generic& operator = (std::initializer_list<OtherNumber> list) { ::new (this) (list); return *this; }
#endif

	operator Number* () { return loc; }
	Vec3Generic operator + (const Vec3Generic& a) const { return Vec3Generic(x + a.x, y + a.y, z + a.z); }
	Vec3Generic operator - (const Vec3Generic& a) const { return Vec3Generic(x - a.x, y - a.y, z - a.z); }
	Vec3Generic operator - () const { return Vec3Generic(-x, -y, -z); }
	Vec3Generic operator / (const Vec3Generic& other) const { 
		if (other.x == 0)
			throw "Divide by zero error: x component of denominator is 0";
		if (other.y == 0)
			throw "Divide by zero error: y component of denominator is 0";
		if (other.z == 0)
			throw "Divide by zero error: z component of denominator is 0";

		return Vec3Generic(x / other.x, y / other.y, z / other.z); 
	}
	Vec3Generic operator / (Number mult) const { 
		if (mult == 0)
			throw "Divide by zero error: denominator is 0";
		return Vec3Generic(x / mult, y / mult, z / mult); 
	}
	Vec3Generic operator * (const Vec3Generic& other) const { return Vec3Generic(x * other.x, y * other.y, z * other.z); }
	Vec3Generic operator * (Number mult) const { return Vec3Generic(x * mult, y * mult, z * mult); }
	Vec3Generic& operator += (const Vec3Generic& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vec3Generic& operator -= (const Vec3Generic& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	bool operator == (const Vec3Generic& other) const { return x == other.x && y == other.y && z == other.z; }
	bool operator != (const Vec3Generic& other) const { return x != other.x || y != other.y || z != other.z; }

	template <class OtherNumber>
	Vec3Generic& operator = (const Vec3Generic<OtherNumber>& other) { x = other.x; y = other.y; z = other.z; return *this; }
	Number& operator [] (int index) { return loc[index]; }
	Number const& operator [] (int index) const { return loc[index]; }

	Number getLength() const { return sqrt(x * x + y * y + z * z); }
	Number getDistanceTo(const Vec3Generic& other) const { return Vec3Generic(x - other.x, y - other.y, z - other.z).getLength(); }
	Number getDotProduct(const Vec3Generic& other) const { return x * other.x + y * other.y + z * other.z; }
	Number getXYAngle() const { return radianstodegrees(atan2(y, x)); }
	Number getYZAngle() const { return radianstodegrees(atan2(z, y)); }
	Number getZXAngle() const { return radianstodegrees(atan2(x, z)); }
	template <class OtherNumber>
	void copyTo(OtherNumber* dest) const { dest[0] = (OtherNumber)x; dest[1] = (OtherNumber)y; dest[2] = (OtherNumber)z; }
	void normalize()
	{
		Number length = getLength();
		x /= length;
		y /= length;
		z /= length;
	}

	Vec3Generic __normalized() const { Vec3Generic temp = *this; temp.normalize(); return temp; }
	Number __magnitude() const { return getLength(); }
	__declspec(property(get = __normalized)) Vec3Generic normalized;
	__declspec(property(get = __magnitude)) Number magnitude;

	Number dot(const Vec3Generic& other) const { return getDotProduct(other); }
	Vec3Generic cross(const Vec3Generic& other) {
		const Vec3Generic& u = *this;
		const Vec3Generic& v = other;
		Vec3Generic r;
		r.x = u.y * v.z - u.z * v.y;
		r.y = u.z * v.x - u.x * v.z;
		r.z = u.x * v.y - u.y * v.x;
		return r;
	}
	Number angle(const Vec3Generic& other) {
		Number thisMagnitude = magnitude;
		if (thisMagnitude == 0)
			throw "Error in u.angle(v) - magnitude of u is 0";

		Number otherMagnitude = other.magnitude;
		if (otherMagnitude == 0)
			throw "Error in u.angle(v) - magnitude of v is 0";

		Number cosTheta = dot(other) / thisMagnitude / otherMagnitude;
		Number theta = acos(cosTheta);
		Number degrees = radianstodegrees(theta);
		return degrees;
	}
	Vec3Generic lerp(const Vec3Generic& other, double t) {
		double omt = 1 - t;
		return Vec3Generic(
			(Number)(x * omt + other.x * t), 
			(Number)(y * omt + other.y * t), 
			(Number)(z * omt + other.z * t)
		);
	}
	Vec3Generic project(TreeNode* from, TreeNode* to) {
		if (!objectexists(from))
			throw "Error in v.project(from, to) - from does not exist";

		if (!objectexists(to))
			throw "Error in v.project(from, to) - to does not exist";

		double newVec[3] = { 0, 0, 0 };
		vectorproject(from, x, y, z, to, newVec);
		return Vec3Generic(newVec);
	}

#define VEC3_ROTATE_A_B(degs, a, b) \
		Number rads = degreestoradians(degrees); \
		Number cosRads = cos(rads); \
		Number sinRads = sin(rads); \
		Vec3Generic temp = *this; \
		a = cosRads * temp.a - sinRads * temp.b; \
		b = sinRads * temp.a + cosRads * temp.b;

	void rotateXY(Number degrees)
	{
		VEC3_ROTATE_A_B(degrees, x, y)
	}
	void rotateYZ(Number degrees)
	{
		VEC3_ROTATE_A_B(degrees, y, z)
	}
	void rotateZX(Number degrees)
	{
		VEC3_ROTATE_A_B(degrees, z, x)
	}
	static Vec3Generic fromRotAndDist(Number degs, Number length, Number zComp = 0)
	{
		Number rads = degreestoradians(degs);
		return Vec3Generic(length * cos(rads), length * sin(rads), zComp);
	}
};

template <class Number>
class Vec2Generic
{
public:
	union {
		struct {
			Number x;
			Number y;
		};
		Number loc[2];
	};
	template <class OtherVec>
	Vec2Generic(const OtherVec& other) : x(other.x), y(other.y) {}
	Vec2Generic(Number x, Number y) : x(x), y(y) {}
	template <class OtherNumber>
	Vec2Generic(const OtherNumber* other) : x(other[0]), y(other[1]) {}
	template <class OtherNumber>
	Vec2Generic(OtherNumber* other) : x(other[0]), y(other[1]) {}
	Vec2Generic() {}
#if _MSC_VER >= 1800
	template <class OtherNumber>
	Vec2Generic(std::initializer_list<OtherNumber> list)
	{
		int index = 0;
		for (auto x = list.begin(); x != list.end() && index < 2; x++, index++)
			this->operator [] (index) = (Number)*x;
	}
	template <class OtherNumber>
	Vec2Generic& operator = (std::initializer_list<OtherNumber> list) { ::new (this) (list); return *this; }
#endif

	operator Number* () { return loc; }
	Vec2Generic operator + (const Vec2Generic& a) const { return Vec2Generic(x + a.x, y + a.y); }
	Vec2Generic operator - (const Vec2Generic& a) const { return Vec2Generic(x - a.x, y - a.y); }
	Vec2Generic operator - () const { return Vec2Generic(-x, -y); }
	Vec2Generic operator / (const Vec2Generic& other) const { return Vec2Generic(x / other.x, y / other.y); }
	Vec2Generic operator / (Number mult) const { return Vec2Generic(x / mult, y / mult); }
	Vec2Generic operator * (const Vec2Generic& other) const { return Vec2Generic(x * other.x, y * other.y); }
	Vec2Generic operator * (Number mult) const { return Vec2Generic(x * mult, y * mult); }
	Vec2Generic& operator += (const Vec2Generic& other) { x += other.x; y += other.y; return *this; }
	Vec2Generic& operator -= (const Vec2Generic& other) { x -= other.x; y -= other.y; return *this; }
	bool operator == (const Vec2Generic& other) const { return x == other.x && y == other.y; }
	bool operator != (const Vec2Generic& other) const { return x != other.x || y != other.y; }

	template <class OtherNumber>
	Vec2Generic& operator = (const Vec2Generic<OtherNumber>& other) { x = other.x; y = other.y; return *this; }
	Number& operator [] (int index) { return loc[index]; }
	Number const& operator [] (int index) const { return loc[index]; }

	Number getLength() const { return sqrt(x * x + y * y); }
	Number getDistanceTo(const Vec2Generic& other) const { return Vec2Generic(x - other.x, y - other.y).getLength(); }
	Number getDotProduct(const Vec2Generic& other) const { return x * other.x + y * other.y; }
	Number getAngle() const { return radianstodegrees(atan2(y, x)); }
	Number getDeterminant(const Vec2Generic& other) const { return x * other.y - y * other.x; }
	template <class OtherNumber>
	void copyTo(OtherNumber* dest) const { dest[0] = (OtherNumber)x; dest[1] = (OtherNumber)y; }
	void normalize()
	{
		Number length = getLength();
		x /= length;
		y /= length;
	}
	void rotate(Number degrees)
	{
		Number rads = degreestoradians(degrees);
		Number cosRads = cos(rads);
		Number sinRads = sin(rads);
		Vec2Generic temp = *this;
		x = cosRads * temp.x - sinRads * temp.y;
		y = sinRads * temp.x + cosRads * temp.y;
	}
	static Vec2Generic fromRotAndDist(Number degs, Number length)
	{
		Number rads = degreestoradians(degs);
		return Vec2Generic(length * cos(rads), length * sin(rads));
	}

};

typedef Vec4Generic<double> Vec4;
typedef Vec4Generic<float> Vec4f;
typedef Vec3Generic<double> Vec3;
typedef Vec3Generic<float> Vec3f;
typedef Vec2Generic<double> Vec2;
typedef Vec2Generic<float> Vec2f;

class engine_export Color
{
public:
	double _r;
	double _g;
	double _b;
	double _a;

	static double bound(double val) { return fmin(1.0, fmax(0.0, val)); }

	double __getR() const { return _r; }
	double __getG() const { return _g; }
	double __getB() const { return _b; }
	double __getA() const { return _a; }

	void __setR(double val) { _r = bound(val); }
	void __setG(double val) { _g = bound(val); }
	void __setB(double val) { _b = bound(val); }
	void __setA(double val) { _a = bound(val); }	

	__declspec(property(get = __getR, put = __setR)) double r;
	__declspec(property(get = __getG, put = __setG)) double g;
	__declspec(property(get = __getB, put = __setB)) double b;
	__declspec(property(get = __getA, put = __setA)) double a;
	
	Color(const Color& o) : _r(bound(o.r)), _g(bound(o.g)), _b(bound(o.b)), _a(bound(o.a)) {}
	Color(double r2, double g2, double b2, double a2) { r = r2; g = g2; b = b2; a = a2; }
	Color() {}

	operator Array()
	{
		Array arr = Array(4);
		arr[1] = r;
		arr[2] = g;
		arr[3] = b;
		arr[4] = a;
		return arr;
	}

	Color operator + (const Color& o) const { return Color(r + o.r, g + o.g, b + o.b, a + o.a); }
	Color operator - (const Color& o) const { return Color(r - o.r, g - o.g, b - o.b, a - o.a); }
	Color operator / (double mult) const
	{
		if (mult == 0)
			throw "Divide by zero error: denominator is 0";
		return Color(r / mult, g / mult, b / mult, a / mult);
	}
	Color operator * (const Color& o) const { return Color(r * o.r, g * o.g, b * o.b, a * o.a); }
	Color operator * (double mult) const { return Color(r * mult, g * mult, b * mult, a * mult); }
	Color& operator += (const Color& o) { r += o.r; g += o.g; b += o.b; a += o.a; return *this; }
	Color& operator -= (const Color& o) { r -= o.r; g -= o.g; b -= o.b; a -= o.a; return *this; }
	bool operator == (const Color& o) const { return r == o.r && g == o.g && b == o.b && a == o.a; }
	bool operator != (const Color& o) const { return r != o.r || g != o.g || b != o.b || a != o.a; }
	Color& operator = (const Color& o) { r = o.r; g = o.g; b = o.b; a = o.a; return *this; }	
	operator double* () { return &_r; }
	
	Color lerp(const Color& o, double t)
	{
		double omt = 1 - t;
		return Color(r * omt + o.r * t, g * omt + o.g * t, b * omt + o.b * t, a * omt + o.a * t);
	}

	static Color byNumber(int val);

	static const Color aqua;
	static const Color blue;
	static const Color brown;
	static const Color gray;
	static const Color green;
	static const Color lightBlue;
	static const Color lime;
	static const Color orange;
	static const Color pink;
	static const Color purple;
	static const Color red;
	static const Color silver;
	static const Color teal;
	static const Color white;
	static const Color black;
	static const Color yellow;
	static Color __aqua()       { return aqua; }
	static Color __blue()		{ return blue; }
	static Color __brown()		{ return brown; }
	static Color __gray()		{ return gray; }
	static Color __green()		{ return green; }
	static Color __lightBlue()	{ return lightBlue; }
	static Color __lime()		{ return lime; }
	static Color __orange()		{ return orange; }
	static Color __pink()		{ return pink; }
	static Color __purple()		{ return purple; }
	static Color __red()		{ return red; }
	static Color __silver()		{ return silver; }
	static Color __teal()		{ return teal; }
	static Color __white()      { return white; }
	static Color __black()      { return black; }
	static Color __yellow()		{ return yellow; }

	static Color random(int stream = 0);
};

class Table
{
public:
	TreeNode* root;
	std::shared_ptr <Table> ref;

	struct TableElement
	{
		std::weak_ptr<Table> tableRef;
		int depth;
		int indexes[10];

		TableElement(std::shared_ptr <Table> table) : tableRef(table) {}

		void operator = (const Variant& val);
		bool operator == (const Variant& val) { return getValue() == val; }
		bool operator != (const Variant& val) { return getValue() != val; }
		TableElement operator [](const Variant& index);

		operator Variant()		{ return getValue(); }
		operator int()			{ return getValue(); }
		operator double()		{ return getValue(); }
		operator std::string()	{ return getValue(); }
		operator TreeNode*()	{ return getValue(); }
		Variant getValue();
	};

	Table(TreeNode* node) : root(node), ref(this) {}
	Table() {}

	Table& operator = (TreeNode* node) { root = node; return *this; }
	operator TreeNode*() { return root; }
	operator Variant() { return root; }
	TableElement operator [](const Variant& row);	

	int __numRows() const;
	int __numCols() const;
	__declspec(property(get = __numRows)) int numRows;
	__declspec(property(get = __numCols)) int numCols;

	std:: string __name() const;
	__declspec(property(get = __name)) std::string name;

	Table& addCol(int col, int datatype);
	Table& addRow(int row, int datatype);	
	TreeNode* cell(int row, int col);
	Table& clear();
	Table& deleteCol(int col);
	Table& deleteRow(int row);
	Variant executeCell(int row, int col);
	std::string getColHeader(int colNum);
	std::string getRowHeader(int rowNum);
	Table& Table::moveCol(int fromCol, int toCol);
	Table& Table::moveRow(int fromRow, int toRow);
	Table& setColHeader(int colNum, std::string name);
	Table& setRowHeader(int rowNum, std::string name);
	Table& setSize(int rows, int cols, int datatype, int overwrite);
	Table& sort(const Variant& cols, const Variant& ascDesc);
	Table& Table::swapCols(int col, int col2);
	Table& Table::swapRows(int row, int row2);	

	Variant getValue(int row, int col);
	void setValue(int row, int col, const Variant& val);	
	int indexFromVariant(int depth, const Variant& headerName);
	void checkBounds(int index, int rowOrCol);
};

}

#ifndef NO_AUTO_USE_FLEXSIM_NAMESPACE
using namespace FlexSim;
#endif