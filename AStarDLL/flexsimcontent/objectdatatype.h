
// COPYRIGHT 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

#ifndef objectdatatype_h
#define objectdatatype_h

#include "byteblock.h"
#include "treenode.h"
#include "hashtable.h"
#include "simpledatatype.h"
#define ODT ObjectDataType

#ifdef FLEXSIM_ENGINE_COMPILE
#include "glm.h"
#endif

#define CLASS_NAME_SEPARATOR ':'

class portcache;

namespace FlexSim {

class ObjectDataType;


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
		void getRot(size_t entryIndex, glm::dvec3& rot);
	#endif
	void clear();
	void addEntries(size_t nrCachePoints);
	unsigned int calcCheckSum(treenode spline);
	void buildCache(treenode holder);

	Entry * entries;
	size_t nrEntries;
	double length;
	unsigned int checkSum;
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

#ifdef FLEXSIM_ENGINE_COMPILE
	class basetable
	{
	public:
	  basetable(){};


	#define H_LOC_ODT_VARIABLE_TABLE(v,ODTMEMBERPREFIX)  \
	  TreeNode * NTable##ODTMEMBERPREFIX##v; 
  
	  //              ATT ADDPOINT 7
  
	#define DECLARE_ATTRIBUTE(ATTRIBUTE_DEFAULT,ATTRIBUTE_NAME, ...) H_LOC_ODT_VARIABLE_TABLE(ATTRIBUTE_NAME,b_)
	#include "attributes_table.h"
	#undef DECLARE_ATTRIBUTE
	};
#else
	class basetable;
#endif


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

	engine_export void initialize();
	ObjectDataType(){initialize();}
	engine_export void cleanup();
	virtual ~ObjectDataType(){cleanup();}
	int resetbasetable();

	// The following method was added by Anthony Johnson 2-16-2006
	virtual unsigned int getClassType(){return 0;}
	virtual double dragConnection(treenode toobject, char characterpressed, unsigned int classtype){return 0;}

	TreeNode objecttree;

	ScenePositionCache* sceneCache;
  
	portcache * theportcache;

	// these are for fast lookup of spline distances
	SplineCache* splineCache;
	void addSplineCache(size_t np, size_t res);
	void clearSplineCache(bool isDestructor = false);
	void buildSplineCache(size_t res);

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
  
	engine_export int bindstructure(TreeNode *, unsigned int flags);
  
	int bind(TreeNode *, TreeNode **, char *);
	virtual void bind() override { SimpleDataType::bind(); }
   
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
	basetable* createbasetable();


	#define H_LOC_ODT_VARIABLE(v,ODTMEMBERPREFIX)  \
	TreeNode * N##ODTMEMBERPREFIX##v; 
  
	//              ATT ADDPOINT 7
  
	TreeNode* firstattribute;
	#define DECLARE_ATTRIBUTE(ATTRIBUTE_DEFAULT,ATTRIBUTE_NAME, ...) H_LOC_ODT_VARIABLE(ATTRIBUTE_NAME,b_)
	#include "attributes.h"
	#undef DECLARE_ATTRIBUTE
	TreeNode* lastattribute;

	void copyattributebindingsfrom(ObjectDataType* odt);

	static TreeNode* findclassbyname(TreeNode* object, char* fullclassname);
	static ObjectDataType* createodtderivativefromclassatt(TreeNode* classatt);

	static const int ODT_BIND_STATE_VARIABLE = 0x1;
	ObjectDataType* checkCreateODTDerivative(TreeNode* classesAtt);
	engine_export TreeNode* bindVariableNode(char* name, bool isStateVariable);
	engine_export void bindVariableByName(const char* name, double& val, int flags = 0);
	engine_export void bindVariableByName(const char* name, TreeNode*& val, int flags = 0);
	engine_export void bindVariableByName(const char* name, ByteBlock& val, int flags = 0);
	engine_export void bindVariableByName(const char* name, NodeRef& val, int flags = 0);
public:

	#define bindVariable(x) bindVariableByName(#x, x)
	#define bindStateVariable(x) bindVariableByName(#x, x, ODT_BIND_STATE_VARIABLE)

	engine_export virtual TreeNode* getObjectTree() override;
	engine_export virtual TreeNode* getLabelNode(const char* labelName, bool assert) override;
	engine_export virtual TreeNode* getLabelNode(int labelRank, bool assert) override;

	engine_export virtual void bindEvents() override;
	engine_export virtual TreeNode* getEventInfoObject(const char* eventTitle) override;

	engine_export virtual void bindInterface() override;
	Vec3 __getCentroid();
	Vec3 getLocation(double xFactor, double yFactor, double zFactor);
	Vec3 getLocation(const Vec3& factors);
	ObjectDataType& setLocation(double x, double y, double z);
	ObjectDataType& setLocation(double x, double y, double z, double xFactor, double yFactor, double zFactor);
	ObjectDataType& setRotation(double x, double y, double z);
	ObjectDataType& setSize(double x, double y, double z);

	Vec3& __getLocation();
	Vec3& __getRotation();
	Vec3& __getSize();

	__declspec(property(get = __getLocation)) Vec3& location;
	__declspec(property(get = __getRotation)) Vec3& rotation;
	__declspec(property(get = __getSize)) Vec3& size;

	Color& __getColor();
	// making color into a property creates name collisions with the color() attribute command
	// so for now I'm leaving this out.
	//__declspec(property(get = __getColor)) Color& color;

	void setLabelProperty(const char* name, unsigned nameHash, const Variant& val);
	Variant getLabelProperty(const char* name, unsigned nameHash, bool dieHard);


	TreeNode* findAttribute(const char* path);
};


// declare the list of allocator functions: one per attribute
int bindattributestree(ObjectDataType *, TreeNode * client);

#define ODT_SETMEMBERFUNC_H(v,ODTMEMBERPREFIX) \
int odtsetmemberfunction##ODTMEMBERPREFIX##v(FlexSim::ObjectDataType * D,  FlexSim::TreeNode * P);
#define DECLARE_ATTRIBUTE(ATTRIBUTE_DEFAULT,ATTRIBUTE_NAME, ...) ODT_SETMEMBERFUNC_H(ATTRIBUTE_NAME,b_)
#include "attributes.h"
#undef DECLARE_ATTRIBUTE

}


#endif
















// COPYRIGHT 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.














