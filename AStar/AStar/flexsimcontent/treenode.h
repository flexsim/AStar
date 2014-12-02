#pragma once
// COPYRIGHT © 2015   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

#include "basicmacros.h"
#include "basicclasses.h"
#include "datatypes.h"

class TreeNode;

#if defined FLEXSIM_ENGINE_COMPILE || defined COMPILING_MODULE_DLL || defined COMPILING_FLEXSIM_CONTENT
#define FULL_TREENODE_DEF
#include "byteblock.h"
#endif

#ifdef FLEXSIM_ENGINE_COMPILE
	#define IN_TREENODE_H
	#include "treenodemacros.h"
#endif

#pragma pack(1)
class TreeNode
{
public:
	// Public interface
	// value
	engine_export Variant __getValue();
	engine_export TreeNode* __setValue(const Variant&);
	__declspec(property(get = __getValue, put = __setValue)) Variant value;

	// name
	engine_export FlexSimPrivateTypes::String __getName();
	engine_export TreeNode* __setName(const FlexSimPrivateTypes::String&);
	__declspec(property(get = __getName, put = __setName)) FlexSimPrivateTypes::String name;

	// dataType
	engine_export int __getDataType();
	engine_export TreeNode* __setDataType(int);
	__declspec(property(get = __getDataType, put = __setDataType)) int dataType;

	// evaluate
	engine_export Variant evaluate(VariantParams& params);
	engine_export Variant evaluate();
	engine_export Variant evaluate(const Variant& p1);
	engine_export Variant evaluate(const Variant& p1, const Variant& p2);
	engine_export Variant evaluate(const Variant& p1, const Variant& p2, const Variant& p3);
	engine_export Variant evaluate(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4);
	engine_export Variant evaluate(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5);
	engine_export Variant evaluate(const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6,
	                      const Variant& p7 = Variant(), const Variant& p8 = Variant(), const Variant& p9 = Variant(),
	                      const Variant& p10 = Variant());
	
	// object data
	template <class T>
	T* object() const { return (T*)data; }

	template <class T> friend class SafeRef;
private:
	engine_export void* __getData();
	engine_export unsigned short __getId();
#ifndef FULL_TREENODE_DEF
	// for normal dll accessors, you should get data with a getter method
	__declspec(property(get = __getData)) void* data;
	__declspec(property(get = __getId)) unsigned short id;

#else
private:
	unsigned int listsize;                        // (4 bytes)
	TreeNode ** array;                            // (4 or 8 bytes)
	TreeNode ** arraybase;                        // (4 or 8 bytes)

	//DATA MEMBERS ARE MANUALLY ALIGNED (NO PADDING)
engine_private:
	unsigned short id;                            // (2 bytes)
	BYTE datatype;                                // (1 byte)
	unsigned char flags;                          // (1 byte)
	unsigned int flags_ex;                        // (4 bytes)
private:
	ByteBlock m_name;                               // (10 or 14 bytes)
public:
	unsigned short parity;                        // (2 bytes)
	TreeNode * ownerobjectcache;                  // (4 or 8 bytes)
	double(*memberfunction) (FLEXSIMINTERFACE); // (4 or 8 bytes)
	HashTable<TreeNode*> * listhash;              // (4 or 8 bytes)
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
	double * safedatafloat();
	ByteBlock * safedatabyteblock();
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
	static unsigned short idcount;

	#ifdef FLEXSIM_ENGINE_COMPILE
		#include "treenodeinternal.h"
	#endif
};
#pragma pack()

struct portinfo
{
	TreeNode* object;
	int portnr;
	short portopen;
	short metaopen;
};

#ifdef FLEXSIM_ENGINE_COMPILE
	#undef IN_TREENODE_H
#endif



// COPYRIGHT © 2015   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.



