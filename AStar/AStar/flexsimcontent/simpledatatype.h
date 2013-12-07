#pragma once
#include "basicclasses.h"
#include "basicmacros.h"
#include "basicutils.h"

// if i'm compiling the engine then I don't yet have access
// to some of the commands I need, so include the right files
#ifdef FLEXSIM_ENGINE_COMPILE
	extern "C" __declspec(dllexport) char* bbgetbuffer(treenode x);
	extern "C" __declspec(dllexport) int bbsetsize(treenode x, int size);
	#include "commandlist.h"
	#include "modelling.h"
#endif


#define SDT_BIND_NONE 0
#define SDT_BIND_ON_LOAD 1
#define SDT_BIND_ON_SAVE 2
#define SDT_BIND_ON_CREATE 3
#define SDT_BIND_ON_DISPLAY 4
#define SDT_BIND_SET_VALUE 5
#define SDT_BIND_GET_VALUE 6

class SimpleDataType
{
	friend class TreeNode;
	friend class CouplingDataType;
private:

	static int bindMode;
	static char* displayStr;
	static size_t displayStrMaxSize;
	static char* displayStrCopyPoint;
	static bool displayVerbose;
	static int detachAfterBind;
	static FlexSimCVector<NodeRef> nodeList;
	static void attachSDTDerivative(TreeNode* x);
	static void bindSDTNode(TreeNode* x);
	static void detachSDTDerivative(TreeNode* x);
	static SimpleDataType* createSDTDerivativeFromName(char* name, TreeNode* holder);
	static TreeNode* s_getBindTree(TreeNode* x);
	static TreeNode* s_assertBindTree(TreeNode* x);
	static double curValue;
	static const char * curValueName;
#define SDT_VALUE_NUMBER 1
#define SDT_VALUE_STRING 2
	static int curValueType;
	TreeNode* assertBindTree();

protected:

public:
	static void appendToDisplayStr(const char* text);
	static bool isDisplayVerbose();
	static void bindNodeList(int doBindMode, bool detachReattach, int startIndex = 0);
	static void clearAttsFromNodeList();
	TreeNode* holder;
	SimpleDataType(){}
	virtual ~SimpleDataType(){}
	virtual const char* getClassFactory(){return 0;}
	virtual void bind(){}
	void bind(int bindMode);
	virtual char* toString(int verbose);
	char* defaultToString(int verbose);
	void* operator new (size_t size)
	{
		void* p = flexsimmalloc(size);
		if(!p) throw 0;
		return p;
	}
	void operator delete (void* p)
	{
		flexsimfree(p);
	}

	static int getBindMode();
	static double& getCurValue();
	static int& getCurValueType();
	static const char * getCurValueName();
	double getValue(const char* name);
	void setValue(const char* name, double value);
	TreeNode* bindByName(const char* name, int asSubNode, int dataType, int * added = 0);

	void bindDoubleByName(const char* name, double& val, int asSubNode);
#define bindDouble(name, asSubNode) bindDoubleByName(#name, name, asSubNode)
	void bindNodeRefByName(const char* name, NodeRef& val, int asSubNode);
#define bindNodeRef(name, asSubNode) bindNodeRefByName(#name, name, asSubNode)
template<class ObjType>
	void bindObjRefByName(const char* name, ObjRef<ObjType>& val, int asSubNode)
	{
		bindNodeRefByName(name, val, asSubNode);
	}
#define bindObjRef(name, asSubNode) bindObjRefByName(#name, name, asSubNode)

	/// <summary>	Binds a FlexSimValue. Use this method if the name you want to bind by is
	/// 			different than the name of the member itself. Otherwise just use
	/// 			bindFlexSimValue()</summary>
	/// <param name="name">	The name of the member. </param>
	/// <param name="val"> 	[in,out] The value. </param>
	void bindFlexSimValueByName(const char* name, double& val);
	/// <summary>	Binds a FlexSimValue. Similar to bindDouble() or
	///				bindNumber(), except this method will check if tonode(value)
	///				is a valid node reference, and if so, it will save a coupling pointer
	///				to the node instead of using number data, so the reference will
	/// 			properly be saved/loaded.
	/// 			Note: bindFlexSimValue is a macro that expands the parameter to a name/value 
	/// 			pair for calling bindFlexSimValueByName. </summary>
	/// <param name="name">	The name of the member to bind. </param>
	#define bindFlexSimValue(name) bindFlexSimValueByName(#name, name)

	template<class T>
	void bindNumberByName(char* name, T& val)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		case SDT_BIND_ON_DISPLAY: {
			char tempStr[1000];
			if(((double)(int)val) != ((double)val))
				sprintf(tempStr, "%s: %lf%s", name, (double)val, isDisplayVerbose() ? "\r\n" : ", ");
			else sprintf(tempStr, "%s: %d%s", name, (int)val, isDisplayVerbose() ? "\r\n" : ", ");
			appendToDisplayStr(tempStr);
			break;
		}
			// else continue into load/save
		case SDT_BIND_ON_SAVE:
		case SDT_BIND_ON_LOAD: {
			TreeNode* theNode = bindByName(name, 0, DATA_FLOAT, 0);
			if(bindMode == SDT_BIND_ON_SAVE)
				theNode->safedatafloat()[0] = (double)val;
			else val = (T)theNode->safedatafloat()[0];
			break;
		}

		case SDT_BIND_SET_VALUE:
			if (strcmp(name, getCurValueName()) == 0) {
				getCurValueType() = SDT_VALUE_NUMBER;
				val = (T)getCurValue();
			}
			break;
		case SDT_BIND_GET_VALUE:
			if (strcmp(name, getCurValueName()) == 0) {
				getCurValueType() = SDT_VALUE_NUMBER;
				getCurValue() = (double)val;
			}
			break;
		}
	}
	#define bindNumber(name) bindNumberByName(#name, name)

	template<class Str>
	void bindStringByName(char* name, Str& val)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		case SDT_BIND_ON_DISPLAY: {
			char tempStr[1000];
			sprintf(tempStr, "%s: %s%s", name, val.c_str(), isDisplayVerbose() ? "\r\n" : ", ");
			appendToDisplayStr(tempStr);
			break;
		}
		// else continue into load/save
		case SDT_BIND_ON_SAVE:
		case SDT_BIND_ON_LOAD: {
			TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
			if(bindMode == SDT_BIND_ON_SAVE)
				sets(theNode, (char*)val.c_str());
			else val = bbgetbuffer(theNode);
			break;
		}

		case SDT_BIND_SET_VALUE:
			if (strcmp(name, getCurValueName()) == 0) {
				getCurValueType() = SDT_VALUE_STRING;
				val = (char*)doubletoptr(getCurValue());
			}
			break;
		case SDT_BIND_GET_VALUE:
			if (strcmp(name, getCurValueName()) == 0) {
				getCurValueType() = SDT_VALUE_STRING;
				getCurValue() = ptrtodouble((void*)val.c_str());
			}
			break;
		}

	}
	#define bindString(name) bindStringByName(#name, name)

	void bindByteBlockByName(const char* name, ByteBlock& val, int asSubNode);
	#define bindByteBlock(name, asSubNode) bindByteBlockByName(#name, name, asSubNode)

	template<class Type, class SizeType>
	void bindLocalArrayByName(char* name, Type* val, SizeType nrElements)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		// else continue into load/save
		case SDT_BIND_ON_SAVE:
		case SDT_BIND_ON_LOAD: {
			TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
			if(bindMode == SDT_BIND_ON_SAVE) {
				bbsetsize(theNode, nrElements * sizeof(Type));
				memcpy(bbgetbuffer(theNode), val, nrElements * sizeof(Type));
			}
			else memcpy(val, bbgetbuffer(theNode), nrElements * sizeof(Type));
			break;
		}
		}

	}
	#define bindLocalArray(name, nrBytes) bindLocalArrayByName(#name, name, nrBytes)

	void bindLocalBufferByName(char* name, void* val, int nrBytes)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		// else continue into load/save
		case SDT_BIND_ON_SAVE:
		case SDT_BIND_ON_LOAD: {
			TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
			if(bindMode == SDT_BIND_ON_SAVE) {
				bbsetsize(theNode, nrBytes);
				memcpy(bbgetbuffer(theNode), val, nrBytes);
			}
			else memcpy(val, bbgetbuffer(theNode), nrBytes);
			break;
		}
		}

	}
	#define bindLocalBuffer(name, nrBytes) bindLocalBufferByName(#name, name, nrBytes)

	template<class Type, class SizeType>
	void bindHeapArrayByName(char* name, Type*& val, SizeType& nrElements)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		// else continue into load/save
		case SDT_BIND_ON_SAVE:
		case SDT_BIND_ON_LOAD: {
			TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
			if(bindMode == SDT_BIND_ON_SAVE) {
				set(assertsubnode(theNode, "nrElements"), nrElements);
				bbsetsize(theNode, nrElements * sizeof(Type));
				memcpy(bbgetbuffer(theNode), val, nrElements * sizeof(Type));
			}
			else {
				nrElements = get(node("/nrElements", theNode));
				val = new Type[nrElements];
				memcpy(val, bbgetbuffer(theNode), nrElements * sizeof(Type));
			}
			break;
		}
		}
	}
	#define bindHeapArray(name, nrElements) bindHeapArrayByName(#name, name, nrElements)

	void bindNodePtrByName(const char* name, TreeNode*& val);
	void bindSubNodeByName(const char* name, TreeNode*& val, int dataType = 1);
	void bindObjPtrByName(const char* name, SimpleDataType*& val);

#define bindSubNode(name, dataType) bindSubNodeByName(#name, name, dataType)
#define bindNodePtr(name) bindNodePtrByName(#name, name)
#define bindObjPtr(name) bindObjPtrByName(#name, (SimpleDataType*&)name)

	TreeNode* getBindTree();

	// now for some stl stuff
	
	// original Saver() definitions
	template <typename Type> class StlValueBinder {
	public:
		static treenode Saver(treenode x, Type* toVal)
		{
			toVal->bind(x);
			return x;
		}
		static Type Loader(treenode x)
		{
			Type myVal;
			myVal.bind(x);
			return myVal;
		}
		static void Displayer(Type* x)
		{
			x->bind(0);
		}
	};

	#define FORMAT_AND_DISPLAY(format, x) \
			char str[200];\
			sprintf(str, format, x);\
			appendToDisplayStr(str);

	template <> class StlValueBinder<double> {
	public:
		static treenode Saver(treenode x, double* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), *toVal);}
		static double Loader(treenode x)
			{return get(x);}
		static void Displayer(double* x)
			{FORMAT_AND_DISPLAY("%lf", *x);}
	};

	template <> class StlValueBinder<float> {
	public:
		static treenode Saver(treenode x, float* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static float Loader(treenode x)
			{return (float)get(x);}
		static void Displayer(float* x)
			{FORMAT_AND_DISPLAY("%f", *x);}
	};

	template <> class StlValueBinder<int> {
	public:
		static treenode Saver(treenode x, int* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static int Loader(treenode x)
			{return (int)get(x);}
		static void Displayer(int* x)
			{FORMAT_AND_DISPLAY("%d", *x);}
	};

	template <> class StlValueBinder<unsigned int> {
	public:
		static treenode Saver(treenode x, unsigned int* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static unsigned int Loader(treenode x)
			{return (unsigned int)get(x);}
		static void Displayer(unsigned int* x)
			{FORMAT_AND_DISPLAY("%u", *x);}
	};

	template <> class StlValueBinder<short> {
	public:
		static treenode Saver(treenode x, short* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static short Loader(treenode x)
			{return (short)get(x);}
		static void Displayer(short* x)
			{FORMAT_AND_DISPLAY("%d", (int)*x);}
	};

	template <> class StlValueBinder<unsigned short> {
	public:
		static treenode Saver(treenode x, unsigned short* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static unsigned short Loader(treenode x)
			{return (unsigned short)get(x);}
		static void Displayer(unsigned short* x)
			{FORMAT_AND_DISPLAY("%u", (unsigned int)*x);}
	};

	template <> class StlValueBinder<char> {
	public:
		static treenode Saver(treenode x, char* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static char Loader(treenode x)
			{return (char)get(x);}
		static void Displayer(char* x)
			{FORMAT_AND_DISPLAY("%d", (int)*x);}
	};

	template <> class StlValueBinder<unsigned char> {
	public:
		static treenode Saver(treenode x, unsigned char* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static unsigned char Loader(treenode x)
			{return (unsigned char)get(x);}
		static void Displayer(unsigned char* x)
			{FORMAT_AND_DISPLAY("%u", (unsigned int)*x);}
	};

	template <> class StlValueBinder<bool> {
	public:
		static treenode Saver(treenode x, bool* toVal)
			{return set(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static bool Loader(treenode x)
			{return (bool)get(x);}
		static void Displayer(bool* x)
			{FORMAT_AND_DISPLAY("%d", (int)*x);}
	};

	template <> class StlValueBinder<char*> {
	public:
		static treenode Saver(treenode x, char** toVal)
			{return sets(nodeadddata(x, DATA_BYTEBLOCK), *toVal);}
		static char* Loader(treenode x)
			{return bbgetbuffer(x);}
		static void Displayer(char** x)
			{appendToDisplayStr(*x);}
	};

	template <> class StlValueBinder<std::string> {
	public:
		static treenode Saver(treenode x, std::string* toVal)
			{return sets(nodeadddata(x, DATA_BYTEBLOCK), *toVal);}
		static std::string Loader(treenode x)
			{return bbgetbuffer(x);}
		static void Displayer(std::string* x)
			{appendToDisplayStr(x->c_str());}
	};

	template <> class StlValueBinder<treenode> {
	public:
		static treenode Saver(treenode x, treenode* toVal)
			{return nodepoint(nodeadddata(x, DATA_POINTERCOUPLING), *toVal);}
		static treenode Loader(treenode x)
			{return tonode(get(x));}
		static void Displayer(treenode* x)
		{
			std::string str;
			if (objectexists(*x))
				str = nodetomodelpath(*x, 2);
			else if(*x == 0)
				str = "NULL";
			else str = "[Invalid Ptr]";
			appendToDisplayStr(str.c_str());
		}
	};

	template <typename T> class StlValueBinder<T*> {
	public:
		static treenode Saver(treenode x, T** toVal)
			{return nodepoint(nodeadddata(x, DATA_POINTERCOUPLING), *toVal ? (*toVal)->holder : 0);}
		static T* Loader(treenode x)
		{
			treenode dereference = tonode(get(x)); 
			if (objectexists(dereference))
				return &o(T, dereference);
			return 0;
		}
		static void Displayer(T** x)
		{
			if(x && (*x))
				StlValueBinder<treenode>::Displayer(&((*x)->holder));
			else appendToDisplayStr("NULL");
		}
	};

	template <class SetType>
	static void StlSetInserter(SetType& theSet, typename SetType::value_type theVal)
	{
		theSet.insert(theVal);
	}

	template <class SetType>
	static void StlVectorInserter(SetType& theSet, typename SetType::value_type theVal)
	{
		theSet.push_back(theVal);
	}


	template <class SetType, class Binder, void (*Inserter) (typename SetType& theSet, typename SetType::value_type theVal)>
	void bindStlContainerByName(const char* prefix, SetType& theSet)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		case SDT_BIND_ON_SAVE: {
			SetType::iterator temp = theSet.begin();
			if (temp == theSet.end())
				return;
			treenode container = bindByName(prefix, 0, DATA_FLOAT);
			clearcontents(container);
			for (; temp != theSet.end(); temp++)
				Binder::Saver(nodeinsertinto(container), (SetType::value_type*)&(*(temp)));
			break;
		}
		case SDT_BIND_ON_LOAD: {
			treenode container = bindByName(prefix, 0, DATA_FLOAT);
			theSet.clear();
			for (int i = 1; i <= content(container); i++)
				Inserter(theSet, Binder::Loader(rank(container, i)));
			break;
		}
		case SDT_BIND_ON_DISPLAY: {
			SetType::iterator temp = theSet.begin();
			appendToDisplayStr(prefix);
			appendToDisplayStr(": ");
			for (SetType::iterator temp = theSet.begin(); temp != theSet.end(); temp++) {
				if(temp != theSet.begin())
					appendToDisplayStr(", ");
				Binder::Displayer((SetType::value_type*)&(*(temp)));
			}
			appendToDisplayStr("\r\n");
			break;
		}
		default:break;

		}
	}

	template <class SetType>
	void bindStlContainerByName(const char* prefix, SetType& theSet)
	{
		bindStlContainerByName<SetType, StlValueBinder<SetType::value_type>, StlVectorInserter<SetType>>(prefix, theSet);
	}
	#define bindStlContainer(x) bindStlContainerByName(#x, x)

	template <class SetType>
	void bindStlSetByName(const char* prefix, SetType& theMap)
	{
		bindStlContainerByName<SetType, StlValueBinder<SetType::value_type>, StlSetInserter<SetType>>
			(prefix, theMap);
	}
	#define bindStlSet(x) bindStlSetByName(#x, x)

	template <class MapType, class KeyBinder, class ValBinder>
	void bindStlMapByName(const char* prefix, MapType& theMap)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		case SDT_BIND_ON_SAVE: {
			MapType::iterator temp = theMap.begin();
			if (temp == theMap.end())
				return;
			treenode container = bindByName(prefix, 0, DATA_FLOAT);
			clearcontents(container);
			for (; temp != theMap.end(); temp++) {
				ValBinder::Saver(
					nodeinsertinto(
						KeyBinder::Saver(nodeinsertinto(container), (MapType::key_type*)&(temp->first))), 
						(&(temp->second)));
			}
			break;
		}
		case SDT_BIND_ON_LOAD: {
			treenode container = bindByName(prefix, 0, DATA_FLOAT);
			theMap.clear();
			for (int i = 1; i <= content(container); i++) {
				treenode x = rank(container, i);
				theMap[KeyBinder::Loader(x)] = ValBinder::Loader(last(x));
			}
			break;
		}
		case SDT_BIND_ON_DISPLAY: {
			appendToDisplayStr(prefix);
			appendToDisplayStr(": ");
			for (MapType::iterator temp = theMap.begin(); temp != theMap.end(); temp++) {
				if(temp != theMap.begin())
					appendToDisplayStr(", ");
				KeyBinder::Displayer((MapType::key_type*)&(temp->first));
				appendToDisplayStr(" => ");
				ValBinder::Displayer(&(temp->second));
			}
			appendToDisplayStr("\r\n");
			break;
		}
		default:break;

		}
	}


	template <class MapType>
	void bindStlMapByName(const char* prefix, MapType& theMap)
	{
		bindStlMapByName<MapType, StlValueBinder<MapType::key_type>, StlValueBinder<MapType::mapped_type>>
			(prefix, theMap);
	}
	#define bindStlMap(x) bindStlMapByName(#x, x)


	// utilities for stl container element bind methods
	template <class SDTType>
	static void bindObjPtrToNodeByName(char* name, SDTType* & ptr, treenode x)
	{
		switch (getBindMode()) {
		case SDT_BIND_ON_SAVE:nodepoint(assertsubnode(x, name, DATA_POINTERCOUPLING), ptr ? ptr->holder : 0); break;
		case SDT_BIND_ON_LOAD: {
			treenode focus = tonode(get(node(name, x))); 
			if (focus) ptr = &o(SDTType, focus); 
			else ptr = 0;
			break;
		}
		}
	}
	#define bindObjPtrToNode(name, x) bindObjPtrToNodeByName(#name, name, x)

	template <typename NumberType>
	static void bindNumberToNodeByName(char* name, NumberType & val, treenode x)
	{
		switch (getBindMode()) {
		case SDT_BIND_ON_SAVE:set(assertsubnode(x, name, DATA_FLOAT), val); break;
		case SDT_BIND_ON_LOAD: val = get(node(name, x)); break;
		}
	}
	#define bindNumberToNode(name, x) bindNumberToNodeByName(#name, name, x)
};


class SqlDelegate : public SimpleDataType
{

/// <summary>	A macro that defines if a column as not found. Returned by the SqlDelegate::getColId() if it can find that column.</summary>
#define SQL_COL_NOT_FOUND INT_MAX
/// <summary>	"Not found" table is one that it tried to resolve but couldn't. </summary>
#define SQL_TABLE_NOT_FOUND (INT_MAX - 2)

#define SQL_COL_END ((const char*) 0x2)
#define SQL_NULL SqlValue(SqlValue::Null, 0)

public:
	virtual bool canResolveRefsAtParseTime() {return true;}
	virtual int getColId(int tableId, const char* colName) = 0;
	virtual const char* enumerateColNames(int tableId, int colNum){return SQL_COL_END;}
	virtual struct SqlValue getValue(int tableId, int row, int colId) {return SQL_NULL;}

	virtual int getTableId(const char* tableName) {return 0;}
	virtual int getRowCount(int tableId) {return 0;}
};

