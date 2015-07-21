#pragma once
#include "basicclasses.h"
#include "basicmacros.h"
#include "datatypes.h"
#include "basicutils.h"

// if i'm compiling the engine then I don't yet have access
// to some of the commands I need, so include the right files
#ifdef FLEXSIM_ENGINE_COMPILE
	extern "C" __declspec(dllexport) char* bbgetbuffer(treenode x);
	extern "C" __declspec(dllexport) int bbsetsize(treenode x, int size);
	extern "C" __declspec(dllexport) int bbgetsize(treenode x);
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
	friend class TableView;
private:

	static int bindMode;
	static char* displayStr;
	static size_t displayStrMaxSize;
	static char* displayStrCopyPoint;
	static bool displayVerbose;
	static int detachAfterBind;
	static std::vector<NodeRef> nodeList;
	static void attachSDTDerivative(TreeNode* x);
	static void bindSDTNode(TreeNode* x);
	static void detachSDTDerivative(TreeNode* x);
	static SimpleDataType* createSDTDerivativeFromName(const char* name, TreeNode* holder);
	engine_export static TreeNode* s_getBindTree(TreeNode* x);
	engine_export static TreeNode* s_assertBindTree(TreeNode* x);
	static Variant curValue;
	static const char * curValueName;
	engine_export TreeNode* assertBindTree();

protected:

public:
	engine_export static void appendToDisplayStr(const char* text);
	static void appendToDisplayStr(double val) { 
		char buffer[100]; 
		double absVal = val >= 0 ? val : -val;
		if (absVal == 0.0 || (absVal > 0.000001 && absVal < 1000000000.0))
			sprintf(buffer, "%f", val); 
		else sprintf(buffer, "%e", val);
		appendToDisplayStr(buffer);
	}
	static void appendToDisplayStr(int val) { char buffer[100]; sprintf(buffer, "%d", val); appendToDisplayStr(buffer); }
	static void appendToDisplayStr(const std::string& str) { appendToDisplayStr(str.c_str()); }
	engine_export static bool isDisplayVerbose();
	engine_export static void bindNodeList(int doBindMode, bool detachReattach, int startIndex = 0);
	static void clearAttsFromNodeList();
	TreeNode* holder;
	SimpleDataType() : holder(0) {}
	virtual ~SimpleDataType(){}
	virtual const char* getClassFactory(){return 0;}
	virtual void bind(){}
	engine_export void bind(int bindMode);
	engine_export virtual char* toString(int verbose);
engine_private:
	virtual TreeNode* getObjectTree() { return 0; }
	virtual TreeNode* getLabelNode(const char* labelName, bool assert) { return 0; }
	virtual TreeNode* getLabelNode(int labelRank, bool assert) { return 0; }
public:
	virtual Variant evaluate(const VariantParams& params) { return holder; }
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

	engine_export static int getBindMode();
	engine_export static Variant& getCurValue();
	engine_export static const char * getCurValueName();
	engine_export Variant getValue(const char* name);
	engine_export void setValue(const char* name, Variant value);
	engine_export TreeNode* bindByName(const char* name, int asSubNode, int dataType, int * added = 0);

	engine_export void bindDoubleByName(const char* name, double& val, int asSubNode);
#define bindDouble(name, asSubNode) bindDoubleByName(#name, name, asSubNode)
	engine_export void bindNodeRefByName(const char* name, NodeRef& val, int asSubNode);
#define bindNodeRef(name, asSubNode) bindNodeRefByName(#name, name, asSubNode)
template<class ObjType>
	void bindObjRefByName(const char* name, ObjRef<ObjType>& val, int asSubNode)
	{
		bindNodeRefByName(name, val, asSubNode);
	}
#define bindObjRef(name, asSubNode) bindObjRefByName(#name, name, asSubNode)

	/// <summary>	Binds a double with "unknown" type. Use this method if the name you want to bind by is
	/// 			different than the name of the member itself. Otherwise just use
	/// 			bindUnknownDouble()</summary>
	/// <param name="name">	The name of the member. </param>
	/// <param name="val"> 	[in,out] The value. </param>
	engine_export void bindUnknownDoubleByName(const char* name, double& val);

	/// <summary>	Binds a double with "unknown" type. Similar to bindDouble() or
	///				bindNumber(), except this method will check if tonode(value)
	///				is a valid node reference, and if so, it will save a coupling pointer
	///				to the node instead of using number data, so the reference will
	/// 			properly be saved/loaded. 
	/// 			
	/// 			Note that this is mostly available for backwards compatibility. 
	/// 			Going forward you should store such members as Variants and use bindVariant().
	/// 			Note: bindUnknownDouble is a macro that expands the parameter to a name/value
	/// 			pair for calling bindUnknownDoubleByName. </summary>
	/// <param name="name">	The name of the member to bind. </param>
	#define bindUnknownDouble(name) bindUnknownDoubleByName(#name, name)

	template<class T>
	void bindNumberByName(const char* name, T& val)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		case SDT_BIND_ON_DISPLAY: {
			char tempStr[1000];
			if (((double)(int)val) != ((double)val)) {
				double absVal = fabs((double)val);
				if (absVal < 1000000000000.0 && absVal > 0.00001)
					sprintf(tempStr, "%s: %f%s", name, (double)val, isDisplayVerbose() ? "\r\n" : ", ");
				else sprintf(tempStr, "%s: %e%s", name, (double)val, isDisplayVerbose() ? "\r\n" : ", ");
			} else sprintf(tempStr, "%s: %d%s", name, (int)val, isDisplayVerbose() ? "\r\n" : ", ");
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
				val = (T)(double)getCurValue();
			}
			break;
		case SDT_BIND_GET_VALUE:
			if (strcmp(name, getCurValueName()) == 0) {
				getCurValue() = (double)val;
			}
			break;
		}
	}
	#define bindNumber(name) bindNumberByName(#name, name)


	template<class T>
	void bindEnumByName(const char* name, T& val)
	{
		int bindMode = getBindMode();
		int valAsInt = static_cast<int>(val);
		bindNumberByName(name, valAsInt);
		if (bindMode == SDT_BIND_ON_LOAD || bindMode == SDT_BIND_SET_VALUE)
			val = static_cast<T>(valAsInt);
	}
	#define bindEnum(name) bindEnumByName(#name, name)

	template<class Str>
	void bindStringByName(const char* name, Str& val)
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
				val = getCurValue().c_str();
			}
			break;
		case SDT_BIND_GET_VALUE:
			if (strcmp(name, getCurValueName()) == 0) {
				getCurValue() = val.c_str();
			}
			break;
		}

	}
	#define bindString(name) bindStringByName(#name, name)

	engine_export void bindByteBlockByName(const char* name, ByteBlock& val, int asSubNode);
	#define bindByteBlock(name, asSubNode) bindByteBlockByName(#name, name, asSubNode)

	template<class Type, class SizeType>
	void bindLocalArrayByName(const char* name, Type* val, SizeType numElements)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
			// else continue into load/save
			case SDT_BIND_ON_SAVE:
			case SDT_BIND_ON_LOAD: {
				TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
				if(bindMode == SDT_BIND_ON_SAVE) {
					bbsetsize(theNode, (int)numElements * sizeof(Type));
					memcpy(bbgetbuffer(theNode), val, numElements * sizeof(Type));
				}
				else memcpy(val, bbgetbuffer(theNode), numElements * sizeof(Type));
				break;
			}
			case SDT_BIND_ON_DISPLAY:
				appendToDisplayStr(name);
				appendToDisplayStr(": ");
				for (int i = 0; i < numElements; i++) {
					StlValueBinder<Type>::Displayer(val + i);
					appendToDisplayStr(" ");
				}
				if (isDisplayVerbose())
					appendToDisplayStr("\r\n");
				break;
		}
	}
	#define bindLocalArray(name, nrBytes) bindLocalArrayByName(#name, name, nrBytes)

	void bindLocalBufferByName(const char* name, void* val, int nrBytes)
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
	void bindHeapArrayByName(const char* name, Type*& val, SizeType& numElements)
	{
		int bindMode = getBindMode();

		switch (bindMode) {
		// else continue into load/save
		case SDT_BIND_ON_SAVE:
		case SDT_BIND_ON_LOAD: {
			TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
			if(bindMode == SDT_BIND_ON_SAVE) {
				bbsetsize(theNode, numElements * sizeof(Type));
				memcpy(bbgetbuffer(theNode), val, numElements * sizeof(Type));
			}
			else {
				numElements = bbgetsize(theNode) / sizeof(Type);
				val = new Type[numElements];
				memcpy(val, bbgetbuffer(theNode), numElements * sizeof(Type));
			}
			break;
		}
		}
	}
	#define bindHeapArray(name, numElements) bindHeapArrayByName(#name, name, numElements)

	private:
	template<class Type>
	void displayFlexSimArray(Type& val)
	{
		char buffer[100];
		sprintf(buffer, "Array[%d]: {", (int)val.size());
		appendToDisplayStr(buffer);
		for (auto x = val.begin(); x != val.end(); x++) {
			if (x != val.begin())
				appendToDisplayStr(", ");
			StlValueBinder<Type::ElementType>::Displayer(x);
		}
		appendToDisplayStr("}");
	}

	public:
	// bind method for treenodearray and string array
	template<class Type>
	void bindFlexSimArrayByName(const char* name, Type& val)
	{
		int bindMode = getBindMode();
		switch (bindMode) {
			// else continue into load/save
			case SDT_BIND_ON_SAVE: {
				TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
				clearcontents(theNode);
				for (auto x = val.begin(); x != val.end(); x++)
					StlValueBinder<Type::ElementType>::Saver(nodeinsertinto(theNode), x);
				break;
			}
			case SDT_BIND_ON_LOAD: {
				TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
				int numElements = content(theNode);
				val.resize(numElements);
				for (int i = 1; i <= content(theNode); i++)
					val[i] = StlValueBinder<Type::ElementType>::Loader(rank(theNode, i));
				break;
			}
			case SDT_BIND_ON_DISPLAY: displayFlexSimArray(val); break;
		}
	}
	// template specialization for doublearray and intarray
	template<>
	void bindFlexSimArrayByName <doublearray>
		(const char* name, doublearray& val)
	{
		int bindMode = getBindMode();
		switch (bindMode) {
			// else continue into load/save
			case SDT_BIND_ON_SAVE: bindLocalArrayByName(name, val.begin(), val.size()); break;
			case SDT_BIND_ON_LOAD: {
				TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
				size_t numElements = bbgetsize(theNode) / sizeof(double);
				val.resize(numElements);
				bindLocalArrayByName(name, val.begin(), numElements);
				break;
			}
			case SDT_BIND_ON_DISPLAY: displayFlexSimArray(val); break;
		}
	}
	template<>
	void bindFlexSimArrayByName <intarray>
		(const char* name, intarray& val)
	{
		int bindMode = getBindMode();
		switch (bindMode) {
			// else continue into load/save
			case SDT_BIND_ON_SAVE: bindLocalArrayByName(name, val.begin(), val.size()); break;
			case SDT_BIND_ON_LOAD: {
				TreeNode* theNode = bindByName(name, 0, DATA_BYTEBLOCK, 0);
				size_t numElements = bbgetsize(theNode) / sizeof(int);
				val.resize(numElements);
				bindLocalArrayByName(name, val.begin(), numElements);
				break;
			}
			case SDT_BIND_ON_DISPLAY: displayFlexSimArray(val); break;
		}
	}

	#define bindFlexSimArray(name) bindFlexSimArrayByName(#name, name)

	engine_export void bindNodePtrByName(const char* name, TreeNode*& val);
	engine_export void bindSubNodeByName(const char* name, TreeNode*& val, int dataType = 1);
	engine_export void bindObjPtrByName(const char* name, SimpleDataType*& val);
	engine_export void bindVariantByName(const char* name, Variant& var);

#define bindSubNode(name, dataType) bindSubNodeByName(#name, name, dataType)
#define bindNodePtr(name) bindNodePtrByName(#name, name)
#define bindObjPtr(name) bindObjPtrByName(#name, (SimpleDataType*&)name)
#define bindVariant(name) bindVariantByName(#name, name)

	engine_export void bindSimpleDataMemberByName(const char* name, SimpleDataType& member);

	template <class T = std::enable_if<std::is_base_of<SimpleDataType, T>::value>::type>
	void bindSdtMemberByName(const char* name, T& member)
	{
		bindSimpleDataMemberByName(name, member);
	}

#define bindSdtMember(name) bindSdtMemberByName(#name, name)

	engine_export TreeNode* getBindTree();

	// now for some stl stuff
	
	// original Saver() definitions
	template <typename Type, class Enable = void> class StlValueBinder;
	
	template <typename Type>
	class StlValueBinder<Type, typename std::enable_if<!std::is_pointer<Type>::value && !std::is_integral<Type>::value && !std::is_floating_point<Type>::value, void>::type> {
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

	template <class Type> 
	class StlValueBinder<Type, typename std::enable_if<std::is_floating_point<Type>::value, void>::type> {
	public:
		static treenode Saver(treenode x, Type* toVal)
			{return setnodenum(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static Type Loader(treenode x)
			{return (Type)get(x);}
		static void Displayer(Type* x)
			{FORMAT_AND_DISPLAY("%lf", (double)*x);}
	};

	template <class Type> 
	class StlValueBinder<Type, typename std::enable_if<std::is_integral<Type>::value, void>::type> {
	public:
		static treenode Saver(treenode x, Type* toVal)
			{return setnodenum(nodeadddata(x, DATA_FLOAT), (double)*toVal);}
		static Type Loader(treenode x)
			{return (Type)get(x);}
		static void Displayer(Type* x)
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

	template <> class StlValueBinder<NodeRef> {
	public:
		static treenode Saver(treenode x, NodeRef* toVal)
		{
			return nodepoint(nodeadddata(x, DATA_POINTERCOUPLING), *toVal);
		}
		static NodeRef Loader(treenode x)
		{
			return tonode(get(x));
		}
		static void Displayer(NodeRef* x)
		{
			std::string str;
			if (objectexists(*x))
				str = nodetomodelpath(*x, 2);
			else if (!(*x))
				str = "NULL";
			else str = "[Invalid Ptr]";
			appendToDisplayStr(str.c_str());
		}
	};

	template <class T> 
	class StlValueBinder<T*, typename std::enable_if<std::is_base_of<SimpleDataType, T>::value, void>::type> {
	public:
		static treenode Saver(treenode x, T** toVal)
			{return nodepoint(nodeadddata(x, DATA_POINTERCOUPLING), *toVal ? (*toVal)->holder : 0);}
		static T* Loader(treenode x)
		{
			treenode dereference = tonode(get(x)); 
			if (objectexists(dereference))
				return dereference->object<T>();
			return 0;
		}
		static void Displayer(T** x)
		{
			if(x && (*x))
				StlValueBinder<treenode>::Displayer(&((*x)->holder));
			else appendToDisplayStr("NULL");
		}
	};


	template <class T>
	class StlValueBinder<T*, typename std::enable_if<!std::is_base_of<SimpleDataType, T>::value, void>::type> {
	public:
		static void Saver(treenode x, T** toVal)
		{
			(*toVal)->bind(x);
		}
		static T* Loader(treenode x)
		{
			T* newT = new T;
			newT->bind(x);
			return newT;
		}
		static void Displayer(T** x)
		{
			(*x)->bind(0);
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
		case SDT_BIND_ON_SAVE:setnodenum(assertsubnode(x, name, DATA_FLOAT), val); break;
		case SDT_BIND_ON_LOAD: val = get(node(name, x)); break;
		}
	}
	#define bindNumberToNode(name, x) bindNumberToNodeByName(#name, name, x)


	template <typename SubClass>
	static void bindCallbackByName(char* name, Variant (SubClass::*callback)(FLEXSIMINTERFACE))
	{
		if (getBindMode() == SDT_BIND_GET_VALUE && strcmp(getCurValueName(), name) == 0)
			getCurValue() = (double)(size_t)force_cast<void*>(callback);
	}
	#define bindCallback(name, classType) bindCallbackByName(#name, &classType::name)
};


/// <summary>	Defines an interface for interaction with FlexSim's SQL parser/evaluator. </summary>
/// <remarks>	Sub-class implementations act as delegates to the parser,
/// 			providing, first, mappings of table and column names to table and
/// 			column id's, and second, an interface for retrieving values out of
/// 			those tables.</remarks>
class SqlDataSource : public SimpleDataType
{

/// <summary>	A macro that defines if a column as not found. Returned by the SqlDataSource::getColId() if it cannot find that column.</summary>
#define SQL_COL_NOT_FOUND INT_MAX
/// <summary>	"Not found" table is one that it tried to resolve but couldn't. </summary>
#define SQL_TABLE_NOT_FOUND (INT_MAX - 2)

#define SQL_COL_END ((const char*) 0x2)
#define SQL_NULL Variant()

public:
	/// <summary>	Returns true if the delegate can resolve column and table refs at parse time, otherwise false. </summary>
	/// <remarks>	Default is true. If false, this means that references must be resolved at query time. This 
	/// 			would only be useful if there is a mechanism by which you can parse and store a query beforehand,
	/// 			and then run the query later, potentially multiple times. This could improve speed because
	/// 			you're only parsing once and querying multiple times, instead parsing on each query. </remarks>
	/// <returns>	true if it can resolve references at parse time, false if not. </returns>
	virtual bool canResolveRefsAtParseTime() {return true;}

	/// <summary>	Returns the column identifier of the column with the defined name in the defined table. </summary>
	/// <remarks>	Anthony, 8/27/2014. </remarks>
	/// <param name="tableId">	Identifier for the table. </param>
	/// <param name="colName">	Name of the column. </param>
	/// <returns>	The column identifier. </returns>
	virtual int getColId(int tableId, const char* colName) { return SQL_COL_NOT_FOUND; }

	/// <summary>	Enumerate column names of a table. </summary>
	/// <remarks>	Anthony, 8/27/2014. </remarks>
	/// <param name="tableId">	 This is used if the parser needs a full enumeration of the columns of a table,
	/// 			specifically for a SELECT * clause. The sql parser will start with colNum = 0, and then
	/// 			iteratively call this method, incrementing colNum each time, until the method returns 
	/// 			SQL_COL_END. Each call should return the name of a column.</param>
	/// <param name="colNum"> 	The 0-based column number. </param>
	/// <returns>	Returns the name of a column, or SQL_COL_END. </returns>
	virtual const char* enumerateColNames(int tableId, int colNum){return SQL_COL_END;}

	/// <summary>	Retrieves a value out of a table. </summary>
	/// <remarks>	Anthony, 8/27/2014. </remarks>
	/// <param name="tableId">	Identifier for the table. </param>
	/// <param name="row">	  	The row. </param>
	/// <param name="colId">  	Identifier for the col. </param>
	/// <returns>	The value. </returns>
	virtual Variant getValue(int tableId, int row, int colId) {return SQL_NULL;}

	/// <summary>	Gets a table's identifier. </summary>
	/// <remarks>	Anthony, 8/27/2014. </remarks>
	/// <param name="tableName">	Name of the table. </param>
	/// <returns>	The table identifier. </returns>
	virtual int getTableId(const char* tableName) {return 0;}

	/// <summary>	Returns the number of rows in a table. </summary>
	/// <remarks>	Anthony, 8/27/2014. </remarks>
	/// <param name="tableId">	Identifier for the table. </param>
	/// <returns>	The number of rows in the table. </returns>
	virtual int getRowCount(int tableId) {return 0;}

	virtual const char* getClassFactory() { return "SqlDataSource"; }
};

// 
class ParseStatisticStringObj : public SimpleDataType
{
public:
	const static int PSS_MODE_GET = 0; // default - get the value specified by the string
	const static int PSS_MODE_ASSERT = 1; // make sure that the object will record the value
	const static int PSS_MODE_ASSERT_FH = 2; // make sure that the object will record the full history
	const static int PSS_MODE_GET_FH = 3; // get the bundle associated with the full history
	const static int PSS_MODE_GET_TIMECOL = 4; // get the column in the history bundle with the time 
	const static int PSS_MODE_GET_VALCOL = 5; // get the column in the history bundle with the values
	const static int PSS_MODE_QUERY_ANY = 6; // get whether or not this object can parse statistic strings
	// Note: PSS_MODE_QUERY allows any object with this method to confirm that it has this interface,
	// without changing its inheritance hierarchy.

	virtual Variant parseStatisticString(const string& statString, int mode, const Variant& data) = 0;
	engine_export Variant parseStatisticString(FLEXSIMINTERFACE);
	virtual void bind() override { bindCallback(parseStatisticString, ParseStatisticStringObj); }
};

/// <summary>	Defines the TrackedVariable class. </summary>
/// <remarks>	Tracked variables accept a sequence of values (one at a time)
///				and provide methods to get the current, min, max, and avg. </remarks>
class TrackedVariable : public ParseStatisticStringObj
{
	friend SimpleDataType* engine_createsdtderivative(char* classname, TreeNode* holder);

public:
	engine_export virtual const char* getClassFactory() { return "TrackedVariable"; }
	engine_export virtual void bind();

	treenode data;
	double isTimeWeighted;
	double fullHistory;
	double cumulative;
	double cumulativeTime;
	double minValue;
	double maxValue;
	double numEntries;

	engine_export virtual void reset();
	engine_export virtual void resetStats();
	engine_export virtual void set(double value);

	engine_export double getAvg();
	engine_export double getMin();
	engine_export double getMax();
	engine_export double getCurrent();
	engine_export double getCount();

	engine_export virtual Variant parseStatisticString(const string& statString, int mode, const Variant& data) override;

	engine_export TrackedVariable();
	engine_export ~TrackedVariable() {}
};

/// <summary>	Defines the Statistic class, a set of TrackedVariables. </summary>
/// <remarks>	The StatisticSet class optionally records content, input, output, and
///				staytime, each as a tracked variable.</remarks>
class StatisticSet : public ParseStatisticStringObj
{
	friend SimpleDataType* engine_createsdtderivative(char* classname, TreeNode* holder);

public:
	engine_export virtual const char* getClassFactory() { return "StatisticSet"; }
	engine_export virtual void bind();

	double recordContent;
	double recordInput;
	double recordOutput;
	double recordStaytime;
	double totalStaytime;

	ObjRef<TrackedVariable> content;
	ObjRef<TrackedVariable> input;
	ObjRef<TrackedVariable> output;
	ObjRef<TrackedVariable> staytime;

	engine_export StatisticSet();

	engine_export virtual void assertVariables();
	engine_export virtual void reset();
	engine_export virtual void resetStats();

	engine_export virtual void updateEntryStats();
	engine_export virtual void updateExitStats(double staytime);

	engine_export virtual double getStatisticByString(const string& tvString, const string& quantity);
	engine_export virtual Variant parseStatisticString(const string& statString, int mode, const Variant& data) override;
};

