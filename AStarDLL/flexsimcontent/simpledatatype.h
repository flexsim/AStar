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
	friend class ObjectDataType;
	friend class TableView;
private:

	static int bindMode;
	static char* displayStr;
	static size_t displayStrMaxSize;
	static char* displayStrCopyPoint;
	static bool displayVerbose;
	static int detachAfterBind;
	static void attachSDTDerivative(TreeNode* x);
	static void bindSDTNode(TreeNode* x);
	static void detachSDTDerivative(TreeNode* x);
	static SimpleDataType* createSDTDerivativeFromName(const char* name, TreeNode* holder);
	engine_export static TreeNode* s_getBindTree(TreeNode* x);
	engine_export static TreeNode* s_assertBindTree(TreeNode* x);
	static Variant curValue;
	static const char * curValueName;
	engine_export TreeNode* assertBindTree();
	static std::vector<NodeRef> nodeList;

protected:

public:
	virtual CouplingDataType* toCoupling() { return nullptr; }
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
	engine_export static void bindNodeList(int doBindMode, bool detachReattach, int startIndex = 0, std::vector<NodeRef>* list = nullptr);
	static void clearAttsFromNodeList(std::vector<NodeRef>* list = nullptr);
	TreeNode* holder;
	SimpleDataType() : holder(0) {}
	virtual ~SimpleDataType(){}
	virtual const char* getClassFactory(){return 0;}
	engine_export virtual void bind();
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
	static void setBindMode(int toMode);
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
				str = nodetomodelpath(*x, 1);
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
				str = nodetomodelpath(*x, 1);
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

	
	/** @name Event Binding
	*	Methods associated with enumerating and subscribing to events
	*/
	//@{
	public:
	virtual void bindEvents() {}
	virtual TreeNode* getEventInfoObject(const char* eventTitle) { return nullptr; }

	static const int EVENT_INFO_PARAMS = 0x1;
	static const int EVENT_INFO_DEFAULT_CODE = 0x2;
	static const int EVENT_INFO_CATEGORY = 0x3;
	static const int EVENT_INFO_LOCALIZED_TITLE = 0x4;
	static const int EVENT_INFO_REQUIREMENTS = 0x5;
	engine_export virtual Variant getEventInfo(const char* eventTitle, int info);
	engine_export virtual Variant getEventInfo(FLEXSIMINTERFACE);

	static const int BIND_EVENT_ENUMERATE = 1;
	static const int BIND_EVENT_ASSERT = 2;
	static const int BIND_EVENT_ON_LOAD = 3;
	static const int BIND_EVENT_FILL_BINDING_ENTRY = 4;

	// flags and op codes for flagging extended functionality as well as retrieving data associated with
	// that functionality
	static const int EVENT_TYPE_MASK = 0x7;
	static const int EVENT_TYPE_DEFAULT = 0x1;
	static const int EVENT_TYPE_VALUE_GETTER = 0x2;
	static const int EVENT_TYPE_VALUE_NOTIFIER = 0x4;

	/// <summary>	A flag to not allow the event binding to a node based on the byte offset from the sdt memory pointer.</summary>
	static const int EVENT_DO_NOT_BIND_BYTE_OFFSET = 0x100;
	static const int EVENT_ATTRIBUTE = 0x200;
	static const int EVENT_NO_DEFAULT_CODE = 0x400;
	static const int EVENT_RELAYED = 0x800;
	static const int EVENT_STAT = 0x1000;

	static const int EVENT_REQUIREMENTS = 0x30000; // the mask around all requirments flags
	static const int EVENT_REQUIREMENTS_BIT_SHIFT = 16; // shift the requirements masked value 16 bits to get the number of requirements
	static const int EVENT_1_REQUIREMENT = 0x10000;
	static const int EVENT_2_REQUIREMENTS = 0x20000;
	static const int EVENT_3_REQUIREMENTS = 0x30000;
	static int getNumRequirementsFromFlags(int flags) 
	{ 
		return (flags & SimpleDataType::EVENT_REQUIREMENTS) >> SimpleDataType::EVENT_REQUIREMENTS_BIT_SHIFT; 
	}

	engine_export static int getBindEventMode();

	typedef TreeNode*(SimpleDataType::*EventNodeResolver) ();
	typedef TreeNode*(SimpleDataType::*EventNodeResolver1) (const Variant& p1);
	typedef TreeNode*(SimpleDataType::*EventNodeResolver2) (const Variant& p1, const Variant& p2);
	typedef TreeNode*(SimpleDataType::*EventNodeResolver3) (const Variant& p1, const Variant& p2, const Variant& p3);

	typedef double(SimpleDataType::*CurValueResolver) ();
	typedef double(SimpleDataType::*CurValueResolver1) (const Variant& p1);
	typedef double(SimpleDataType::*CurValueResolver2) (const Variant& p1, const Variant& p2);
	typedef double(SimpleDataType::*CurValueResolver3) (const Variant& p1, const Variant& p2, const Variant& p3);

	class EventBindingEntry
	{
	public:
		EventBindingEntry() : flags(0), resolver(nullptr), node(nullptr)
		{}
		EventBindingEntry(SimpleDataType* sdt, const char* nodeName, TreeNode*& node, const char* eventTitle, long long flags, 
				EventNodeResolver resolver, CurValueResolver valueResolver) :
			nodeName(nodeName ? nodeName : ""), 
			node(&node), 
			eventTitle(eventTitle ? eventTitle : ""), 
			flags(flags | s_bindEventFlags), 
			resolver(resolver), 
			valueResolver(valueResolver)
		{
			if (!(flags & EVENT_DO_NOT_BIND_BYTE_OFFSET))
				nodeByteOffset = (char*)(void*)(&node) - (char*)(void*)sdt;
			if (this->flags & EVENT_REQUIREMENTS)
				this->node = nullptr;
		}
		/// <summary>	Future use: when a TE binds events, he's going to forward bindEvents to his navigator, which makes it
		/// 			so nodeByteOffset can't be used (the events aren't members of the TE class, but on something like AGVData). </summary>
		static int s_bindEventFlags;
		std::string nodeName;
		std::string eventTitle;
		long long flags;
		int nodeByteOffset = 0;
		TreeNode** node;
		EventNodeResolver resolver;
		CurValueResolver valueResolver;
		int numForwardsContained = 0;
	};

	private:
	engine_export void bindEventByNameEx(const char* nodeName, TreeNode*& node, const char* eventTitle, int flags = 0, EventNodeResolver resolver = nullptr, CurValueResolver valueResolver = nullptr);
	engine_export void bindRelayedClassEventsEx(const char* prefix, int flags, EventNodeResolver resolver, SimpleDataType* sdt);
	public:
	template <class ResolverCallbackType = nullptr_t, class ValueResolverCallbackType = nullptr_t>
	void bindEventByName(const char* nodeName, TreeNode*& node, const char* eventTitle, int flags = 0, 
		ResolverCallbackType resolver = nullptr, ValueResolverCallbackType valueResolver = nullptr)
	{
		bindEventByNameEx(nodeName, node, eventTitle, flags, force_cast<EventNodeResolver>(resolver), force_cast<CurValueResolver>(valueResolver));
	}
	#define bindEvent(name, ...) bindEventByName("on" #name, on##name, "On" #name, __VA_ARGS__)

	template <class ResolverCallbackType = nullptr_t, class ValueResolverCallbackType = nullptr_t>
	void bindEventWithRequirement(const char* eventTitle, int flags, ResolverCallbackType resolver, ValueResolverCallbackType valueResolver)
	{
		TreeNode* x;
		bindEventByNameEx("", x, eventTitle, flags, force_cast<EventNodeResolver>(resolver), force_cast<CurValueResolver>(valueResolver));
	}


	template <class RelayToClass, class ResolverCallbackType = nullptr_t>
	void bindRelayedClassEvents(const char* prefix, int flags, ResolverCallbackType resolver)
	{
		switch (getBindEventMode()) {
			case BIND_EVENT_ENUMERATE: 
			case BIND_EVENT_FILL_BINDING_ENTRY:
			{
				RelayToClass relayToClass;
				bindRelayedClassEventsEx(prefix, flags, force_cast<EventNodeResolver>(resolver), &relayToClass);
				break;
			}
		}
	}

	engine_export void bindStatisticsAsEvents();

	void bindEventsOnLoad();

	engine_export void enumerateEvents(TreeNode* destNode, bool asEventBinding);
	engine_export void enumerateEvents(EventBinding* dest);
	engine_export Variant enumerateEvents(FLEXSIMINTERFACE);

	engine_export TreeNode* assertEvent(const char* eventTitle);
	engine_export TreeNode* assertEvent(EventBinding* enumeration);
	engine_export TreeNode* assertEvent(const char* eventTitle, const Variant& p1, const Variant& p2 = Variant(), const Variant& p3 = Variant(), int* outFlags = nullptr);
	engine_export TreeNode* assertEvent(EventBinding* enumeration, const Variant& p1, const Variant& p2 = Variant(), const Variant& p3 = Variant());
	engine_export Variant assertEvent(FLEXSIMINTERFACE);
	engine_export TreeNode* assertEventNode(const char* eventTitle, TreeNode*& node);
	
	engine_export double getEventCurValue(EventBinding* binding);
	engine_export double getEventCurValue(EventBinding* binding, const Variant& p1, const Variant& p2 = Variant(), const Variant& p3 = Variant());
	engine_export double getEventCurValue(const char* eventTitle);
	engine_export double getEventCurValue(const char* eventTitle, const Variant& p1, const Variant& p2 = Variant(), const Variant& p3 = Variant());


#define FIRE_SDT_EVENT(node, ...) if (node) { node->evaluate(__VA_ARGS__); }
#define FIRE_SDT_EVENT_VALUE_GETTER(node, ...) (node ? node->evaluate(__VA_ARGS__) : Variant())
#define FIRE_SDT_EVENT_VALUE_CHANGE(node, newValue, oldValue) {if (node && newValue != oldValue) { node->evaluate(newValue, oldValue); }}

	private:
	/// <summary>	Makes sure that the enumeration is properly filled. </summary>
	/// <remarks>	Anthony.johnson, 8/14/2015. </remarks>
	/// <param name="enumeration">	[in,out] The enumeration. </param>
	bool assertValidEventBindingData(EventBinding* enumeration);
	TreeNode* SimpleDataType::assertRelayedEvent(EventBindingEntry& entry, const Variant& p1, const Variant& p2, const Variant& p3);
	TreeNode* assertEvent(EventBindingEntry& entry);
	TreeNode* assertEvent(EventBindingEntry& entry, const Variant& p1, const Variant& p2, const Variant& p3);
	double getEventCurValue(EventBindingEntry& entry);
	double getEventCurValue(EventBindingEntry& entry, const Variant& p1, const Variant& p2, const Variant& p3);
	static int s_bindEventMode;
	static EventBinding* s_eventBinding;
	static const char* s_assertEventTitle;
	static TreeNode* s_assertedEvent;
	static EventBindingEntry* s_eventBindingEntry;
	static std::string s_forwardingPrefix;
	static EventNodeResolver s_relayedEventResolver;
	TreeNode* getEventNode(const char* nodeName, const char* eventTitle, int flags, bool assert);
	//@}

	/** @name Statistic Binding
	*	Methods associated with enumerating and subscribing to statistics
	*/
	//@{
	public:
	virtual void bindStatistics() {}

	static const int BIND_STAT_ENUMERATE = 1;
	static const int BIND_STAT_ASSERT = 2;
	static const int BIND_STAT_ON_LOAD = 3;
	static const int BIND_STAT_FILL_BINDING_ENTRY = 4;
	static const int BIND_STAT_ON_RUNWARM = 5;
	static const int BIND_STAT_ON_BIND_EVENTS = 6;
	static const int BIND_STAT_ENUMERATE_REQUIREMENT_POSSIBILITIES = 7;

	// flags and op codes for flagging extended functionality as well as retrieving data associated with
	// that functionality
	static const int STAT_TYPE_MASK = 0x7;
	static const int STAT_TYPE_LEVEL = 0x1; // the default, level stats change by delta
	static const int STAT_TYPE_CUMULATIVE = 0x2; // input, output can only be incremented; max, min, and avg are pointless
	static const int STAT_TYPE_TIME_SERIES = 0x3; // staytime is a stream of unrelated values; current value is less important
	static const int STAT_TYPE_CATEGORICAL = 0x4; // discrete is a set of discrete values that don't relate mathematically, i.e. state

	static const int STAT_USE_HISTORY = 0x10;
	static const int STAT_USE_PROFILE = 0x20;
	static const int STAT_IGNORE_WARMUP = 0x40;

	static const int STAT_RELAYED = 0x100;
	static const int STAT_NOT_EVENT = 0x400;

	static const int STAT_REQUIREMENTS = 0x30000; // the mask around all requirments flags
	static const int STAT_REQUIREMENTS_BIT_SHIFT = 16; // shift the requirements masked value 16 bits to get the number of requirements
	static const int STAT_1_REQUIREMENT = 0x10000;
	static const int STAT_2_REQUIREMENTS = 0x20000;
	static const int STAT_3_REQUIREMENTS = 0x30000;
	static int getNumStatRequirementsFromFlags(int flags)
	{
		return (flags & SimpleDataType::STAT_REQUIREMENTS) >> SimpleDataType::STAT_REQUIREMENTS_BIT_SHIFT;
	}

	// These constants deal with the meaningful derivative values
	static const int STAT_DERIVE_CUR = 0x1;
	static const int STAT_DERIVE_MIN = 0x2;
	static const int STAT_DERIVE_MAX = 0x4;
	static const int STAT_DERIVE_AVG = 0x8;

	engine_export static int getStatDerivativesFromFlags(int flags);

	engine_export static int getBindStatisticMode();

	typedef TreeNode*(SimpleDataType::*StatNodeResolver1) (const Variant& p1);
	typedef TreeNode*(SimpleDataType::*StatNodeResolver2) (const Variant& p1, const Variant& p2);
	typedef TreeNode*(SimpleDataType::*StatNodeResolver3) (const Variant& p1, const Variant& p2, const Variant& p3);
	
	static const int STAT_ENUM_REQS_INVALID = 0;
	static const int STAT_ENUM_REQS_STATIC = 1;
	static const int STAT_ENUM_REQS_DYNAMIC = 2;
	typedef int(SimpleDataType::*StatRequirementEnumerator) (TreeNode* dest, const Variant& p1, const Variant& p2);
	

	class StatisticBindingEntry
	{
	public:
		static int s_bindStatFlags;
		ByteBlock statName;
		ByteBlock nodeName;
		int flags;
		int nodeByteOffset = 0;
		TreeNode** node;
		StatNodeResolver1 resolver;
		int numForwardsContained = 0;

		StatisticBindingEntry() : flags(0), resolver(nullptr), node(nullptr)
		{}
		StatisticBindingEntry(SimpleDataType* sdt, const char* _nodeName, TreeNode*& _node, const char* _statName, int _flags, StatNodeResolver1 _resolver)
			: node(&_node)
			, flags(_flags | s_bindStatFlags)
			, resolver(_resolver)
		{
			if (_nodeName)
				nodeName.write(_nodeName);

			if (_statName)
				statName.write(_statName);

			if (flags & STAT_REQUIREMENTS)
				node = nullptr;
			nodeByteOffset = (char*)(void*)(&_node) - (char*)(void*)sdt;
		}
	};

	private:
	engine_export void bindStatisticByNameEx(const char* nodeName, TreeNode*& node, const char* statName, int flags = 0, StatNodeResolver1 resolver = nullptr);
	engine_export void bindRelayedClassStatisticsEx(const char* prefix, int flags, StatNodeResolver1 resolver, StatRequirementEnumerator enumerator, SimpleDataType* sdt);
	public:
	template <class ResolverCallbackType = nullptr_t>
	void bindStatisticByName(const char* nodeName, TreeNode*& node, const char* statName, int flags = 0, ResolverCallbackType resolver = nullptr)
	{
		bindStatisticByNameEx(nodeName, node, statName, flags, force_cast<StatNodeResolver1>(resolver));
	}
	#define bindStatistic(name, ...) \
		bindStatisticByName(#name, name, #name, __VA_ARGS__);

	template <class ResolverCallbackType = nullptr_t>
	void bindStatisticWithRequirement(const char* statTitle, int flags, ResolverCallbackType resolver)
	{
		TreeNode* x;
		bindStatisticByNameEx("", x, statTitle, flags, force_cast<StatNodeResolver1>(resolver));
	}


	template <class RelayToClass, class ResolverCallbackType = nullptr_t, class EnumeratorCallbackType = nullptr_t>
	void bindRelayedClassStatistics(const char* prefix, int flags, ResolverCallbackType resolver, EnumeratorCallbackType enumerator = nullptr)
	{
		switch (getBindStatisticMode()) {
		case BIND_STAT_ENUMERATE:
		case BIND_STAT_FILL_BINDING_ENTRY:
		case BIND_STAT_ENUMERATE_REQUIREMENT_POSSIBILITIES: {
			RelayToClass relayToClass;
			bindRelayedClassStatisticsEx(prefix, flags, force_cast<StatNodeResolver1>(resolver), force_cast<StatRequirementEnumerator>(enumerator), &relayToClass);
			break;
		}
		}
	}

	void bindStatisticsOnLoad();

	engine_export void enumerateStatistics(TreeNode* destNode, bool asStatisticBinding);
	engine_export void enumerateStatistics(StatisticBinding* dest);
	engine_export Variant enumerateStatistics(FLEXSIMINTERFACE);

	engine_export TreeNode* assertStatistic(const char* statTitle);
	engine_export TreeNode* assertStatistic(StatisticBinding* enumeration);
	engine_export TreeNode* assertStatistic(const char* statTitle, const Variant& p1, const Variant& p2 = Variant(), const Variant& p3 = Variant(), int* outFlags = nullptr);
	engine_export TreeNode* assertStatistic(StatisticBinding* enumeration, const Variant& p1, const Variant& p2 = Variant(), const Variant& p3 = Variant());
	engine_export Variant assertStatistic(FLEXSIMINTERFACE);
	engine_export TreeNode* assertStatisticNode(const char* statTitle, TreeNode*& node);

	engine_export int enumerateRequirementPossibilities(const char* statTitle, TreeNode* destNode, const Variant& p1 = Variant(), const Variant& p2 = Variant());
	engine_export Variant enumerateRequirementPossibilities(FLEXSIMINTERFACE);

#define UPDATE_SDT_STAT(node, newValue) if (node) { node->objectAs(TrackedVariable)->set(newValue); }
#define UPDATE_SDT_STAT_DELTA(node, delta) if (node) {\
	TrackedVariable* tv = node->objectAs(TrackedVariable);\
	tv->set(tv->getCurrent() + delta); }
#define UPDATE_SDT_STAT_CUMULATIVE(node) UPDATE_SDT_STAT_DELTA(node, 1)
#define RESET_SDT_STAT(node, ...) if (node) {node->objectAs(TrackedVariable)->reset(__VA_ARGS__);}

	/// <summary>	Sets the SDT's primary value. </summary>
	/// <remarks>	 This is used to allow a user to use
	/// 			setlabel() or some other mechanism to set the value on a node. Child 
	/// 			classes should override this if they want setlabel() to set a value on 
	/// 			the node without removing/adding new data.</remarks>
	/// <param name="val">	The value. </param>
	/// <returns>	true if it succeeds, false if it cannot set its primary value to the given value. </returns>
	virtual bool setPrimaryValue(const Variant& val) { return false; }
	virtual Variant getPrimaryValue() { 
		VariantParams params;
		return evaluate(params);
	}

	private:
	/// <summary>	Makes sure that the enumeration is properly filled. </summary>
	/// <remarks>	Anthony.johnson, 8/14/2015. </remarks>
	/// <param name="enumeration">	[in,out] The enumeration. </param>
	bool assertStatisticBinding(StatisticBinding* enumeration);
	TreeNode* assertStatistic(StatisticBindingEntry& entry);
	TreeNode* assertStatistic(StatisticBindingEntry& entry, const Variant& p1, const Variant& p2, const Variant& p3);
	static int s_bindStatisticMode;
	static StatisticBinding* s_statBinding;
	static const char* s_assertStatisticName;
	static TreeNode* s_assertedStatistic;
	static StatisticBindingEntry* s_statBindingEntry;
	static std::string s_forwardingStatPrefix;
	static std::string s_statAsEventPrefix;
	static StatNodeResolver1 s_relayedStatResolver;
	static StatRequirementEnumerator s_requirementEnumerator;
	static SimpleDataType* s_enumerateObject;
	static const char* s_enumerateReqsName;
	static TreeNode* s_enumerateReqsNode;
	static Variant s_requirement1;
	static Variant s_requirement2;
	static int s_enumerateReqsResult;
	TreeNode* getStatisticNode(const char* nodeName, int flags, bool assert);

	//@}
};

/// <summary>	Event binding. Stores enumerated events and saves binding information for later use.  </summary>
/// <remarks>	Allows a "client" object to get an enumeration of an object's available events once, 
/// 			and then bind to a specific event without having to call bindEvents()
/// 			each time. This can be especially helpful at simulation run time if you don't want
/// 			to have to call bindEvents() over and over again each time you want to get the node
/// 			associated with an event. This method is much faster using a method that repeatedly 
/// 			calls bindEvents().
/// 			Here's how you work with it.
/// 			
/// 			// at model building time, or on reset
/// 			sdt->enumerateEvents(destNode, true); // this will populate the EventBinding with all the needed data
/// 			EventBinding* binding = destNode->objectAs(EventBinding);
/// 			binding->select("OnEntry"); // this selects the given event
/// 			
/// 			... later, during simulation run
/// 			treenode eventNode = sdt->assertEvent(binding); // will get the node associated with the event, without calling bindEvents().
/// 			
/// 			... also, you can switch to another sdt of the same class. Note that it MUST be of the same 
/// 			class, or else all hell will break loose.
/// 			treenode newEventNode = newSDT->assertEvent(binding);
/// 			</remarks>
class EventBinding : public SimpleDataType
{
public:
	virtual const char* getClassFactory() override { return "EventBinding"; }
	engine_export virtual void bind() override;
	ObjRef<SimpleDataType> object;
	int selected = -1;
	bool isSelectionValid() { return selected >= 0 && selected < events.size(); }
	void* virtualTable = nullptr;
	ByteBlock selectedEventTitle;
	/// <summary>	Selects the given event. This can be used in conjunction with SimpleDataType::assertEvent(EventBinding*, ...). 
	/// 			Instead of </summary>
	/// <remarks>	Anthony.johnson, 8/15/2015. </remarks>
	/// <param name="eventTitle">	The event title. </param>
	engine_export void select(const char* eventTitle);
	/// <summary>	Selects the given sdt, rebinding its event entries based on that sdt. </summary>
	/// <remarks>	This will rebind event node pointers. If there is a currently selected event, then
	/// 			for speed reasons it will only rebind that event's node. </remarks>
	/// <param name="sdt">	[in,out] If non-null, the sdt. </param>
	engine_export void select(SimpleDataType* sdt);
	std::vector<SimpleDataType::EventBindingEntry> events;
	const EventBindingEntry& getSelectedEntry() { return events[selected]; }
};

class StatisticBinding : public SimpleDataType
{
private:
	std::vector<SimpleDataType::StatisticBindingEntry> statistics;

public:
	virtual const char* getClassFactory() override { return "StatisticBinding"; }
	engine_export virtual void bind() override;
	ObjRef<SimpleDataType> object;
	int selected = -1;
	bool isSelectionValid() { return selected >= 0 && selected < statistics.size(); }
	void* virtualTable = nullptr;
	ByteBlock selectedStatisticTitle;
	/// <summary>	Selects the given statsitic. This can be used in conjunction with SimpleDataType::assertStatistic(StatisticBinding*, ...). 
	/// 			Instead of </summary>
	/// <remarks>	Anthony.johnson, 8/15/2015. </remarks>
	/// <param name="statName">	The statistic name. </param>
	engine_export void select(const char* statName);
	/// <summary>	Selects the given sdt, rebinding its stat entries based on that sdt. </summary>
	/// <remarks>	This will rebind stat node pointers. If there is a currently selected stat, then
	/// 			for speed reasons it will only rebind that stat's node. </remarks>
	/// <param name="sdt">	[in,out] If non-null, the sdt. </param>
	engine_export void select(SimpleDataType* sdt);
	
	void addStatistic(StatisticBindingEntry& newEntry);
	engine_export StatisticBindingEntry& getSelectedEntry();
	void clearStatistics();

	engine_export StatisticBindingEntry* begin();
	engine_export StatisticBindingEntry* end();
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

/// <summary>	Defines the TrackedVariable class. </summary>
/// <remarks>	Tracked variables accept a sequence of values (one at a time)
///				and provide methods to get the current, min, max, and avg. </remarks>
class TrackedVariable : public SimpleDataType
{
private:

	static const int HISTORY_FIELD_TIME = 0;
	static const int HISTORY_FIELD_VALUE = 1;
	void assertHistory();
	void resetHistory();
	void deassertHistory();
	void deassertProfile();
	TrackedVariable();
	double curValue;
public:

	engine_export virtual const char* getClassFactory() override { return "TrackedVariable"; }
	engine_export virtual void bind() override;
	engine_export virtual char* toString(int verbose) override;

	treenode history = nullptr;
	int type = SimpleDataType::STAT_TYPE_LEVEL;
	double cumulative;
	double cumulativeTime;
	double minValue;
	double maxValue;
	double numEntries;
	double lastSetTime;
	treenode profile = nullptr;
	treenode onChange = nullptr;
	double flags = 0;

	engine_export virtual void reset();
	engine_export virtual void reset(double value);
	engine_export virtual void reset(double value, int type);
	engine_export virtual void set(double value);
	engine_export virtual void bindEvents() override;
	engine_export virtual void bindStatistics() override;

	engine_export double getAvg();
	engine_export double getMin();
	engine_export double getMax();
	engine_export double getCurrent();
	engine_export double getCount();
	engine_export double getTotalTimeAt(const Variant& state);
	Variant getTotalTimeAt(FLEXSIMINTERFACE);
	static const int PROFILE_FIELD_NAME = 0;
	static const int PROFILE_FIELD_TIME = 1;
	static const int PROFILE_FIELD_ACTIVE = 2;
	engine_export void assertProfile(int toStateRank, TreeNode* guide, bool persist);
	engine_export bool hasProfile(int toStateRank);

	engine_export virtual bool setPrimaryValue(const Variant& val) override;
	virtual Variant getPrimaryValue() override { return curValue; }
	virtual Variant evaluate(const VariantParams& params) override { return curValue; }

	engine_export static TrackedVariable* create();
	engine_export void addSubscriber(bool needsHistory, bool needsProfile, bool persist);
	Variant addSubscriber(FLEXSIMINTERFACE);
private:
	void countDownSubscribers();
	engine_export ~TrackedVariable() {}
	int needsHistoryCountDown = 0;
	int needsProfileCountDown = 0;
};
