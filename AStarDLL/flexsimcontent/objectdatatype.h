
// COPYRIGHT 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

#ifndef objectdatatype_h
#define objectdatatype_h

#include "byteblock.h"
#include "treenode.h"
#include "simpledatatype.h"
#include "couplingdatatype.h"

#define ODT ObjectDataType

#ifdef FLEXSIM_ENGINE_COMPILE
#include "glm.h"

#define STATE_PROFILE_CURRENT 1
#define STATE_PROFILE_SINCE 2
#define STATE_PROFILE_LIST 3
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
	static double splineTension;
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
	int imageautoload(TreeNode * parentobject);
	int soundautoload(TreeNode * parentobject);
  
	engine_export int bindstructure(TreeNode *, unsigned int flags);
  
	int bind(TreeNode *, TreeNode **, char *);
	virtual void bind() override { SimpleDataType::bind(); }
   
	int datatostring(char *, int n);
  
	Menu custommenu;
	static const int MENU_MERGE = 1;
	static const int MENU_OVERRIDE = 2;
	Menu popupmenu(TreeWin* t, int* objMenuMode, TreeNode* theMenu = 0);
	int createmenufromtree(TreeNode *menutree);
	int createmenufromtree_(TreeNode *menutree, Menu nextmenu, Menu supermenu);
   
	int bind_media_shape();
	int bind_media_image();
	int bind_media_sound();
  

	TreeNode* thefunctionbindings[SM_MAX_MESSAGES];

	struct hashvalue {int counterindex; int offset;};
	static std::unordered_map<std::string, hashvalue> hashattributes;
	static std::unordered_map<std::string, hashvalue> hashbasetable;
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

	static TreeNode* findclassbyname(TreeNode* object, const char* fullclassname);
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
	engine_export void bindStatsObject(const char* version = nullptr);

public:
	engine_export Vec3 __getCentroid();
	engine_export Vec3 getLocation(double xFactor, double yFactor, double zFactor);
	engine_export Vec3 getLocation(const Vec3& factors);
	engine_export ObjectDataType& setLocation(double x, double y, double z);
	engine_export ObjectDataType& setLocation(double x, double y, double z, double xFactor, double yFactor, double zFactor);
	engine_export ObjectDataType& setLocation(const Vec3& location, const Vec3& factors)
	{
		return setLocation(location.x, location.y, location.z, factors.x, factors.y, factors.z);
	}
	engine_export ObjectDataType& setRotation(double x, double y, double z);
	engine_export ObjectDataType& setSize(double x, double y, double z);




	engine_export Vec3& __getLocation();
	engine_export Vec3& __getRotation();
	engine_export Vec3& __getSize();

	__declspec(property(get = __getLocation)) Vec3& location;
	__declspec(property(get = __getRotation)) Vec3& rotation;
	__declspec(property(get = __getSize)) Vec3& size;

	engine_export void setState(int state, int profile);

	engine_export Color& __getColor();
	// making color into a property creates name collisions with the color() attribute command
	// so for now I'm leaving this out.
	//__declspec(property(get = __getColor)) Color& color;

	engine_export void setLabelProperty(const char* name, unsigned nameHash, const Variant& val);
	engine_export Variant getLabelProperty(const char* name, unsigned nameHash, bool dieHard);

	engine_export TreeNode* findAttribute(const char* path);

	private:
	typedef TreeNode* (ObjectDataType::*GetBoundEventAttribute)();
	static GetBoundEventAttribute eventAttributeGetters[SM_MAX_MESSAGES];
	TreeNode * getBoundEventAttribute_SM_RESET(){ return Nb_OnReset; }
	TreeNode * getBoundEventAttribute_SM_MESSAGE() { return Nb_OnMessage;}
	TreeNode * getBoundEventAttribute_SM_EVENT() { return Nb_OnTimerEvent;}
	TreeNode * getBoundEventAttribute_SM_DRAW() { return Nb_OnDraw;}
	TreeNode * getBoundEventAttribute_SM_PREDRAW() { return Nb_OnPreDraw;}
	TreeNode * getBoundEventAttribute_SM_INOPEN() { return Nb_OnInOpen;}
	TreeNode * getBoundEventAttribute_SM_OUTOPEN() { return Nb_OnOutOpen;}
	TreeNode * getBoundEventAttribute_SM_ACCEPT() { return Nb_OnReceive;}
	TreeNode * getBoundEventAttribute_SM_GIVE() { return Nb_OnSend;}
	TreeNode * getBoundEventAttribute_SM_ENTER() { return Nb_OnEntering;}
	TreeNode * getBoundEventAttribute_SM_EXIT() { return Nb_OnExiting;}

	TreeNode * getBoundEventAttribute_SM_COMPILE() { return Nb_OnCompile;}
	TreeNode * getBoundEventAttribute_SM_CREATE() { return Nb_OnCreate;}
	TreeNode * getBoundEventAttribute_SM_DESTROY() { return Nb_OnDestroy;}
	TreeNode * getBoundEventAttribute_SM_UNDO() { return Nb_OnUndo;}
	TreeNode * getBoundEventAttribute_SM_CLICK() { return Nb_OnClick;}
	TreeNode * getBoundEventAttribute_SM_RUNSTART() { return Nb_OnRunStart;}
	TreeNode * getBoundEventAttribute_SM_RUNWARM() { return Nb_OnRunWarm;}
	TreeNode * getBoundEventAttribute_SM_RUNEND() { return Nb_OnRunEnd;}
	TreeNode * getBoundEventAttribute_SM_LISTEN() { return Nb_OnListen;}
	TreeNode * getBoundEventAttribute_SM_DRAWPLANAR() { return Nb_OnDrawPlanar;}
	TreeNode * getBoundEventAttribute_SM_PREDRAWPLANAR() { return Nb_OnPreDrawPlanar;}
	TreeNode * getBoundEventAttribute_SM_PRELISTEN() { return Nb_OnPreListen;}

	TreeNode * getBoundEventAttribute_SM_STATECHANGE() { return Nb_OnStateChange;}

	TreeNode * getBoundEventAttribute_SM_DRAG() { return Nb_OnDrag;}
public:
	TreeNode* getBoundEventAttributeByMessageCode(int messageCode);

	static ObjectDataType* createEngineODTDerivative(const char* classname);
	typedef ObjectDataType* (*CreateODTDerivative)(const char* classname);
	static CreateODTDerivative createContentODTDerivative;
	static ObjectDataType* createODTDerivative_NoDLLConnection(const char* classname);

	// These lists are bound in CompilerDataTypes.cpp, so I can bind them as registered classes, not content registered classes

	static bool shouldCachePorts;

	engine_export TreeNode* assertAttribute(const char *name, int datatype);
	engine_export ObjectDataType* __getClassObject();
	__declspec(property(get = __getClassObject)) ObjectDataType* classObject;


	typedef NodeListArray<ObjectDataType>::OutObjectTypeOneBased OutObjectArray;
	typedef NodeListArray<ObjectDataType>::InObjectTypeOneBased InObjectArray;
	typedef NodeListArray<ObjectDataType>::CenterObjectTypeOneBased CenterObjectArray;
	typedef NodeListArray<ObjectDataType>::ObjSubNodeTypeOneBased ObjectItemArray;

	void resetStats();

	class engine_export Animation
	{
		friend Variant getanimationvar(TreeNode*, int, const char*);
	protected:
		TreeNode* animation;
		TreeNode* object;
		TreeNode* variables;

#if defined FLEXSIM_COMMANDS
		static TreeNode* animationVariable;
#endif

	public:
		Animation(TreeNode* animationNode = nullptr);
		void construct(const Animation& other);
		Animation& operator=(const Animation& other);

		void start(int speedType = 0, double speedValue = 0, int repeatType = 0, double repeatValue = 0);
		void stop();
		void update(double updateTime = -1);

		Variant getVariable(const char* variableName, unsigned nameHash, bool dieHard);
		void setVariable(const char* variableName, unsigned nameHash, const Variant& value);

		static void bindInterface();
	};

	class engine_export AnimationsArray
	{
	protected:
		TreeNode* object = nullptr;
		TreeNode* animations = nullptr;

	public:
		AnimationsArray(TreeNode* object = nullptr);
		void construct(const AnimationsArray& other);
		AnimationsArray& operator=(const AnimationsArray& other);

		Animation operator [](const char* animation);
		Animation operator [](int animation);
		Animation operator [](const Variant& animation);
		// Animation _assert(const char* animationName);
		int __getLength();
		__declspec(property (get = __getLength)) int length;

		operator bool();

		static void bindInterface();
	};

	engine_export AnimationsArray __getAnimations() { return AnimationsArray(holder); }
	__declspec(property(get = __getAnimations)) AnimationsArray animations;

	engine_export virtual void stop(int stopState, int id = 0, double priority = 0.0, int stateProfile = 0);
	engine_export virtual void resume(int id = 0, int stateProfile = 0);

	engine_export const float* __getModelToWorldMatrix();
	__declspec(property(get = __getModelToWorldMatrix)) const float* modelToWorldMatrix;

	virtual ObjectDataType* toObject() override { return this; }
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














