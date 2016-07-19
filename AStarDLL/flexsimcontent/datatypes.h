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
	IntArray = 4,
	DoubleArray = 5,
	TreeNodeArray = 6,
	StringArray = 7,
	Pointer = 8
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

#define COMPARE_STRING(op) \
	inline bool operator op (const std::string& other) const { return strcmp(other.c_str(), buffer) op 0; } \
	inline bool operator op (const char* other) const { return strcmp(other, buffer) op 0; }

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
			else throw 0;
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
		void pop_back()
		{
			if (vectorSize <= 0)
				throw 0;
			elements[vectorSize - 1].~T();
			vectorSize--;
		}
		T& back()
		{
			if (vectorSize <= 0)
				throw 0;
			return elements[vectorSize - 1];
		}
		const T& back() const
		{
			if (vectorSize <= 0)
				throw 0;
			return elements[vectorSize - 1];
		}
		T& front()
		{
			if (vectorSize <= 0)
				throw 0;
			return elements[0];
		}
		const T& front() const
		{
			if (vectorSize <= 0)
				throw 0;
			return elements[0];
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
	__declspec(dllexport) NodeRef& operator=(const Variant&);

	operator bool() const { return ref != 0; }
	bool operator !() const { return ref == 0; }
	bool operator ==(const TreeNode* other) const { return ref == other; }
	bool operator ==(const NodeRef& other) const { return ref == other.ref; }
	bool operator ==(TreeNode* other) const { return ref == other; }
	bool operator ==(NodeRef& other) const { return ref == other.ref; }
	bool operator !=(const TreeNode* other) const { return ref != other; }
	bool operator !=(const NodeRef& other) const { return ref != other.ref; }
	bool operator !=(TreeNode* other) const { return ref != other; }
	bool operator !=(NodeRef& other) const { return ref != other.ref; }
	operator TreeNode*() const { return ref; }
	TreeNode* get() const { return ref; }
	TreeNode* operator ->() const { return ref; }
	engine_export void bind(TreeNode* x);
	std::string toString() const;
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
	FlexSimArray(const ArrayType& other) : arrayType(TypeId) {
		::new (&theArray()) FlexSimPrivateTypes::SharedPtr<MyVecType>(other.theArray());
	}
	~FlexSimArray() {
		theArray().~MySharedPtrType();
	}
	void destruct() { this->~FlexSimArray(); } 
	void construct() { ::new(this)FlexSimArray(); } 
	template <typename T> Type& operator[](T n) { return theArray()->operator[]((size_t)n); }
	template <typename T> const Type& operator[] (T n) const { return theArray()->operator[](n); }
	ArrayType& operator=(const ArrayType& other) { theArray() = other.theArray(); return *this; }
	ArrayType& operator=(size_t n) { theArray()->resize(n + 1); return *this; }
	ArrayType& operator=(int n) { theArray()->resize(n + 1); return *this; }
	void resize(size_t n) { theArray()->resize(n + 1); }
	size_t size() const { return theArray()->size() < 1 ? 0 : theArray()->size() - 1; }
	void push(const Type& val)
	{
		theArray()->push_back(val);
		if (theArray()->size() == 1)
			theArray()->push_back(val);
	}
	void pop() { theArray()->pop_back(); }
	ArrayType& append(const ArrayType& val)
	{
		size_t startSize = size();
		size_t valSize = val.size();
		resize(startSize + val.size());
		for (int i = 1; i <= valSize; i++)
			operator[](i + startSize) = val[i];
		return *this;
	}

	static ArrayType clone(const ArrayType& original)
	{ 
		ArrayType copy(original.size());
		if (copy.size() > 0) {
			for (size_t i = 0; i <= copy.size(); i++)
				copy[i] = original[i];
		}
		return copy;
	}
	ArrayType clone()
	{
		return clone(*this);
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
	typename std::enable_if<std::is_same<Type, FlexSimPrivateTypes::String>::value && std::is_same<X, const char*>::value>::type
	push(X val)
	{
		push(FlexSimPrivateTypes::String(val));
	}

	template<class X>
	typename std::enable_if<std::is_same<Type, FlexSimPrivateTypes::String>::value && std::is_same<X, const std::string&>::value>::type
	push(X val)
	{
		push(FlexSimPrivateTypes::String(val));
	}
	template<class X>
	typename std::enable_if<std::is_same<Type, NodeRef>::value && std::is_same<X, TreeNode*>::value>::type
		push(X val)
	{
		push(NodeRef(val));
	}


	typedef FlexSimArray<int, VariantType::IntArray> IntArray;
	typedef FlexSimArray<double, VariantType::DoubleArray> DoubleArray;
	typedef FlexSimArray<NodeRef, VariantType::TreeNodeArray> TreeNodeArray;
	typedef FlexSimArray<FlexSimPrivateTypes::String, VariantType::StringArray> StringArray;
	typedef FlexSimArrayUnionMember<int, VariantType::IntArray> IntArrayUnionMember;
	typedef FlexSimArrayUnionMember<double, VariantType::IntArray> DoubleArrayUnionMember;
	typedef FlexSimArrayUnionMember<NodeRef, VariantType::TreeNodeArray> TreeNodeArrayUnionMember;
	typedef FlexSimArrayUnionMember<FlexSimPrivateTypes::String, VariantType::StringArray> StringArrayUnionMember;
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

class Variant : public FlexSimPrivateTypes::NewDelete
{
public:
	VariantType type;
	friend struct Compiler::ClassInfo;
private:
	// a weak str ptr is one that's not owned by me, so I shouldn't deallocate it
	static const unsigned char WEAK_STR = 0x1;
	unsigned char flags;
	short reserved;// reserved for future use
	union
	{
		// union x86/x64 bytes = 12/24
		FlexSimPrivateTypes::NodeRefUnionMember asTreeNodeUnionMember; // 12/24 bytes
		double asNumber; // 8 bytes
		void* asPointer; // 4/8 bytes
		FlexSimPrivateTypes::StringUnionMember asStringUnionMember; // 8/16 bytes 

		FlexSimArray<>::IntArrayUnionMember asIntArrayUnionMember; // 4/8 bytes
		FlexSimArray<>::DoubleArrayUnionMember asDoubleArrayUnionMember; // 4/8 bytes
		FlexSimArray<>::TreeNodeArrayUnionMember asTreeNodeArrayUnionMember; // 4/8 bytes
		FlexSimArray<>::StringArrayUnionMember asStringArrayUnionMember; // 4/8 bytes
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

			case VariantType::IntArray: ::new (&asIntArray()) intarray(copyFrom.asIntArray()); break;
			case VariantType::DoubleArray: ::new (&asDoubleArray()) doublearray(copyFrom.asDoubleArray()); break;
			case VariantType::TreeNodeArray: ::new (&asTreeNodeArray()) treenodearray(copyFrom.asTreeNodeArray()); break;
			case VariantType::StringArray: ::new (&asStringArray()) stringarray(copyFrom.asStringArray()); break;
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
			case VariantType::IntArray: 
				::new (&asIntArray()) intarray(std::move(from.asIntArray())); 
				from.asIntArray().~intarray(); 
				break;
			case VariantType::DoubleArray: 
				::new (&asDoubleArray()) doublearray(std::move(from.asDoubleArray()));  
				from.asDoubleArray().~doublearray(); 
				break;
			case VariantType::TreeNodeArray: 
				::new (&asTreeNodeArray()) treenodearray(std::move(from.asTreeNodeArray())); 
				from.asTreeNodeArray().~treenodearray(); 
				break;
			case VariantType::StringArray: 
				::new (&asStringArray()) stringarray(std::move(from.asStringArray()));  
				from.asStringArray().~stringarray(); 
				break;
			case VariantType::Pointer: asPointer = from.asPointer; break;
			default: asNumber = 0; break;
		}
		from.type = VariantType::Null;
		from.asNumber = 0;
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

#pragma endregion Contains both public and private constructors

public:

	~Variant()
	{
		cleanup();
	}
	
#pragma region assignment operators

#define DEFINE_ASSIGNMENT_OPERATOR(ValType) \
		Variant& operator = (ValType copyFrom) \
			{ \
				cleanup(); \
				::new (this) Variant(copyFrom); \
				return *this; \
			}\

	DEFINE_ASSIGNMENT_OPERATOR(Variant&&)
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
	DEFINE_ASSIGNMENT_OPERATOR(const intarray&)
	DEFINE_ASSIGNMENT_OPERATOR(const doublearray&)
	DEFINE_ASSIGNMENT_OPERATOR(const treenodearray&)
	DEFINE_ASSIGNMENT_OPERATOR(const stringarray&)
	DEFINE_ASSIGNMENT_OPERATOR(void*)

#pragma endregion Contains assignment operators for every VariantType and other Variants

#pragma region casting operators

#define DEFINE_NUMBER_CAST(NumberType) \
	operator NumberType() const \
		{ \
		switch (type) { \
			case VariantType::Number: return static_cast<NumberType>(asNumber); \
			case VariantType::DoubleArray: return static_cast<NumberType>(asDoubleArray().size() > 0 ? asDoubleArray()[1] : 0); \
			case VariantType::IntArray: return static_cast<NumberType>(asIntArray().size() > 0 ? asIntArray()[1] : 0); \
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
			case VariantType::TreeNodeArray: return (asTreeNodeArray().size() > 0 ? asTreeNodeArray()[1] : 0);;
			default: return 0;
		}
	}
	operator std::string() const
	{
		switch (type) {
			case VariantType::String: return std::string(asString().c_str(), asString().getLength());
			case VariantType::StringArray: 
				if (asStringArray().size() > 0) {
					auto& element = asStringArray()[1];
					return std::string(element.c_str(), element.getLength());
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
	operator intarray() const
	{
		switch (type) {
			case VariantType::IntArray: return intarray(asIntArray());
			case VariantType::Number: {
				intarray theArray(1);
				theArray[1] = static_cast<int>(asNumber);
				return theArray;
			}
			default: return intarray(0);
		}
	}
	operator doublearray() const
	{
		switch (type) {
			case VariantType::DoubleArray: return doublearray(asDoubleArray());
			case VariantType::Number: {
				doublearray theArray(1);
				theArray[1] = asNumber;
				return theArray;
			}
			default: return doublearray();
		}
	}
	operator treenodearray() const
	{
		switch (type) {
			case VariantType::TreeNodeArray: return treenodearray(asTreeNodeArray());
			case VariantType::TreeNode: {
				treenodearray theArray(1);
				theArray[1] = asTreeNode();
				return theArray;
			}
			default: return treenodearray(0);
		}
	}
	operator stringarray() const
	{
		switch (type) {
			case VariantType::StringArray: return stringarray(asStringArray());
			case VariantType::String: {
				stringarray theArray(1);
				theArray[1] = asString();
				return theArray;
			}
			default: return stringarray(0);
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
		case VariantType::StringArray: return (int)asStringArray().size();
		case VariantType::IntArray: return (int)asIntArray().size();
		case VariantType::DoubleArray: return (int)asDoubleArray().size();
		case VariantType::TreeNodeArray: return (int)asTreeNodeArray().size();
		case VariantType::Null: return 0;
		default: return 1;
		}
	}

	Variant operator [] (int index) const
	{
		switch (type) {
		case VariantType::StringArray: return asStringArray()[index];
		case VariantType::IntArray: return asIntArray()[index];
		case VariantType::DoubleArray: return asDoubleArray()[index];
		case VariantType::TreeNodeArray: return asTreeNodeArray()[index];
		default: return *this;
		}
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
		bool isNumType = isNumberType();
		bool isOtherNumType = other.isNumberType();
		if (isNumType != isOtherNumType)
			return false;
		if (isNumType)
			return operator double() < other.operator double();
		else if (type == VariantType::String) {
			if (other.type != VariantType::String)
				return false;
			return strcmp(asString().c_str(), other.asString().c_str()) < 0;
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
			return strcmp(asString().c_str(), other.asString().c_str()) > 0;
		}
		return false;
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
		//case VariantType::IntArray: return asIntArray().begin() == other.asIntArray().begin();
		//case VariantType::DoubleArray: return asDoubleArray().begin() == other.asDoubleArray().begin();
		//case VariantType::StringArray: return asStringArray().begin() == other.asStringArray().begin();
		//case VariantType::TreeNodeArray: return asTreeNodeArray().begin() == other.asTreeNodeArray().begin();
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

#define COMPARE_NUMBER_1(numberType, op) \
	bool operator op (numberType theNum) const \
	{\
		if (type == VariantType::Number) return asNumber op theNum; \
		return false; \
	}\

#define COMPARE_NUMBER_2(numberType, op) \
	bool operator op (numberType theNum) const \
	{\
		if (type == VariantType::Number) return asNumber op theNum; \
		if (type == VariantType::TreeNode && theNum == 0) return operator TreeNode*() op nullptr; \
		return false; \
	}\

#define COMPARE_NUMBER_TYPES_1(op)\
	FOR_ALL_NUMBER_TYPES(COMPARE_NUMBER_1, op)
#define COMPARE_NUMBER_TYPES_2(op)\
	FOR_ALL_NUMBER_TYPES(COMPARE_NUMBER_2, op)

		COMPARE_NUMBER_TYPES_1(<)
		COMPARE_NUMBER_TYPES_1(>)
		COMPARE_NUMBER_TYPES_1(<=)
		COMPARE_NUMBER_TYPES_1(>=)
		COMPARE_NUMBER_TYPES_2(==)
		COMPARE_NUMBER_TYPES_2(!=)

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
#undef UNARY_NUM_OP
#pragma endregion ++, --, pre and post

	double forceLegacyDouble() const
	{
		switch (type) {
			case VariantType::Number: return asNumber;
			case VariantType::TreeNode: return ptrtodouble(asTreeNode().get());
			case VariantType::String: return ptrtodouble((void*)asString().c_str());
			case VariantType::DoubleArray: return asDoubleArray().size() > 0 ? asDoubleArray()[1] : 0.0;
			case VariantType::TreeNodeArray: return asTreeNodeArray().size() > 0 ? ptrtodouble(asTreeNodeArray()[1]) : 0.0;
			case VariantType::IntArray: return asIntArray().size() > 0 ? asIntArray()[1] : 0.0;
			case VariantType::StringArray: return asStringArray().size() > 0 ? ptrtodouble((void*)asStringArray()[1].c_str()) : 0.0;
			case VariantType::Pointer: return (double)(size_t)asPointer;
			default: return 0;
		}
	}
	engine_export static Variant interpretLegacyDouble(double val);

	// only return my pointer if it's a non-owned cstr, i.e. it won't
	// go out of scope if I'm destructed.
	const char* getWeakStr() const { return (type == VariantType::String && (flags & WEAK_STR)) ? asString().c_str() : 0; }
	const char* c_str() const { return (type == VariantType::String) ? asString().c_str() : ""; }

private:
	std::string toStringInternal() const;
public:
	engine_export const char* toString() const;
};

#pragma region number comparisons

#define COMPARE_NUMBER(numberType, op, notOp)\
	inline bool operator op (numberType left, const Variant& right) {\
		return !(right notOp left);\
	}\

#define COMPARE_NUMBER_TYPES(op, notOp)\
	FOR_ALL_NUMBER_TYPES_2(COMPARE_NUMBER, op, notOp)

	COMPARE_NUMBER_TYPES(<, >=)
	COMPARE_NUMBER_TYPES(<=, >)
	COMPARE_NUMBER_TYPES(>, <=)
	COMPARE_NUMBER_TYPES(>=, <)
	COMPARE_NUMBER_TYPES(==, !=)
	COMPARE_NUMBER_TYPES(!=, ==)


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


class VariantLValue {
	enum {
		None,
		AsVariant,
		AsDouble,
		AsInt,
		AsString,
		AsTreeNode,
		AsNodeRef,
		AsFSString
	} type;
	union {
		Variant* asVariant;
		double* asDouble;
		int* asInt;
		std::string* asString;
		FlexSimPrivateTypes::String* asFSString;
		TreeNode** asTreeNode;
		NodeRef* asNodeRef;
	};
public:
	VariantLValue() : type(None), asVariant(nullptr) {}
	VariantLValue(VariantLValue& other) : type(other.type), asVariant(other.asVariant) {}
	VariantLValue(Variant& v) : type(AsVariant), asVariant(&v) {}
	VariantLValue(double& val) : type(AsDouble), asDouble(&val) {}
	VariantLValue(int& val) : type(AsInt), asInt(&val) {}
	VariantLValue(std::string& val) : type(AsString), asString(&val) {}
	VariantLValue(FlexSimPrivateTypes::String& val) : type(AsFSString), asFSString(&val) {}
	VariantLValue(TreeNode*& val) : type(AsTreeNode), asTreeNode(&val) {}
	VariantLValue(NodeRef& val) : type(AsNodeRef), asNodeRef(&val) {}

	operator ::FlexSim::Variant() const
	{
		switch (type) {
			case AsVariant: return *asVariant;
			case AsDouble: return *asDouble;
			case AsInt: return *asInt;
			case AsString: return *asString;
			case AsFSString: return *asFSString;
			case AsTreeNode: return *asTreeNode;
			case AsNodeRef: return (TreeNode*)*asNodeRef;
		}
		return ::FlexSim::Variant();
	}

	#define DEFINE_LVAL_NUMBER_CAST_OP(ToType) \
	operator ToType() const \
	{ \
		switch (type) { \
			case AsVariant: return (ToType)*asVariant; \
			case AsDouble: return (ToType)*asDouble; \
			case AsInt: return (ToType)*asInt; \
		} \
		return (ToType)0; \
	}

	DEFINE_LVAL_NUMBER_CAST_OP(double)
	DEFINE_LVAL_NUMBER_CAST_OP(int)
	DEFINE_LVAL_NUMBER_CAST_OP(size_t)
	DEFINE_LVAL_NUMBER_CAST_OP(short)

	operator std::string() const
	{
		switch (type) {
			case AsVariant: return (std::string)*asVariant;
			case AsString: return *asString;
			case AsFSString: return *asFSString;
		}
		return "";
	}
	operator TreeNode*() const
	{
		switch (type) {
			case AsTreeNode: return *asTreeNode;
			case AsNodeRef: return *asNodeRef;
		}
		return nullptr;
	}

	VariantLValue& operator = (double toVal)
	{
		switch (type) {
			case AsVariant: *asVariant = toVal; break;
			case AsDouble: *asDouble = (double)toVal; break;
			case AsInt: *asInt = (int)toVal; break;
		}
		return *this;
	}
	VariantLValue& operator = (int toVal)
	{
		switch (type) {
			case AsVariant: *asVariant = toVal; break;
			case AsDouble: *asDouble = (double)toVal; break;
			case AsInt: *asInt = (int)toVal; break;
		}
		return *this;
	}
	VariantLValue& operator = (std::string& toVal)
	{
		switch (type) {
			case AsVariant: *asVariant = toVal; break;
			case AsString: *asString = toVal; break;
			case AsFSString: *asFSString = toVal; break;
		}
		return *this;
	}
	VariantLValue& operator = (FlexSimPrivateTypes::String& toVal)
	{
		switch (type) {
			case AsVariant: *asVariant = toVal; break;
			case AsString: *asString = toVal; break;
			case AsFSString: *asFSString = toVal; break;
		}
		return *this;
	}
	VariantLValue& operator = (TreeNode* toVal)
	{
		switch (type) {
			case AsVariant: *asVariant = toVal; break;
			case AsTreeNode: *asTreeNode = toVal; break;
			case AsNodeRef: *asTreeNode = toVal; break;
		}
		return *this;
	}
	VariantLValue& operator = (NodeRef& toVal)
	{
		switch (type) {
			case AsVariant: *asVariant = toVal; break;
			case AsTreeNode: *asTreeNode = toVal; break;
			case AsNodeRef: *asTreeNode = toVal; break;
		}
		return *this;
	}

};

/*
inline Variant Variant::operator [](int index)
{
	switch (type) {
		case VariantType::StringArray: return asStringArray()[index];
		case VariantType::IntArray: return asIntArray()[index];
		case VariantType::DoubleArray: return asDoubleArray()[index];
		case VariantType::TreeNodeArray: return asTreeNodeArray()[index];
		default: return *this;
	}
}


Variant::Variant(const VariantLValue& other)
{
	::new (this) Variant(other.operator Variant());
}


#define DEFINE_LVAL_EQUAL_COMPARISONS_LEFT(PassedClass, ConvertToClass) \
inline bool operator == (PassedClass left, const VariantLValue& right) { return left == (ConvertToClass)right; } \
inline bool operator != (PassedClass left, const VariantLValue& right) { return left != (ConvertToClass)right; } 

#define DEFINE_LVAL_EQUAL_COMPARISONS_RIGHT(PassedClass, ConvertToClass) \
inline bool operator == (const VariantLValue& left, PassedClass right) { return (ConvertToClass)left == right; } \
inline bool operator != (const VariantLValue& left, PassedClass right) { return (ConvertToClass)left != right; } 


#define DEFINE_LVAL_EQUAL_COMPARISONS(PassedClass, ConvertToClass) \
DEFINE_LVAL_EQUAL_COMPARISONS_LEFT(PassedClass, ConvertToClass) \
DEFINE_LVAL_EQUAL_COMPARISONS_RIGHT(PassedClass, ConvertToClass) 

#define DEFINE_LVAL_COMPARISONS_LEFT(PassedClass, ConvertToClass) \
DEFINE_LVAL_EQUAL_COMPARISONS_LEFT(PassedClass, ConvertToClass) \
inline bool operator > (PassedClass left, const VariantLValue& right) { return left > (ConvertToClass)right; } \
inline bool operator >= (PassedClass left, const VariantLValue& right) { return left >= (ConvertToClass)right; } \
inline bool operator < (PassedClass left, const VariantLValue& right) { return left < (ConvertToClass)right; } \
inline bool operator <= (PassedClass left, const VariantLValue& right) { return left <= (ConvertToClass)right; } 

#define DEFINE_LVAL_COMPARISONS_RIGHT(PassedClass, ConvertToClass) \
DEFINE_LVAL_EQUAL_COMPARISONS_RIGHT(PassedClass, ConvertToClass) \
inline bool operator > (const VariantLValue& left, PassedClass right) { return (ConvertToClass)left > right; } \
inline bool operator >= (const VariantLValue& left, PassedClass right) { return (ConvertToClass)left >= right; } \
inline bool operator < (const VariantLValue& left, PassedClass right) { return (ConvertToClass)left < right; } \
inline bool operator <= (const VariantLValue& left, PassedClass right) { return (ConvertToClass)left <= right; } 

#define DEFINE_LVAL_COMPARISONS(PassedClass, ConvertToClass) \
DEFINE_LVAL_COMPARISONS_LEFT(PassedClass, ConvertToClass) \
DEFINE_LVAL_COMPARISONS_RIGHT(PassedClass, ConvertToClass) 

DEFINE_LVAL_COMPARISONS(const Variant&, Variant)
DEFINE_LVAL_COMPARISONS(double, double)
DEFINE_LVAL_COMPARISONS(int, int)
DEFINE_LVAL_EQUAL_COMPARISONS(std::string, std::string)
DEFINE_LVAL_EQUAL_COMPARISONS(TreeNode*, TreeNode*)
DEFINE_LVAL_EQUAL_COMPARISONS(const NodeRef&, TreeNode*)
DEFINE_LVAL_COMPARISONS_LEFT(const VariantLValue&, Variant)

*/

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
template<class T = TreeNode, void(*Adder)(treenode x, T* obj) = 0, T* (*Getter)(treenode x) = 0>
class NodeListArray
{
	TreeNode* parent;

public:
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
		for (int i = 0; i < copyFrom.size(); i++)
			add(copyFrom[i]);
		return *this;
	}

	int size() const { return content(parent); }

	T* operator[](int index) const
	{
		_ASSERTE(index >= 0 && index < size());
		treenode subNode = rank(parent, index + 1);
		return Getter(subNode);
	}
	T* operator[](const char* name) const
	{
		treenode x = node(name, parent);
		if (objectexists(x))
			return operator[](getrank(x) - 1);
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
		_ASSERTE(obj != 0 && atIndex <= size());
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
		_ASSERTE(index >= 0 && index < size());
		destroynode(rank(parent, index + 1));
	}
	void clear() { clearcontents(parent); }
	void swap(int index1, int index2) { swapnoderanks(parent, index2 + 1, index1 + 1); }
	void setRank(int fromIndex, int toIndex) { setrank(rank(parent, fromIndex + 1), toIndex + 1); }
	int find(T* x) const
	{
		int tmpSize = size();
		for (int i = 0; i < tmpSize; i++)
			if (operator[](i) == x)
				return i;
		return -1;
	}

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


	/*********************************************************************
	OK, Here are the list of classes that this header file sets up for you.
	**********************************************************************/

	/*********************************************************************
	NodeListArray<TheClass>::SubNodeType
	This one represents a simple list of sub-nodes
	**********************************************************************/
	typedef NodeListArray<TreeNode, SubNodeAdder, SubNodeGetter> SubNodeType;

	/*********************************************************************
	NodeListArray<TheClass>::ObjPtrType
	This one represents a list of direct one-way pointers to odt or sdt objects,
	For example, you may do:
	NodeListArray<NetworkNode>::ObjPtrType myNetNodes;
	Then dereferencing myNetNodes[arrayIndex] will get you back a NetworkNode*
	**********************************************************************/
	typedef NodeListArray<T, ObjPtrAdder, ObjPtrGetter> ObjPtrType;

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
	typedef NodeListArray<T, CouplingSdtPtrAdder, ObjPtrGetter> CouplingSdtPtrType;

	/*********************************************************************
	NodeListArray<TheClass>::ObjStoredAttCouplingType
	This one represents a list of two-way couplings to odt objects. The other side of the
	coupling will be stored in the "stored" attribute of each object.
	NodeListArray<NetworkNode>::ObjStoredAttCouplingType myNetNodes;
	myNetNodes[arrayIndex] will then retrieve a NetworkNode*
	**********************************************************************/
	typedef NodeListArray<T, ObjCouplingAdder, ObjCouplingGetter> ObjStoredAttCouplingType;

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
	typedef NodeListArray<T, Adder, ObjCouplingGetter> ObjCouplingType;

	/*********************************************************************
	NodeListArray<TheClass>::SdtSubNodeType
	This one represents a straight list of sdt's.

	NodeListArray<MySdt>::SdtSubNodeType mySdts;
	myNetNodes[arrayIndex] will then retrieve the MySdt* stored directly in the given sub-node.
	**********************************************************************/
	typedef NodeListArray<T, SdtSubNodeAdder, SdtSubNodeGetter> SdtSubNodeType;
	typedef NodeListArray<T, SdtSubNodeBindingAdder, SdtSubNodeGetter> SdtSubNodeBindingType;

	/*********************************************************************
	NodeListArray<TheClass>::CouplingSdtSubNodeType
	This one represents a straight list of coupling sdt's. It's just like SdtSubNodeType, except
	the adder will use nodeaddcouplingdata() instead of nodeaddsimpledata().

	NodeListArray<MySdt>::CouplingSdtSubNodeType mySdts;
	myNetNodes[arrayIndex] will then retrieve the MySdt* stored directly in the given sub-node.
	**********************************************************************/
	typedef NodeListArray<T, CouplingSdtSubNodeAdder, SdtSubNodeGetter> CouplingSdtSubNodeType;
	typedef NodeListArray<T, CouplingSdtSubNodeBindingAdder, SdtSubNodeGetter> CouplingSdtSubNodeBindingType;

	/*********************************************************************
	NodeListArray<TheClass>::ObjSubNodeType
	This one represents a straight list of odt's.

	NodeListArray<MyObj>::ObjSubNodeType myObjs;
	myObjs[arrayIndex] will then retrieve the MyObj* stored directly in the given sub-node.
	to add, you do myObjs.add(&o(MyObj, createinstance(theClass, model())));
	**********************************************************************/
	typedef NodeListArray<T, ObjSubNodeAdder, SdtSubNodeGetter> ObjSubNodeType;

	/*********************************************************************
	NodeListArray::NodePtrType:
	This one represents a list of one-way pointers to nodes. This is just like the
	NodeListArray::ObjPtrType, except it returns a TreeNode*, i.e. the node itself instead of the odt/sdt.
	This can be used if you're pointing to nodes that don't necessarily have object data.
	NodeListArray::NodePtrType myNetNodes;
	myNetNodes[arrayIndex] will then get back a treenode that is the network node.
	**********************************************************************/
	typedef NodeListArray<TreeNode, NodePtrAdder, NodePtrGetter> NodePtrType;

	/*********************************************************************
	NodeListArray::StoredAttCouplingType:
	This one represents a list of two-way couplings to objects. This is just like the
	NodeListArray::ObjStoredAttCouplingType, except it returns a TreeNode*, i.e. the node itself instead of the odt/sdt.
	Like ObjListArray, the other side of the coupling will be stored in the "stored" attribute
	of the object.
	NodeListArray::StoredAttCouplingType myNetNodes;
	myNetNodes[arrayIndex] will then get back a treenode that is the network node.
	**********************************************************************/
	typedef NodeListArray<TreeNode, StoredAttCouplingAdder, StoredAttCouplingGetter> StoredAttCouplingType;

	/*********************************************************************
	NodeListArray::SubNodeCouplingType:
	This one represents a list of two-way couplings to nodes. This will store the other side of the
	coupling as a sub-node of the node referenced, and when dereferenced it will return the node that
	contains the coupling sub-node.
	**********************************************************************/
	typedef NodeListArray<TreeNode, SubNodeCouplingAdder, SubNodeCouplingGetter> SubNodeCouplingType;

	/*********************************************************************
	NodeListArray<MyObj>::SdtSubNodeCouplingType:
	This one represents a list of two-way couplings to objects. This will store the other side of the
	coupling as a sub-node of the object referenced, and when dereferenced it will return the object
	whose holder node contains the coupling sub-node. It's just like SubNodeCouplingType, except it returns
	an object reference instead of a node reference.
	**********************************************************************/
	typedef NodeListArray<T, SdtSubNodeCouplingAdder, SdtSubNodeCouplingGetter> SdtSubNodeCouplingType;

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
	typedef NodeListArray<T, Adder, SdtSubSubNodeCouplingGetter> SdtSubSubNodeCouplingType;

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
	void pop_back() { remove(size() - 1); }
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

struct portinfo
{
	TreeNode* object;
	int portnr;
	short portopen;
	short metaopen;
};

}

#ifndef NO_AUTO_USE_FLEXSIM_NAMESPACE
using namespace FlexSim;
#endif