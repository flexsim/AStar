#pragma once
// COPYRIGHT 2015   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

#include "basicmacros.h"
#include "basicclasses.h"
#include "datatypes.h"
#include <unordered_map>

#if defined FLEXSIM_ENGINE_COMPILE || defined COMPILING_MODULE_DLL || defined COMPILING_FLEXSIM_CONTENT
#define FULL_TREENODE_DEF
#include "byteblock.h"
#endif

#ifdef FLEXSIM_ENGINE_COMPILE
	#include <stack>
	#include <map>
	#include <list>
	#define IN_TREENODE_H
	#include "treenodemacros.h"
	visible int validlink(FlexSim::TreeNode *, char *);
	#define VALIDLINKFAST(x) (x != nullptr && x!=&TreeNode::failSafeLink && testpointer(x,sizeof(TreeNode), nullptr) && x->checkParity())

	#include "Platform.h"
#endif

namespace FlexSim {

class engine_export SubnodesArray
{
protected:
	TreeNode* holder = nullptr;
public:
	SubnodesArray(TreeNode* holder = nullptr) : holder(holder) {}
	SubnodesArray(const SubnodesArray& other) : holder(other.holder) {}
	void construct(const SubnodesArray& other) { ::new(this)SubnodesArray(other); }
	SubnodesArray& operator =(const SubnodesArray& other) { holder = other.holder; return *this; }

	int __getLength();
	__declspec(property(get = __getLength)) int length;
	TreeNode* _assert(const char* name);
	TreeNode* _assert(const char* name, const Variant& val) { return _assert(name, val, false); }
	TreeNode* _assert(const char* name, const Variant& val, bool persist);
	void clear();
	TreeNode* operator[](int r);
	TreeNode* operator[](const char* name);
	TreeNode* operator[](const Variant& index);
	TreeNode* add();
	Array toArray();
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



class TreeNode
{
public:
	// Public interface
	// value
	engine_export Variant __getValue();
	engine_export TreeNode* __setValue(const Variant&);
	Variant __getValueSafe();
	TreeNode* __setValueSafe(const Variant&);
#ifdef FLEXSIM_ENGINE_COMPILE
	__declspec(property(get = __getValueSafe, put = __setValueSafe)) Variant value;
#else
	__declspec(property(get = __getValue, put = __setValue)) Variant value;
#endif

	// name
	engine_export FlexSimPrivateTypes::String __getName();
	engine_export void __setName(const FlexSimPrivateTypes::String&);
	__declspec(property(get = __getName, put = __setName)) FlexSimPrivateTypes::String name;

	// dataType
	engine_export int __getDataType();
	engine_export void __setDataType(int);
	__declspec(property(get = __getDataType, put = __setDataType)) int dataType;

	// rank
	engine_export int __getRank();
	engine_export void __setRank(int);
	__declspec(property(get = __getRank, put = __setRank)) int rank;

	// first
	engine_export TreeNode* __getFirst();
	engine_export void __setFirst(TreeNode*);
	__declspec(property(get = __getFirst, put = __setFirst)) TreeNode* first;

	// last
	engine_export TreeNode* __getLast();
	engine_export void __setLast(TreeNode*);
	__declspec(property(get = __getLast, put = __setLast)) TreeNode* last;

	// up
	engine_export TreeNode* __getUp();
	engine_export void __setUp(TreeNode*);
	__declspec(property(get = __getUp, put = __setUp)) TreeNode* up;

	// prev
	engine_export TreeNode* __getPrev();
	__declspec(property(get = __getPrev)) TreeNode* prev;

	// next
	engine_export TreeNode* __getNext();
	__declspec(property(get = __getNext)) TreeNode* next;

	SubnodesArray __getSubnodes() { return SubnodesArray(this); }
	__declspec(property(get = __getSubnodes)) SubnodesArray subnodes;

	LabelsArray __getLabels() { return LabelsArray(this); }
	__declspec(property(get = __getLabels)) LabelsArray labels;

	engine_export TreeNode* __getOwnerObject();
	__declspec(property(get = __getOwnerObject)) TreeNode* ownerObject;
	engine_export TreeNode* findOwnerObject();
	// evaluate
	engine_export Variant evaluate(const VariantParams& params);
	engine_export Variant evaluate();
	engine_export Variant evaluate(const Variant&);
	engine_export Variant evaluate(const Variant&, const Variant&);
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&);
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&);
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&);
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&);
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&);
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant& );
	engine_export Variant evaluate(const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&, const Variant&);


	/// <summary>	Destroys the node. </summary>
	/// <remarks>	If undos are enabled, this will add an undo record. </remarks>
	/// <param name="to">	[in,out] If non-null, to. </param>
	engine_export void destroy();

	/// <summary>	Joins this node with another node using a two-way coupling. </summary>
	/// <remarks>	If undos are enabled, this will add an undo record. </remarks>
	/// <param name="to">	[in,out] If non-null, to. </param>
	engine_export TreeNode* joinTo(TreeNode* to);

	/// <summary>	Points this node to another node using a one-way coupling. </summary>
	/// <remarks>	If undos are enabled, this will add an undo record. </remarks>
	/// <param name="to">	[in,out] If non-null, to. </param>
	engine_export TreeNode* pointTo(TreeNode* to);

	/// <summary>	Breaks off this node's pointer coupling data. </summary>
	/// <remarks>	If it is currently a two-way coupling, both sides of the coupling will be set to point to null.
	/// 			If undos are enabled, this will add an undo record. </remarks>
	/// <param name="to">	[in,out] If non-null, to. </param>
	engine_export TreeNode* breakItOff();

	/// <summary>	Sets the name of the node. </summary>
	/// <remarks>	If undos are enabled, this will add an undo record. </remarks>
	/// <param name="name">	The name. </param>
	engine_export TreeNode* setName(const char* name);

	/// <summary>	Adds data to the node. </summary>
	/// <remarks>	If undos are enabled, this will add an undo record. </remarks>
	/// <param name="type">	The data type. </param>
	/// <returns>	This node, allowing you to chain commands. </returns>
	engine_export TreeNode* addData(int type);

	engine_export TreeNode* find(const char* path);

	engine_export TreeNode* addSimpleData(SimpleDataType* simple, bool bind);
	engine_export TreeNode* addCouplingData(CouplingDataType* cdt, bool bind);

	// object data
	template <class T>
	T* object() const { return (T*)data; }
private:
	engine_export void* __getData();
#ifndef FULL_TREENODE_DEF
	// for normal dll accessors, you should get data with a getter method
	__declspec(property(get = __getData)) void* data;
#else
private:
	unsigned int listsize;                        // (4 bytes)
	TreeNode ** array;                            // (4 or 8 bytes)
	TreeNode ** arraybase;                        // (4 or 8 bytes)
	NodeRef * refsToMe;                      // (4 or 8 bytes)

	//DATA MEMBERS ARE MANUALLY ALIGNED (NO PADDING)
engine_private:
	unsigned short parity;                        // (2 bytes)
	unsigned short datatype;                      // (2 bytes)
protected:
	unsigned long long flags;                     // (8 bytes)
	ByteBlock m_name;                             // (12 or 16 bytes)
public:
	TreeNode * ownerobjectcache;                  // (4 or 8 bytes)
	void* dupedMember;                            // (4 or 8 bytes)
	std::unordered_map<std::string, TreeNode*> * listhash;              // (4 or 8 bytes)
	int arraysize;                                // (4 bytes)
	TreeNode * parent;                            // (4 or 8 bytes)
content_private:
	TreeNode * owner;                             // (4 or 8 bytes)
	TreeNode * branch;                            // (4 or 8 bytes) 

engine_private:
	union{                                        // (4 or 8 bytes) 
		void * data;
		double* dataasdouble;
		ObjectDataType* dataasobject;
		ByteBlock* dataasbyteblock;
		CouplingDataType* dataascoupling;
		Bundle* dataasbundle;
		SimpleDataType* dataassimple;
	};

public:
	TreeNode() { initialize(); }
	~TreeNode() { cleanup(); }
	engine_export void initialize();
	engine_export int cleanup();
	engine_export double * safedatafloat();
	engine_export ByteBlock * safedatabyteblock();
	engine_export TreeNode * safedatapartner();

	#ifdef COMPILING_FLEXSIM_CONTENT
		// do not use this method. It is for backwards compatibility
		void __addUnknownData(void* theData) { datatype = 0; data = theData; }
	#endif

	public:
		class IteratorElement
		{
		public:
			TreeNode* listHead;
			TreeNode* element;
			int curRank;
			IteratorElement(TreeNode* node, int curRank)
				: listHead(node->owner == node ? node : node->branch),
				curRank(curRank), element(listHead ? listHead->array[curRank] : 0)
			{}
			IteratorElement() : listHead(0), curRank(0), element(0) {}
			IteratorElement(IteratorElement& other) : listHead(other.listHead), curRank(other.curRank), element(other.element) {}
			TreeNode* operator ->() const { return element; }
			TreeNode* operator * () { return element; }
			TreeNode* operator * () const { return element; }
			operator TreeNode*() const { return element; }
			IteratorElement& swap(IteratorElement& other)
			{
				IteratorElement temp = other;
				other = *this;
				*this = temp;
				return *this;
			}
			IteratorElement& operator = (IteratorElement& other)
			{
				if (listHead == other.listHead && curRank) {
					element = other.element;
					listHead->array[curRank] = element;
					element->array = listHead->array + curRank;
				} else {
					listHead = other.listHead;
					curRank = other.curRank;
					element = other.element;
				}
				return *this;
			}
		};
#endif // end full treenode def
private:

	#ifdef FLEXSIM_ENGINE_COMPILE
		#include "treenodeinternal.h"
	#endif
};
#pragma pack()

}

#ifdef FLEXSIM_ENGINE_COMPILE
	#undef IN_TREENODE_H
#endif



// COPYRIGHT 2015   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.



