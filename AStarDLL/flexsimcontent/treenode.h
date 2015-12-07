#pragma once
// COPYRIGHT 2015   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

#include "basicmacros.h"
#include "basicclasses.h"
#include "datatypes.h"
class TreeNode;

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
	visible int validlink(TreeNode *, char *);
	#define VALIDLINKFAST(x) (x!=&TreeNode::failSafeLink && !IsBadReadPtr(x,sizeof(TreeNode)) && x->checkParity())
#endif

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
	engine_export double * safedatafloat();
	engine_export ByteBlock * safedatabyteblock();
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


#ifdef FLEXSIM_ENGINE_COMPILE
	#undef IN_TREENODE_H
#endif



// COPYRIGHT 2015   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.



