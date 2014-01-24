
// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

# ifndef LINKLIST_H
# define LINKLIST_H

#include "basicmacros.h"
#include "basicclasses.h"
#include "byteblock.h"
#ifdef FLEXSIM_ENGINE_COMPILE
#include <vector>
#endif

#define CWSM_END 0
#define CWSM_DOUBLE 1
#define CWSM_NODE 2
#define CWSM_STRING 3
#define CWSM_BUNDLE_DATA 4
#define CWSM_BUNDLE_HEADER 5
#define CWSM_BUNDLE_RANGE 6
#define CWSM_BUNDLE 7
#define CWSM_BINARY_BYTEBLOCK 8
#define CWSM_JSON 9

#define DATA_UNDEFINED 255
// test cvs branch
#define FLAG_EXPANDED 0x01
#define FLAG_HASOWNER 0x02
#define FLAG_CPPFUNC 0x04
//#define FLAG_SELECTED 0x08 deprecated: use FLAG_EX_SELECTED
#define FLAG_HIDECONNECTORS 0x10
#define FLAG_HIDELABEL 0x20
#define FLAG_EXTENDEDFLAGS 0x40 // deprecated
#define FLAG_HASBRANCH 0x80

#define FLAG_EX_SHOWOBJECT          0x00000001
#define FLAG_EX_SELECTED            0x00000002
#define FLAG_EX_FLEXSCRIPT          0x00000004
// FLAG_EX_NULL used to be used for core->failsafelink, but now I just do a compare
// so this can be reused for something else in future versions
//#define FLAG_EX_NULL                0x00000008 

#define FLAG_EX_FUNCTIONDISABLED    0x00000010
#define FLAG_EX_KEYWORD             0x00000020 // no longer used. Can reuse in the future.
#define FLAG_EX_STATELOCKED         0x00000040 // first used for port state-change masking
#define FLAG_EX_HIDDEN              0x00000080 // prevent user viewing

#define FLAG_EX_PROTECTED           0x00000100 // prevent user editing
#define FLAG_EX_HIDESHAPE           0x00000200
#define FLAG_EX_USER_SDT			0x00000400
#define FLAG_EX_HIDEBASE            0x00000800

#define FLAG_EX_HIDECONTENT         0x00001000
#define FLAG_EX_STATSTAG            0x00002000
#define FLAG_EX_INDEXCACHE          0x00004000
#define FLAG_EX_MAINTAINARRAY       0x00008000

#define FLAG_EX_DLLFUNC				0x00010000
#define FLAG_EX_CUSTOMDISPLAY		0x00020000
#define FLAG_EX_GLOBALCPPFUNC		0x00040000
#define FLAG_EX_EXECUTINGNOW		0x00080000

#define FLAG_EX_POINTEDTO			0x00100000 // flagged only when saved, and tells me if another CouplingDataType is pointing to this node
#define FLAG_EX_DISTRIBUTEDSAVE		0x00200000 // flagged only when saved, and tells me if the node is to be saved in a "distributed file"

#define FLAG_EX_TEMP                0x00400000 // for temporary use by local procedures, such as marking used packedmedia nodes
#define FLAG_EX_VISITED				0x00400000 // visited: shared with temp: tells whether a node has been visited in a save traversal
#define FLAG_EX_DELETINGNOW			0x00400000 // deleting now: prevents recursive delete. Uses temp because it's only temporary

#define FLAG_EX_HASHEDLIST			0x00800000 // flag that says to manage a hash table of names
#define FLAG_EX_DISOWNEDDATA		0x01000000 // flag that says my data is not owned by me... only set when live, not when saved
#define FLAG_EX_ACTIVELISTENERS		0x02000000
#define FLAG_EX_DESTROYONRESET		0x04000000
#define FLAG_EX_PRESERVE_COUPLING  0x08000000 // flag that says I want to preserve coupling partners in a copy-paste or a createcopy().

#define FLAG_EX_EXTRA_BYTES			0x80000000 // reserve the last bit for future when we run out of bits and need to encode extra stuff to
												// the tree file

#define FLAG_EX_UNSAVABLE (FLAG_EX_DISOWNEDDATA | FLAG_EX_USER_SDT | FLAG_EX_INDEXCACHE | FLAG_EX_EXECUTINGNOW | FLAG_EX_TEMP)

#define SF safefind
#define SS safestep
#define SB safebranch
#define SDF safedatafloat
#define SDB safedatabyteblock
#define SDP safedatapartner

#define PAINT_BECAUSE_CLOCKTICK 1
#define PAINT_BECAUSE_OBJECTCHANGE 2
#define PAINT_BECAUSE_FLYUPDATE 3
#define PAINT_BECAUSE_LOAD 4
#define PAINT_BECAUSE_BUTTONUP 5
#define PAINT_BECAUSE_SCROLL 6
#define PAINT_BECAUSE_OBJECTSELECT 7
#define PAINT_BECAUSE_NEW 8
#define PAINT_BECAUSE_BUILD 9
#define PAINT_BECAUSE_RESET 10
#define PAINT_BECAUSE_UNDO 11
#define PAINT_BECAUSE_GUIEVENT 12
#define PAINT_BECAUSE_WINDOWOPENED 13

#define SAVE_TYPE_SESSION 1
#define SAVE_TYPE_PROJECT 2
#define SAVE_TYPE_VIEW 3
#define SAVE_TYPE_MODEL 4
#define SAVE_TYPE_LIBRARY 5
#define SAVE_TYPE_TREE 6
#define SAVE_TYPE_XML 7
#define SAVE_TYPE_MEMORY_BUFFER 8
#define SAVE_TYPE_CLIPBOARD 9
#define SAVE_TYPE_FOR_COPY 10

#define HOTLINK 1
#define COLDLINK 2
#define HOTLINKNAME 3
#define COLDLINKNAME 4
#define COMBOLINK 5
#define TABLELINK 5

#define ODTT(node) ((ObjectDataType*)(node->data))
#define PDTT(node) ((ParticleDataType*)(node->data))

#define LATEST_TREE_FILE_VERSION 4
#define LEGACY_TREE_FILE_VERSION 2

class ObjectDataType;
TreeNode * cachedfunctionnode(TreeNode *theclass, int code);
	
enum TreeSaveFlags {
	None = 0x0,
	DoNotRemoveOrphaned = 0x1,
	DoNotPreserveOrphaned = 0x2
};
inline TreeSaveFlags operator | (TreeSaveFlags a, TreeSaveFlags b)
{return static_cast<TreeSaveFlags>(static_cast<int>(a) | static_cast<int>(b));}

struct mapcmp
{
  bool operator()(TreeNode* s1, TreeNode* s2) const
  {
    return s1 < s2;
  }
};

struct treefileheader
{
	public:
	char headerstring[24];// a string identifying the tree file as a version > 2 tree format
	unsigned int headersize;// the size of the header struct
	unsigned short version;// the version number of the tree file format
	unsigned short filetype;// the filetype of the file (project/model/view/session/state/library/tree)
	unsigned int flags;// if compressed, how was it compressed (not defined, but maybe someday)
	unsigned __int64 uncompressedsize;
	unsigned char shahash[20];
};

#define FILE_FLAG_ENCRYPTED 0x1
#define FILE_FLAG_ZIPPED 0x2

#pragma pack(1) //I do my own memory alignment and padding
class TreeNode
{
  //DATA MEMBERS ARE MANUALLY ALIGNED (NO PADDING)
private:
	long unsigned int listsize;                   // (4 bytes)
	TreeNode ** array;                            // (4 or 8 bytes)
	TreeNode ** arraybase;                        // (4 or 8 bytes)
public:
	unsigned short id;                            // (2 bytes)
	BYTE datatype;                                // (1 byte)
	unsigned char flags;                          // (1 byte)
	unsigned int flags_ex;                        // (4 bytes)
private:
	ByteBlock name;                               // (10 or 14 bytes)
public:
	unsigned short parity;                        // (2 bytes)
	TreeNode * ownerobjectcache;                  // (4 or 8 bytes)
	double (* memberfunction) (FLEXSIMINTERFACE); // (4 or 8 bytes)
	HashTable<TreeNode*> * listhash;              // (4 or 8 bytes)
	int arraysize;                                // (4 bytes)
public:
	TreeNode * parent;                            // (4 or 8 bytes)
	TreeNode * owner;                             // (4 or 8 bytes)
	TreeNode * branch;                            // (4 or 8 bytes)  
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
	static unsigned short idcount;

	void initialize();
	TreeNode(){initialize();}
	int cleanup();
	~TreeNode(){cleanup();}
	double * safedatafloat();
	ByteBlock * safedatabyteblock();


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
		TreeNode* operator ->() const {return element;}
		TreeNode* operator * () {return element;}
		TreeNode* operator * () const {return element;}
		operator TreeNode*() const {return element;}
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

#ifdef FLEXSIM_ENGINE_COMPILE

	void* operator new (size_t size);
	void operator delete (void* p);

	static char treefileloadversion;

	// ------------------------
	// extra
	// ------------------------

	inline HashTable<TreeNode*> * & assertlisthash();
	HashTable<TreeNode*> * & refreshlisthash();
	// ------------------------
	// extra
	// ------------------------

	int assertarraysize(int size);
  
	// data
public:

	void breakallreferencestome();

	// checking
  
	int isvalidindex(long unsigned int i);
	inline bool checkParity(){return parity==(unsigned short)(size_t)this;}//true if valid
	TreeWin* treewindow();
	// creation
  
	TreeNode* insert(TreeNode*);
	// undoable method pointers for insert
	TreeNode* insert_undoable(TreeNode*);
	typedef TreeNode* (TreeNode::*_insert)(TreeNode*);
	static _insert insert_wrapper;

	TreeNode* insert(TreeNode*,TreeNode*);

	TreeNode* insertinto(TreeNode*);
	// undoable method pointers for insertinto
	TreeNode* insertinto_undoable(TreeNode*);
	typedef TreeNode* (TreeNode::*_insertinto)(TreeNode*);
	static _insertinto insertinto_wrapper;

	TreeNode* insertinto(TreeNode*,TreeNode*);
	int insertblock(int qty);
	int add(); // insert at end
	int add(TreeNode*); // insert at end
  
	// deletion
  
	int clear();
	int remove(TreeNode*);
	int destroy(TreeNode*);
	int nullify(TreeNode*);
	int swap(int index1, int index2);
	int validatelist();
  
	int insertbranch();
	int destroybranch();
	// undoable method pointers for destroybranch
	int destroybranch_undoable();
	typedef int (TreeNode::*_destroybranch)();
	static _destroybranch destroybranch_wrapper;
  
	// readlabel() should return a const char*, to make sure people don't write to the label
	// but that would require a ton of changes to existing code, so for now I'm leaving it
	char * readlabel();
	int getlabelsize();
	int setlabelsize(int size);

	int writelabel(const char *newname);
	// undoable method pointers for deleting data
	int writelabel_undoable(const char *);
	typedef int (TreeNode::*_writelabel)(const char *);
	static _writelabel writelabel_wrapper;

	int writelabel(const char *buffer, unsigned int size);

	// undoable method pointers for setting number data
	void setdatafloat_default(double*);
	void setdatafloat_undoable(double*);
	typedef int (TreeNode::*_setdatafloat)(double*);
	static _setdatafloat setdatafloat;

	// undoable method pointers for setting string data
	void setdatastr_default(char*);
	void setdatastr_undoable(char*);
	typedef int (TreeNode::*_setdatastr)(char*);
	static _setdatastr setdatastr;
  
	// access
  
	inline TreeNode * faststep(size_t);
	inline TreeNode * step(size_t);
	TreeNode * find(const char *);
	TreeNode * findrecursive(const char *searchname);
  
	size_t size();
	TreeNode * lastitem();
	int findindex(char *);
	int findindexrecursive(char *, int);
	int findindexrecursive_traverse(char *, int * accum, int);
  
  
	TreeNode * safefind(const char *);	
	#define F safefind
	TreeNode * safefindrecursive(const char *);	
	#define FR safefindrecursive
	inline TreeNode * safestep(int);		
	#define S safestep
	TreeNode * safenext();			
	#define N safenext
	TreeNode * safebranch();		
	#define B safebranch			
	#define DF safedatafloat
	#define	DB safedatabyteblock
	TreeNode * safedatapartner();	
	#define DP safedatapartner
  
	TreeNode * diesafely(const char* );
	#define BS(x) safebranch()->safestep(x) 
	#define BF(x) safebranch()->safefind(x) 
  
	TreeNode operator/(char *);
	TreeNode operator/(size_t);
	TreeNode operator>(char *);
	TreeNode operator>(size_t);
	//friend TreeNode * operator/(TreeNode *, char*);
	//friend TreeNode * operator/(TreeNode *, unsigned int);
  
	size_t position();
  
	TreeNode * up();
	TreeNode* next();
	TreeNode* prev();
  
	int getthepathname(TreeNode * x, char * buffer);
  
  
	// flags
  
	int toggleexpanded();
	int togglefunction();
	int toggleglobalfunction();
	int toggleflexscript();
	int toggledll();
	int togglehideconnectors();
	int toggleflag(char);
	int toggleflagex(size_t);
	int switchflag(char, int on=-1);
	int switchflagex(unsigned int, int on=-1);
	int ascodecpp();
	int ascodefpp();
	int ascodeglobalcpp();

	// load-save
  
	static bool didLastLoadHaveCppCode;
	static TreeSaveFlags curSaveFlags;
	template <class BufferAllocator>
	/// <summary>	Saves a tree. </summary>
	/// <remarks>	Allocates the necessary storage buffer and returns that buffer. The caller
	/// 			must take ownership of the returned buffer. </remarks>
	/// <param name="bufferAllocator">	The buffer allocator. Can be a lambda that allocates the storage.</param>
	/// <param name="saveType">		  	Type of the save. </param>
	/// <param name="saveSizeOut">	  	[out] (Optional) If non-null, the resulting save size
	/// 								out. </param>
	/// <returns>	Returns the buffer. </returns>
	char* saveTree(BufferAllocator bufferAllocator, int saveType, size_t* saveSizeOut = 0, TreeSaveFlags flags = None)
	{
		curSaveType = saveType;
		curSaveFlags = flags;
		saveTreePrepare();

		size_t bufferSize = estimateSaveSize();
		char* buffer = bufferAllocator(bufferSize);
		size_t saveSize = 0;
		if (buffer)
			saveSize = saveTree(buffer, saveType);

		saveTreeCleanup();

		if (saveSizeOut)
			*saveSizeOut = saveSize;

		curSaveType = SAVE_TYPE_MODEL;
		curSaveFlags = None;
		return buffer;
	}

	/// <summary>	Saves a tree. </summary>
	/// <remarks>	Allocates the necessary storage buffer and returns that buffer. The caller
	/// 			takes ownership of the returned buffer. </remarks>
	/// <param name="saveType">   	Type of the save. </param>
	/// <param name="saveSizeOut">	[out] (Optional) If non-null, the resulting save size. </param>
	/// <returns>	null if it fails, else. </returns>
	char* saveTree(int saveType, size_t* saveSizeOut = 0, TreeSaveFlags flags = None)
	{
		return saveTree([](size_t bufferSize) -> char* {return new char[bufferSize];}, saveType, saveSizeOut, flags);
	}
private:
	void saveTreePrepare();
	void saveTreeCleanup();
	size_t saveTree(char* destination, int filetype);
  
	/* There are two main file versions right now
	version 2 (really 0-2) are used for Flexsim 1-4
	version 3 has been introduced for Flexsim 5.1

	This will include compression and encryption capabilities, 
	as well as hopefully embedded media capabilities.
	*/
	bool save   (std::ostream& stream);
	bool loadstream_v2(std::istream& stream);
	bool loadstream_v3(std::istream& stream);
	int save(char*& destination);
	int load_v3(char*& source);
	int load_v2(char*& source);
	bool savelist(std::ostream& stream);
	bool loadlist(std::istream& stream);
	int savelist(char*& destination);
	int loadlist(char*& source);
	typedef int (TreeNode::*LoadCallback)(char*& source);
	static LoadCallback load;
	typedef int (TreeNode::*LoadStreamCallback)(std::istream& stream);
	static LoadStreamCallback loadstream;
	int loaddata(char*& source);
	bool savedata(std::ostream& stream);
	bool loaddata(std::istream& stream);
	int savedata(char*& source);
	/// <summary>	Estimates the save size. </summary>
	/// <remarks>	This will estimate the save size for the tree. It is just that,
	/// 			an estimate. It may not be exact. When it is not exact, it will always
	/// 			over-estimate the size needed so that if you use the return value to 
	/// 			allocate a buffer, the buffer will always be large enough for the save. </remarks>
	/// <param name="savesize">	[out] The save size. </param>
	/// <returns>	. </returns>
	size_t estimateSaveSize();
	void estimateSaveSizeRecursive(size_t& savesize);
	void estimateDataSaveSize(size_t& savesize);
	void estimateListSaveSize(size_t& savesize);
public:
	bool savetree(std::ostream& stream, int filetype);
	bool loadtree(std::istream& stream, int copycache = 0);
	int savetreetofile(const char* filepath, int filetype, int uncompressed=0);
	int loadtree(char* source, int copycache = 0, bool savedInSameProcess = false);
	int loadtreefromfile(char* filepath);
	void checkAddToSDTNodeList(int bindMode);
	void populateSDTNodeList(int bindMode, bool resetList = false);
	void bindSDTs(int bindMode, bool detachReattach = false);
	static void bindSDTList(int bindMode, bool detachReattach = false);
	static std::vector<TreeNode*> lastLoadPreservedCouplings;
private:
	void serialize_populateList();
	void serialize_resolveCounters();
	static void serialize_preserveOrphaned();
	static void serialize_removeOrphaned();
	static void serialize_finalize();
	static void serialize_restoreOrphaned();
	static int serializationcounter;
	
	enum OrphanType {
		Orphaned,
		Preserved
	};
	struct OrphanedCoupling
	{
		TreeNode* couplingNode;
		TreeNode* originalOwner;
		int rank;
		OrphanType orphanType;
	};
	static std::vector<OrphanedCoupling> orphanedCouplings;
	static TreeNode orphanedCouplingOwner;
	struct couplingrecord
	{
		TreeNode** froms;
		int nrfroms;
		int maxnrfroms;
		TreeNode* to;
		int resolved;
		double (* dupedmemberfunction) (FLEXSIMINTERFACE); 
	};
	// the following nodes are for saveing a tree
	static couplingrecord* serializationlist;
	static ptrdiff_t serializationlistsize;
	static ptrdiff_t serializationlistmaxsize;
	static void addtoserializationlist(TreeNode*, TreeNode*);
	static void resolveserialization(TreeNode*, int index);
	static int curSaveType;
	/// <summary>	when pasting/duplicating, if the copy/save was done in the same process, this is
	/// 			a flag to signal that preserved couplings can indeed be preserved. </summary>
	static bool loadBufferSavedInSameProcess;
  
	static MSXML2::IXMLDOMDocumentPtr filemapdoc;

	int pointerize_v2(TreeNode ** links, long unsigned int population);
	static std::vector<NodeRef> pointerizationpointers;
	static std::vector<NodeRef> pointerizationpointedtos;
	static int xmlpointerizationcounter;
	int serializepointers(TreeNode ** links,long unsigned int * index);
	int pointerize();
  
 public:
	void counttotalpopulation();
	// data
	int adddata(int type);
	int addSimpleData(SimpleDataType* simple, int bind, int userSDT);
	int addCouplingData(CouplingDataType* cdt, int bind, int userSDT);
	void detachSimpleData();
	// undoable method pointers for adding data
	int adddata_undoable(int type);
	typedef int (TreeNode::*_adddata)(int);
	static _adddata adddata_wrapper;
  
	int deldata();
	// undoable method pointers for deleting data
	int deldata_undoable();
	typedef int (TreeNode::*_deldata)();
	static _deldata deldata_wrapper;

	void disownDouble(double* toDouble);
	void reownDouble();

	void disownCoupling(SafeRef<TreeNode>& to);
	void reownCoupling();

	void disownByteBlock(ByteBlock * toData);
	void reownByteBlock();

	int datatostring(char *datastring, int maxsize, int precision = -1);
	int stringtodata(char *datastring);
	int isinobject();
  
	// data-pointer
  
	int pointto(TreeNode*);
	// undoable method pointers for jointo
	int pointto_undoable(TreeNode*);
	typedef int (TreeNode::*_pointto)(TreeNode*);
	static _pointto pointto_wrapper;

	int jointo(TreeNode*);
	// undoable method pointers for jointo
	int jointo_undoable(TreeNode*);
	typedef int (TreeNode::*_jointo)(TreeNode*);
	static _jointo jointo_wrapper;


	int joinback(TreeNode*);
	int breakfrom(TreeNode * source);

	int breakitoff();
	// undoable method pointers for breakitoff
	int breakitoff_undoable();
	typedef int (TreeNode::*_breakitoff)();
	static _breakitoff breakitoff_wrapper;
  
  
	// MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
	// beyond here could be part of other objects in a future version
	// MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  
  
	// class-instance
	#define LISTEN_TIME_MASK_PRE_LISTEN 0x1
	#define LISTEN_TIME_MASK_LISTEN 0x2
	void notifylisteners(TreeNode* listeners, int listencode, int originalcode, EventDataStruct * data, CallPoint* callpoint, TreeNode * associated, bool requireFlag = false);

	double receivemessage(int code, EventDataStruct * data, CallPoint * callpoint, TreeNode * associated);
	TreeNode* getclassfunctionnode(int code);
	//double executemyownfunction(TreeNode * theclass, TreeNode * theinstance, int code, void * data, char * name, int group, CallPoint * callpoint, TreeNode * associated);
	TreeNode * ihavethefunctionmyself(int code);
	TreeNode * findtheclass(int code, TreeNode **);
	TreeNode * rememberfunctionnode(int code, TreeNode *);
	double executememberfunctionwithexceptionhandling(FLEXSIMINTERFACE);
	void reportDllConnectionFailure(TreeNode* codeNode);
  
	// gui
  
	static int updatehotlinkscode;
	int updatehotlinks(int e, int); //char*);
	int updatehotlinks_in(int e, int);  //char*);
	int updatehotlinks_out(int e, int);  //char*);
	TreeNode * locatehotlink(int type, int byExpr);  //char*);
	int isnamehotlink(int t);
	int resetbuttonstate(int e);
  
	// view
  
	int spawnwindow(HWND,int, TreeNode *);
	int killwindow();
  
	int storeallviews();
	int restoreallviews();
	int restoreallviewsA();
	int restoreallviewsB();
  
	int repaintall(int reason);
	int _repaintall(int reason);
  
  
	// misc recursive
  
	int shapeautoload(int e);
	int imageautoload(int e);
	int soundautoload(int e);
	int shapeautoloadrecursive(int e);
	int imageautoloadrecursive(int e);
	int soundautoloadrecursive(int e);
  
	int expandall(int);
	int expandallobjects(int);
  
	int notifyall(int messagecode);
  
	// objecttype: 0=viewobject, 1=modelobject
	int objectbindall(int flags);
	int objectbindall_(int flags);
  
	int select(int state, int options, TreeNode* recordedchanges = NULL);
  
	int buildallflexscript();
	int cleanallflexscript();
  
	int searchall(char * pattern, double value, int type, unsigned int *n, int doreplace, char * replace, double replacen, double all);
  
	int statstoselection(int,int);

	int savetreexml(MSXML2::IXMLDOMDocumentPtr doc, char* filepath);
	static void xmlnewline(MSXML2::IXMLDOMDocumentPtr doc, MSXML2::IXMLDOMElementPtr parentnode, int indent);
	static void xmlsavedouble(MSXML2::IXMLDOMElementPtr curxmlnode, double val);
	int savexml(MSXML2::IXMLDOMDocumentPtr doc, MSXML2::IXMLDOMElementPtr parentnode, int depth = 0);
	int savedataxml(MSXML2::IXMLDOMDocumentPtr doc, MSXML2::IXMLDOMElementPtr parentnode, int depth = 0);
  
	static double xmlloaddouble(MSXML2::IXMLDOMNodePtr datanode);
	int loadtreexml(MSXML2::IXMLDOMDocumentPtr doc, char* filepath, int ignorelicense = 0);
	int loadxml(MSXML2::IXMLDOMNodeListPtr thenodes, int index);
	int loaddataxml(MSXML2::IXMLDOMNodePtr curnode);

	int isequal(TreeNode *, int *);
	void swapodt(ObjectDataType* newodt);
	static int receivemessageeventtypes[50];
	static void registereventtypes();

	static int listenermessagecode;
	static TreeNode* listenerassociated;
	static TreeNode* listenercoupling;

	static const int STOP_TRAVERSE_OBJ_TREE = 0x1;
	static const int STOP_TRAVERSE_SUB_TREE = 0x2;
	static const int STOP_TRAVERSE = STOP_TRAVERSE_OBJ_TREE | STOP_TRAVERSE_SUB_TREE;
	template <class Func>
	void traverseTree(Func func, bool includeObjects = true)
	{
		int stopType = func(this);

		if(includeObjects && datatype == DATA_OBJECT && !(stopType & STOP_TRAVERSE_OBJ_TREE))
			dataasobject->objecttree.traverseTree(func, includeObjects);

		if (listsize > 0) {
			TreeNode* curNode = step(1), *nextNode = 0;
			while (curNode) {
				nextNode = curNode->next();
				curNode->traverseTree(func, includeObjects);
				curNode = nextNode;
			}
		}

		if(branch && !(stopType & STOP_TRAVERSE_SUB_TREE))
			branch->traverseTree(func, includeObjects);
	}

	bool contains(TreeNode* descendant);
#endif
};
#pragma pack()//restore packing to its default value


struct portinfo
{
	TreeNode* object;
	int portnr;
	short portopen;
	short metaopen;
};
#ifdef FLEXSIM_ENGINE_COMPILE

int duplicate(TreeNode * from, TreeNode * to);
TreeNode * ensurebranch(TreeNode * node);

TreeNode * operator/(TreeNode& a, char  * b);

TreeNode * forcevalidlink(TreeNode *, char *);

TreeNode * boundfunctionnode(TreeNode *theclass, int code);

void * flexsimmalloc(size_t size);
void * flexsimrealloc(void* memory, size_t size);
void flexsimfree(void * p);

__int64 asciiblock_getsize(char * f, __int64 p, __int64 sz, char * starttag, char * endtag);
__int64 asciiblock_read(char * f, __int64 p, __int64 sz, char * starttag, char * endtag, char *destination);
__int64 asciiblock_whatisnexttag(char * f, __int64 p, __int64 sz, char * starttag, char * endtag, char *destination);
__int64 asciiblock_advancepasttag(char * f, __int64 p, __int64 sz, char * tag);
__int64 asciiblock_advancebeforetag(char * f, __int64 p, __int64 sz, char * tag);


//extern char rb[1000000];
#define ASCIIBLOCK_READoriginal(TAG_A,TAG_B)\
  asciiblock_read(f,p,sz,TAG_A,TAG_B,rb);\
  p=asciiblock_advancepasttag(f,p,sz,TAG_A);\
  p=asciiblock_advancepasttag(f,p,sz,TAG_B); 


#define ASCIIBLOCK_READ(TAG_A,TAG_B)\
  bsz=asciiblock_getsize(f,p,sz,TAG_A,TAG_B);\
  if (rb) delete [] rb; rb=new char[bsz+4];\
  asciiblock_read(f,p,sz,TAG_A,TAG_B,rb);\
  p=asciiblock_advancepasttag(f,p,sz,TAG_A);\
  p=asciiblock_advancepasttag(f,p,sz,TAG_B); 

inline char gethexvalue(char c)
{
	switch(c)
	{
		case '0':default: return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'a':case 'A': return 0xa;
		case 'b':case 'B': return 0xb;
		case 'c':case 'C': return 0xc;
		case 'd':case 'D': return 0xd;
		case 'e':case 'E': return 0xe;
		case 'f':case 'F': return 0xf;
	}
}
#endif

# endif
















// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.














