
// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

#ifndef objectdatatype_h
#define objectdatatype_h

//class TreeNode; 

#include "treenode.h"
#include "hashtable.h"
#include "simpledatatype.h"
#define ODT ObjectDataType

#define CLASS_NAME_SEPARATOR ':'

class ObjectDataType;
class portcache;

#ifdef FLEXSIM_ENGINE_COMPILE
#include "glm.h"
#endif

class SplineCache
{
public:
	SplineCache() : nrEntries(0), entries(0), length(0.0), checkSum(0) {}
	~SplineCache();
	struct Entry
	{
		#ifdef FLEXSIM_ENGINE_COMPILE
			glm::dvec3 pos;
		#else
			double pos[3];
		#endif
		double distAlong;
		double percAlong;
	};
	
	#ifdef FLEXSIM_ENGINE_COMPILE
		void getRot(int entryIndex, glm::dvec3& rot);
	#endif
	void clear();
	void addEntries(int nrCachePoints);
	unsigned int calcCheckSum(treenode spline);
	void buildCache(treenode holder);

	Entry * entries;
	int nrEntries;
	double length;
	unsigned int checkSum;
};

class odtfptr_
{
public:
  odtfptr_(){};
  int (* setmember) (ObjectDataType*, TreeNode *);         
};

/***** The following class is only defined because I want to explicitly fire code when I start***/
class fireconstructor{
public:
	int dummyval;
	fireconstructor();
};


class _LOD
{
public:
  _LOD();
  int * LODtable;
  int LODtablesize;
  
  int LODresettable();
  int LODgetmember(int index);

  int LODaddtotable(int index);
  int LODgettablesize();

  double range_pers;
  double range_pers_type;
  double range_ortho;


};

class _REEL
{
public:
  _REEL();
  int * REELtable;
  int REELtablesize;
  
  int REELresettable();
  int REELgetmember(int index);

  int REELaddtotable(int index);
  int REELgettablesize();

  double range_pers;
  double range_pers_type;
  double range_ortho;


};


class basetable
{
public:
  basetable(){};


#define H_LOC_ODT_VARIABLE_TABLE(v,ODTMEMBERPREFIX)  \
  TreeNode * NTable##ODTMEMBERPREFIX##v; 
  
  //              ATT ADDPOINT 7
  
#define DECLARE_ATTRIBUTE(ATTRIBUTE_DEFAULT,ATTRIBUTE_NAME,ATTRIBUTE_COMMENTS) H_LOC_ODT_VARIABLE_TABLE(ATTRIBUTE_NAME,b_)
#include "attributes_table.h"
#undef DECLARE_ATTRIBUTE
};

  
//extern odtfptr_ setmemberptr[140];

int objectdatatype__setmemberfunctionpointerarray();

class ObjectDataType : public SimpleDataType
{
private:

	int reset();

public:
  
	void* operator new (size_t size)
	{
		void* p = flexsimmalloc(size);
		if(!p) throw 0;
		return p;
	}

	void operator delete (void* p){flexsimfree(p);}

	void initialize();
	ObjectDataType(){initialize();}
	void cleanup();
	virtual ~ObjectDataType(){cleanup();}
	int resetbasetable();

	// The following method was added by Anthony Johnson 2-16-2006
	virtual unsigned int getClassType(){return 0;}
	virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype){return 0;}

	TreeNode objecttree;

	ScenePositionCache* sceneCache;

	//int setmemberfunctionpointerarray();
  
	portcache * theportcache;

	// these are for fast lookup of spline distances
	SplineCache* splineCache;
	void addSplineCache(int np, int res);
	void clearSplineCache(bool isDestructor = false);
	void buildSplineCache(int res);

	TreeNode * classcache;
	TreeNode * superclasscache;
	char * copycache;
	TreeWin * treewindow;
  
	unsigned int boundnodecheckmask;
	unsigned int boundnodeabsentmask;

	ByteBlock cpptypestring;
	int cpptypecode;
 
	int shapeautoload(TreeNode * parentobject);
	int shapeautoload_diag(TreeNode * parentobject);
	int imageautoload(TreeNode * parentobject);
	int soundautoload(TreeNode * parentobject);
  
	int bindstructure(TreeNode *, unsigned int flags);
  
	int bind(TreeNode *, TreeNode **, char *);
   
	int datatostring(char *, int n);
  
	HMENU custommenu;
	static const int MENU_MERGE = 1;
	static const int MENU_OVERRIDE = 2;
	HMENU popupmenu(TreeWin* t, int* objMenuMode, TreeNode* theMenu = 0);
	int createmenufromtree(TreeNode *menutree);
	int createmenufromtree_(TreeNode *menutree, HMENU nextmenu, HMENU supermenu);
   
	int bind_media_shape();
	int bind_media_image();
	int bind_media_sound();
  

	TreeNode* thefunctionbindings[SM_MAX_MESSAGES];
	struct hashvalue {int counterindex; int offset;};
	static HashTable<hashvalue> hashattributes;
	static HashTable<hashvalue> hashbasetable;
	static void bindhashattributes();
	int resetfunctionbindings();

	virtual void bindVariables(){return;}
	PortDrawCache* findPortDrawCache(TreeNode* couplingNode);
   
	int indexbindings;

	basetable * thebasetable;
	int createbasetable();


	#define H_LOC_ODT_VARIABLE(v,ODTMEMBERPREFIX)  \
	TreeNode * N##ODTMEMBERPREFIX##v; 
  
	//              ATT ADDPOINT 7
  
	TreeNode* firstattribute;
	#define DECLARE_ATTRIBUTE(ATTRIBUTE_DEFAULT,ATTRIBUTE_NAME,ATTRIBUTE_COMMENTS) H_LOC_ODT_VARIABLE(ATTRIBUTE_NAME,b_)
	#include "attributes.h"
	#undef DECLARE_ATTRIBUTE
	TreeNode* lastattribute;

	void copyattributebindingsfrom(ObjectDataType* odt);

	static TreeNode* findclassbyname(TreeNode* object, char* fullclassname);
	static ObjectDataType* createodtderivativefromclassatt(TreeNode* classatt);

	ObjectDataType* checkCreateODTDerivative(TreeNode* classesAtt);
	TreeNode* bindVariableNode(char* name);
	void bindVariableByName(const char* name, double& val);
	void bindVariableByName(const char* name, TreeNode*& val);
	void bindVariableByName(const char* name, ByteBlock& val);
	void bindVariableByName(const char* name, NodeRef& val);
	#define bindVariable(x) bindVariableByName(#x, x)
};

int bindattributestree(ObjectDataType *, TreeNode * client);

// declare the list of allocator functions: one per attribute


#define ODT_SETMEMBERFUNC_H(v,ODTMEMBERPREFIX) \
int odtsetmemberfunction##ODTMEMBERPREFIX##v(ObjectDataType * D,  TreeNode * P);
    
#define DECLARE_ATTRIBUTE(ATTRIBUTE_DEFAULT,ATTRIBUTE_NAME,ATTRIBUTE_COMMENTS) ODT_SETMEMBERFUNC_H(ATTRIBUTE_NAME,b_)
#include "attributes.h"
#undef DECLARE_ATTRIBUTE



#endif
















// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.














